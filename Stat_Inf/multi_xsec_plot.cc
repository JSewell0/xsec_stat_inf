#include "TCanvas.h"
#include "TMultiGraph.h"
#include <iostream>
#include <fstream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <map>
#include <cstdlib>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

vector<vector<string>> read_csv(TString file_name){

  fstream fin;
  fin.open(file_name, ios::in);

  vector<string> row;
  vector<vector<string>> table;
  string word, temp;

  while (getline(fin,temp)) {

    row.clear();
    stringstream s(temp);

    while (getline(s, word, ',')) {

	    row.push_back(word);
    }
    table.push_back(row);
  }
  return table;
}

double get_median_mu(float nlsp_mass){

  TFile* tf = new TFile("Limits_bTag_v2_NoUncNoCR_TChiWH.root","r");
  TH2D* th = (TH2D*) tf->Get("mGlmNLSP_median");
  double mu = th->GetBinContent(th->GetXaxis()->FindBin(nlsp_mass),th->GetYaxis()->FindBin(100),0);

  return mu;
}

float get_xsec_sum(float nlsp_mass){
  
  TFile* tf2 = new TFile("EWkinoXsec.root","r");  
  TH1D* th1 = (TH1D*) tf2->Get("mEWeakino_N2C1Xsec");
  float xsec = th1->GetBinContent(th1->GetXaxis()->FindBin(nlsp_mass))*1000;

  return xsec;
  
}

TGraph* GraphMake(int size,float mass_arr[],float xsec_arr[],TString name,int j){


  
  TGraph* tg = new TGraph(size,mass_arr,xsec_arr);


  cout<<endl;
  
  return tg;
}

void GraphDraw(TString outfile_name,vector<TString> scenarios,vector<TGraph*>& tg){

  vector<Color_t> colors = {kRed+1,kViolet+5,kBlue+8,kBlack};
  
  TFile* outfile  = new TFile("multi_limits.root", "recreate");  
  TCanvas* can1 = new TCanvas("can1","can1",500,500);
  can1->SetGrid();
  gPad->SetLogy();

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(outfile_name);
  mg->GetXaxis()->SetTitle("Mass Gev");
  mg->GetYaxis()->SetTitle("CL upper limit on cross section [pb]");  
  
  for(int j=0;j<tg.size();j++){
    
    tg[j]->SetLineColor(colors[j]);
    tg[j]->SetLineWidth(2);
    
    if(j == 3){
      tg[j]->SetLineStyle(9);
    }
    
    mg->Add(tg[j]);
    
  }

  mg->Draw("*L");
  mg->GetXaxis()->SetLimits(200,1100);
  mg->SetMinimum(0.1);
  mg->SetMaximum(10000);  

  auto legend = new TLegend(0.45,0.8,0.6,0.9);
  legend->SetHeader("models","C");
  legend->SetTextSize(0.025);

  for(int i=0;i<tg.size()-1;i++){
    
    legend->AddEntry(tg[i],scenarios[i]+" limit","l");
    
  }

  cout<<endl<<"Constructed sms multigraphs..."<<endl<<endl;
  
  legend->AddEntry(tg[3],"Vinay limit","l");  
  legend->Draw();
  
  outfile->WriteObject(can1,"mutli sms limits");

  cout<<"Wrote "<<outfile_name<<".root"<<"!"<<endl;
  
  delete can1;
  
}

int multi_xsec_plot(){

  vector<TString> scenarios = {"WHsms","WWsms","WZsms","WZsms"};
  vector<TGraph*> graph_vect = {};  

  for(int j=0;j<scenarios.size()+1;j++){
    vector<vector<string>> rval_table = read_csv(scenarios[j]+"_rvals_avg.csv");

    // get xsec for each mass point
    vector<float> xsecs;
    vector<float> median_xsecs;

    for(int i=1;i<rval_table.size();i++){

      float mass = stof(rval_table[i][0]);
      float rval = stof(rval_table[i][1]);
      double mu = get_median_mu(mass);
      float xsec_sum = get_xsec_sum(mass);
      xsecs.push_back(rval*xsec_sum);
      median_xsecs.push_back(mu*xsec_sum);

    }




    int size = xsecs.size();

    float mass_arr[size];
    float xsec_arr[size];
    float median_xsec_arr[size];


    // convert vectors to arrays for tgraph
    for(int i=0;i<size;i++){
      median_xsec_arr[i] = median_xsecs[i];
      xsec_arr[i] = xsecs[i];
      mass_arr[i] = stof(rval_table[i+1][0]);
    }

    if(graph_vect.size() == scenarios.size()-1){

      graph_vect.push_back(GraphMake(size,mass_arr,median_xsec_arr,"Vinay limit",j));
      break;
      
    }

    graph_vect.push_back(GraphMake(size,mass_arr,xsec_arr,scenarios[j]+" limit",j));
      
  }

  cout<<endl<<"Constructed Graphs..."<<endl;
  GraphDraw("multi_limits",scenarios,graph_vect);
  
  return 0;  
}
