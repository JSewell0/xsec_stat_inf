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

float get_xsec_sum(vector<vector<string>> table,int i){
  
  int index = 0;
  float sum = 0;
  
  for(string name : table[0]){
    if(name.find("xc") != string::npos) {
      sum += stof(table[i][index]);
    }
    index += 1;
  }  
  return sum;
}

void GraphDraw(TFile* outfile,TString outfile_name,vector<TGraph*> tg){

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetGrid();
  gPad->SetLogy();

  TFile* tf1 = new TFile("Excl1D_Limits_AllReg_v8_TChiWH.root","r");
  TGraph* tg1 = (TGraph*) tf1->Get("exp");

  TMultiGraph *mg = new TMultiGraph();
  
  tg[0]->SetLineColor(kViolet+5);
  tg[0]->SetLineWidth(2);

  tg[1]->SetLineColor(kSpring+4);
  tg[1]->SetLineWidth(2);

  tg1->SetLineColor(1);
  tg1->SetLineWidth(2);
  tg1->SetLineStyle(9);
  
  mg->Add(tg[0]);
  mg->Add(tg[1]);
  mg->Add(tg1,"L");
  mg->Draw("L*");

  mg->SetMaximum(1.1);
  mg->SetMinimum(.0001);
  
  auto legend = new TLegend(0.45,0.8,0.6,0.9);
  legend->SetHeader("","C");
  legend->SetTextSize(0.025);
  legend->AddEntry(tg[0],"pos mu","l");
  legend->AddEntry(tg[1],"neg mu","l");
  legend->AddEntry(tg1,"median expected","l");  
  legend->Draw();
  
  mg->SetTitle(outfile_name);  
  mg->GetXaxis()->SetTitle("Mass Gev");
  mg->GetYaxis()->SetTitle("CL upper limit on cross section [pb]");  
  
  outfile->WriteObject(can,outfile_name);

  cout<<"Wrote "<<outfile_name<<"!"<<endl;
  
  delete can;
  

}

int xsec_plot(){

  TFile* outfile  = new TFile("xsec_graphs_avg.root", "recreate");
  vector<string> scenarios = {"1a","1b","2b","3b"};

  for(string scenario : scenarios){
    vector<vector<string>> rval_table = read_csv(scenario+"_rvals_avg.csv");
    vector<vector<string>> rates_table = read_csv(scenario+"rates.csv");

    // get xsec for each mass point
    vector<vector<float>> xsecs;
    for(int j=1;j<3;j++){

      vector<float> temp = {};

      for(int i=1;i<rval_table.size();i++){

	float rval = stof(rval_table[i][j]);
	float xsec_sum = get_xsec_sum(rates_table,i);
	temp.push_back(rval*xsec_sum);
      }

      xsecs.push_back(temp);
    }

    int size = xsecs[0].size();
    
    float mass_arr[size];
    float  pos_mu_xsec_arr[size];
    float  neg_mu_xsec_arr[size];

    // convert vectors to arrays for tgraph
    for(int i=0;i<size;i++){
      pos_mu_xsec_arr[i] = xsecs[0][i];
      neg_mu_xsec_arr[i] = xsecs[1][i];    
      mass_arr[i] = stof(rval_table[i+1][0]);
    }

    //add +- mu xsec tgraphs to root file
    TGraph* tg1 = new TGraph(size,mass_arr,pos_mu_xsec_arr);
    TGraph* tg2 = new TGraph(size,mass_arr,neg_mu_xsec_arr);
    vector<TGraph*> graph_vect = {tg1,tg2};
    GraphDraw(outfile,scenario+"_limits",graph_vect);
  }  
  return 0;  
}
