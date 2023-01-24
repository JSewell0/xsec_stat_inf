#include "TCanvas.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#define myclass_cxx
#include "autumnclass.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

TString inFileName ="/Users/jsewell/Documents/ROOT_documents/EW_SUSY/Signal_1000_100_Autumn18Fast_TChiWH.root";
TFile* tf = new TFile(inFileName,"r");
TTree* tr = (TTree*) tf->Get("tree");
    autumnclass h(tr);

TLorentzVector MET4;
vector<double> AK4DPhi = {1.5,0.5,0.3,0.3};
vector<double> AK8DPhi = {1.5,0.5};


bool AK4JetsCut(){
  int c = 0;
  for(int i=0;i<h.Jets->size();i++){
    if (h.Jets->at(i).Pt()>30 && fabs(h.Jets->at(i).Eta())<2.4){
      c++;
    }
    
  }
  return !(c<2 || c>6);
  }
      
bool AK8JetsCut(){
  int c = 0;
    for(int i=0;i<h.JetsAK8->size();i++){
      if(h.JetsAK8->at(i).Pt()>200 && fabs(h.JetsAK8->at(i).Eta())<2 && h.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
     }
  return (c>=1);
}

bool TwoAK8Jets(){
  if(h.JetsAK8->size() >= 2){
    return (true);
  }
  else {return (false);}
}
  
bool HTPTCut(){
  return (h.HT>300 && h.MET>200);
}

bool AK4DeltaPhiCut(){
  for(int i=0;i<h.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
        if(!(fabs(h.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);
}

bool AK8DeltaPhiCut(){
    for(int i=0;i<h.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(h.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
}

bool NVetos(){
  return ( h.NElectrons == 0 && h.NMuons == 0 );
}

bool TrackVetos(){
  return ( h.isoElectronTracks == 0 && h.isoMuonTracks == 0 && h.isoPionTracks == 0 );
}


void SUSY_Analysis(){
 
   gStyle->SetOptStat(1111111);

    TCanvas* tc = new TCanvas("aa","bb",800,600);
    TH1F* h1 = new TH1F("h1","title",100,-1,3);


    
  // Read each event
    for(int evt=0;evt<tr->GetEntries();evt++){
    h.GetEntry(evt);

    MET4.SetPtEtaPhiE(h.MET,0,h.METPhi,0);
    
    if(h.Jets->size() == 0){
      continue;}
    
    if(h.JetsAK8->size() == 0){
      continue;}

    if( NVetos() && TrackVetos() && HTPTCut() && AK4JetsCut() && AK8JetsCut() && AK4DeltaPhiCut() && AK8DeltaPhiCut() && TwoAK8Jets()){
      h1->Fill(1,h.Weight*137000);}
       
      
  }


  h1->Draw();

  h1->SetTitle("count");
  h1->SetLineColor(kViolet+5);
  h1->SetLineWidth(2);

  tc->SetGrid();
  tc->SaveAs("count.png");
  delete tc;
}




