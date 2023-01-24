#include "TCanvas.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>

//gInterpreter->GenerateDictionary("vector<TLorentzVector>", "vector");
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

TString inFileName ="/Users/jsewell/Documents/ROOT_documents/Autumn18Fast.NiramaySUSY_CN925_sgino100_sget90_sgetBB_7_RA2AnalysisTree.root";


void HistPlot()
{
  // Open the root file
  TFile* tf = new TFile(inFileName,"r");

  // look for a TTree object in the root file
  TTree* tr = (TTree*) tf->Get("TreeMaker2/PreSelection");
  tr->SetMakeClass(1);
  // Define variables which will store the values read from the root file
  vector<TLorentzVector>* EvtVal;                  // This will store a single float value per event read
  EvtVal=0;
  vector<int>* TriggerPrescales{0};      // This will store a std::vector of integers per event read
  
  TString Branch = "Jets";
  
  TCanvas* tc = new TCanvas("aa","bb",800,600); 
  TH1F* h1 = new TH1F("h1","title",100,-5,5);
  
  //cout << EvtVal << endl;
  // declare which branches to read, and where to store the data read
  tr->SetBranchAddress(Branch,&EvtVal);
  tr->SetBranchAddress("TriggerPrescales",&TriggerPrescales);

  // Read each event
  for(int evt=0;evt<tr->GetEntries();evt++){
    tr->GetEntry(evt);          // This will read evt'th entry, and store the data

    if( EvtVal->size() != 0 ){
    	h1->Fill(EvtVal->at(3).Eta());
    } 
  
  }
  
  h1->Draw();

  h1->SetTitle(Branch+".Eta()");
  h1->SetLineColor(kViolet+5);
  h1->SetLineWidth(2);
  
  tc->SetGrid();
  tc->SaveAs(Branch+"Eta3.png");
  delete tc;
}


`
