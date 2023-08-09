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

vector<vector<string>> get_rates(string file_name){

	// File pointer
	fstream fin;

	// Open an existing file
	fin.open(file_name, ios::in);

	// Read the Data from the file
	// as String Vector
	vector<string> row;
        vector<vector<string>> table;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// append row of data to table
		table.push_back(row);

	}
	return table;
}


void file_process(TFile* trf,TString file_name,TString sr,TString hist_file_name,TString hist_name,float xsec,string mass,TH1F* hist1){
  
  TString path = "/Users/jsewell/Documents/xsec_stat_inf/Stat_Inf/";

  TString file1 = path + hist_file_name;

  TFile* tf1 = new TFile(file1,"r");

  TH3F* th3 = (TH3F*) tf1->Get(hist_name);

  float nlsp_mass = stof(mass);
  float lsp_mass = 100;
  float lum = 137000;


  for(int i=1;i<hist1->GetNbinsX()+1;i++){
    float AccXEff = th3->GetBinContent(th3->GetXaxis()->FindBin(nlsp_mass),th3->GetYaxis()->FindBin(lsp_mass),i);
    float num_events = AccXEff * xsec * lum;
  
    hist1->SetBinContent(i,num_events);
  }

  hist1->SetLineColor(kViolet+5);
  hist1->SetLineWidth(2);
  TString root_file_name = "TChi"+file_name+"_"+sr+"_"+Form("%.3g",nlsp_mass)+"_"+Form("%.3g",lsp_mass);
  
  trf->WriteObject(hist1,root_file_name);
  if(nlsp_mass > 540){
    cout<<"model: "<<file_name<<endl;
    cout<<"sr: "<<sr<<endl;
    cout<<"nlsp mass: "<<nlsp_mass<<endl;
    cout<<"xsec: "<<xsec<<endl;
    cout<<"num entries: "<<hist1->Integral()<<endl<<endl;
    /* cout<<"Wrote "<<root_file_name<<"... "<<endl<<endl; */
  }
 
}

void mu_signal_finder(){

  float xsec;
  TString file_name_mu;
  TFile* outfile_name  = new TFile("2b_signal_templates.root", "RECREATE");
  
  vector<vector<string>> table = get_rates("2brates.csv");
  vector<TString> plus_minus = {"+","-"};
  vector<TString> file_names = {"HZ","WH","WW"};
  vector<TString> search_regions = {"WHSR","WSR","HSR","bVeto"};
  int mass_index = 22;

  for(int i=0;i<file_names.size();i++){
    
    TString file_name = file_names[i];
    TString hist_file_name = "AllBinAccXEff_TChi"+file_name+".root";

    for(int n=0;n<2;n++){

      if(file_name == "WW" && n == 1){break;}
      
      for(int j=0;j<search_regions.size();j++){
      
	TString sr = search_regions[j];
	TString hist_name = "AccXEff_"+sr;

	for(int k=1;k<table.size();k++){
	
	  double WHbins[9] = {200,250,300,350,400,450,500,600,1200};
	  double Wbins[10] = {200,250,300,350,400,450,500,600,800,1200};
	  double Hbins[10] = {200,250,300,350,400,450,500,600,800,1200};
	  
	  if(file_name == "HZ"){
	    file_name_mu = file_name + plus_minus[n];
	    xsec = stof(table[k][n+7]);
	  }	  

	  else if(file_name == "WH"){
	    file_name_mu = file_name + plus_minus[n];
	    xsec = stof(table[k][n+2]);
	  }

	  else if(file_name == "WW"){
	    file_name_mu = file_name;
	    xsec = stof(table[k][4]);
	  }	  	  
	  
	  if(sr == "WHSR"){
	    TH1F* signal_met = new TH1F("signal_met",";MET;Events",8,WHbins);
	    file_process(outfile_name,file_name_mu,sr,hist_file_name,hist_name,xsec,table[k][mass_index],signal_met);
	  }
	
	  else{
	    TH1F* signal_met = new TH1F("signal_met",";MET;Events",9,Hbins);
	    file_process(outfile_name,file_name_mu,sr,hist_file_name,hist_name,xsec,table[k][mass_index],signal_met);
	  }

	}
      }
    }
  }
  cout<<"Done!"<<endl;
}
