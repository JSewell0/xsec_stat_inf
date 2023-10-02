#include "TCanvas.h"
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
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

vector<vector<string>> read_csv(string file_name){

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
  
  TString xsec_file_name="EWkinoXsec.root";
  TFile* tf2 = new TFile("EWkinoXsec.root","r");  
  TH1D* th1 = (TH1D*) tf2->Get("mEWeakino_N2C1Xsec");
  float xsec = th1->GetBinContent(th1->GetXaxis()->FindBin(nlsp_mass))*1000;

  return xsec;
  
}

void GraphDraw(TFile* outfile,TString outfile_name,vector<TGraph*> tg){

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetGrid();
  gPad->SetLogy();

  // TFile* tf1 = new TFile("Excl1D_Limits_AllReg_v8_TChiWH.root","r");
  // TGraph* tg1 = (TGraph*) tf1->Get("exp");

  TMultiGraph *mg = new TMultiGraph();
  
  tg[0]->SetLineColor(kViolet+5);
  tg[0]->SetLineWidth(2);

  tg[1]->SetLineColor(kSpring-7);
  tg[1]->SetLineWidth(2);  

  // tg1->SetLineColor(1);
  // tg1->SetLineWidth(2);
  // tg1->SetLineStyle(9);
  
  mg->Add(tg[0]);
  mg->Add(tg[1]);
  mg->Draw("L*");

  mg->SetMaximum(1.1);
  mg->SetMinimum(.0001);
  
  auto legend = new TLegend(0.45,0.8,0.6,0.9);
  legend->SetHeader("","C");
  legend->SetTextSize(0.025);
  legend->AddEntry(tg[0],"WH sms","l");
  legend->AddEntry(tg[1],"NoUnc limit","l");  
  // legend->AddEntry(tg1,"median expected","l");  
  legend->Draw();
  
  mg->SetTitle(outfile_name);  
  mg->GetXaxis()->SetTitle("Mass Gev");
  mg->GetYaxis()->SetTitle("CL upper limit on cross section [pb]");  
  
  outfile->WriteObject(can,outfile_name);

  cout<<"Wrote "<<outfile_name<<"!"<<endl;
  
  delete can;
  

}

int sms_xsec_plot(){

  TFile* outfile  = new TFile("sms_limits.root", "recreate");
  string scenario = "WHsms";

  vector<vector<string>> rval_table = read_csv(scenario+"_rvals_avg.csv");

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

  //add +- mu xsec tgraphs to root file
  TGraph* tg1 = new TGraph(size,mass_arr,xsec_arr);
  TGraph* tg2 = new TGraph(size,mass_arr,median_xsec_arr);  
  vector<TGraph*> graph_vect = {tg1,tg2};
  GraphDraw(outfile,scenario+"_limits",graph_vect);
  
  return 0;  
}
