#include "TCanvas.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

unique_ptr<TFile> trf( TFile::Open("signal_templates.root", "RECREATE") );

void file_process(TString file_name,TString sr,TString hist_file_name,TString hist_name,TString model_xsec,vector<float> mass,TH1F* hist1,TString xsec_file_name="EWkinoXsec.root"){
  
  TString path = "/Users/jsewell/Documents/ROOT_documents/Stat_Inf/";

  TString file1 = path + hist_file_name;
  TString file2 = path + xsec_file_name;

  TFile* tf1 = new TFile(file1,"r");
  TFile* tf2 = new TFile(file2,"r");

  TH3F* th3 = (TH3F*) tf1->Get(hist_name);
  TH1D* th1 = (TH1D*) tf2->Get(model_xsec);

  float nlsp_mass = mass[0];
  float lsp_mass = mass[1];
  float lum = 137;


  for(int i=1;i<hist1->GetNbinsX()+1;i++){
    float AccXEff = th3->GetBinContent(th3->GetXaxis()->FindBin(nlsp_mass),th3->GetYaxis()->FindBin(lsp_mass),i);
    float xsec = th1->GetBinContent(th1->GetXaxis()->FindBin(nlsp_mass))*1000;
    float num_events = AccXEff * xsec * lum;
  
    hist1->SetBinContent(i,num_events);
  }

  hist1->SetLineColor(kViolet+5);
  hist1->SetLineWidth(2);
  TString root_file_name = "TChi"+file_name+"_"+sr+"SR_"+Form("%g",nlsp_mass)+"_"+Form("%g",lsp_mass);
  
  trf->WriteObject(hist1,root_file_name);
  cout<<"Wrote "<<root_file_name<<"... "<<endl;
 
}

void signal_finder(){

  vector<vector<float>> masses = {{1000,100},{925,100},{750,100},{600,100},{500,100}};
  vector<TString> file_names = {"HZ","WH","WW","WZ"};
  vector<TString> search_regions = {"WH","W","H"};

  for(int i=0;i<file_names.size();i++){
    
    TString file_name = file_names[i];
    TString hist_file_name = "AllBinAccXEff_TChi"+file_name+".root";
    
    for(int j=0;j<search_regions.size();j++){
      
      TString sr = search_regions[j];
      TString hist_name = "AccXEff_"+sr+"SR";

      for(int k=0;k<masses.size();k++){
	
	double WHbins[9] = {200,250,300,350,400,450,500,600,1200};
	double Wbins[10] = {200,250,300,350,400,450,500,600,800,1200};
	double Hbins[10] = {200,250,300,350,400,450,500,600,800,1200};
	
	if(sr == "WH"){
	  TH1F* signal_met = new TH1F("signal_met",";MET;Events",8,WHbins);
          file_process(file_name,sr,hist_file_name,hist_name,"mEWeakino_N2C1Xsec",masses[k],signal_met);
	}
	
	else if(sr == "W"){
	  TH1F* signal_met = new TH1F("signal_met",";MET;Events",9,Wbins);
          file_process(file_name,sr,hist_file_name,hist_name,"mEWeakino_N2C1Xsec",masses[k],signal_met);
	}

	else if(sr == "H"){
	  TH1F* signal_met = new TH1F("signal_met",";MET;Events",9,Hbins);
          file_process(file_name,sr,hist_file_name,hist_name,"mEWeakino_N2C1Xsec",masses[k],signal_met);
	}	

      }
    }
  }
  cout<<"Done!"<<endl;
}













