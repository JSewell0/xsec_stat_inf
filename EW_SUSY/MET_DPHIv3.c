#include "TCanvas.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include "WHBB.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

//Root file initialization
TString prod_method = "WZ";
TString bb_or_glgl = "BB";
TString particle_name = "G";
int pdg_id = 1000039;
TString sample_name = prod_method+bb_or_glgl;
unique_ptr<TFile> trf( TFile::Open(sample_name+"_"+particle_name+"DPHI.root", "RECREATE") );

//Cut values & Weights
TLorentzVector MET4;
vector<double> AK4DPhi = {1.5,0.5,0.3,0.3};
vector<double> AK8DPhi = {1.5,0.5};

double Scale5 = (46.3533e-3 * 137000);
double Scale6 = (20.1372e-3 * 137000);
double Scale7 = (6.69356e-3 * 137000);
double Scale9 = (2.12907e-3 * 137000);

//Functions
bool AK4JetsCut(WHBB& obj){

  int c = 0;
  for(int i=0;i<obj.Jets->size();i++){
    if (obj.Jets->at(i).Pt()>30 && fabs(obj.Jets->at(i).Eta())<2.4){
      c++;
   }
     }
  return !(c<2 || c>6);

}
  
      
bool AK8JetsCut(WHBB& obj){

  int c = 0;
    for(int i=0;i<obj.JetsAK8->size();i++){
      if(obj.JetsAK8->at(i).Pt()>200 && fabs(obj.JetsAK8->at(i).Eta())<2 && obj.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
      else{continue;}
    }
  return (c>=1);
}

bool TwoAK8Jets(WHBB& obj){

  int c = 0;
    for(int i=0;i<obj.JetsAK8->size();i++){
      if(obj.JetsAK8->at(i).Pt()>200 && fabs(obj.JetsAK8->at(i).Eta())<2 && obj.JetsAK8_softDropMass->at(i)>0){
	c++;
	      }
     }
  return (c>=2);

}
  
bool HTPTCut(WHBB& obj){

  return (obj.HT>300 && obj.MET>200);

}

bool AK4DeltaPhiCut(WHBB& obj){

  for(int i=0;i<obj.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
      if(!(fabs(obj.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);

}

bool AK8DeltaPhiCut(WHBB& obj){

    for(int i=0;i<obj.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(obj.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
}

bool NVetos(WHBB& obj){

  return ( obj.NElectrons == 0 && obj.NMuons == 0 );

}

bool TrackVetos(WHBB& obj){

  return ( obj.isoElectronTracks == 0 && obj.isoMuonTracks == 0 && obj.isoPionTracks == 0 );
  
}

//WH SR-->WHTag(1,999,1,999)
//H SR-->WHTag(0,0,1,999)
//W SR-->WHTag(1,999,0,0)

bool WHTag(int MinWTag,int MaxWTag, int MinHTag, int MaxHTag,WHBB& obj){
  
double AK8PtThreshold=200.;
double AK8EtaThreshold=2.0;
double AK4PtThreshold=30.;
double AK4EtaThreshold=2.4;
double bbDiscThreshold=0.8365;
double WDiscThreshold=0.918;
double bDiscThreshold=0.4184;


std::vector<int> BtagIndices;

 
BtagIndices.clear();
 int HiggsTags = 0 ;
 int WbosonTags = 0 ;
 
for( int i = 0 ; i < obj.Jets->size(); i++){
  if( obj.Jets->at(i).Pt() > AK4PtThreshold &&
      fabs(obj.Jets->at(i).Eta()) < AK4EtaThreshold &&
      obj.Jets_bJetTagDeepCSVBvsAll->at(i) > bDiscThreshold ) BtagIndices.push_back(i);
}

if( BtagIndices.size() == 0 ) return false;


for( int i = 0 ; i < obj.JetsAK8->size() ; i++){

  bool HiggsCand=false;

  for( int b = 0 ; b < BtagIndices.size() ; b++){

    if( obj.JetsAK8->at(i).DeltaR(obj.Jets->at(BtagIndices[b])) < 0.8 ){
      HiggsCand=true;
      break;
    }// end if 
  }// end loop over bjets

if( HiggsCand ){

    HiggsTags+=int(obj.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		   fabs(obj.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		   obj.JetsAK8_DeepMassDecorrelTagbbvsLight->at(i) > bbDiscThreshold &&
		   obj.JetsAK8_softDropMass->at(i) > 75 &&
		   obj.JetsAK8_softDropMass->at(i) < 140 );
  }else{

    WbosonTags+=int(obj.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		    fabs(obj.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		    obj.JetsAK8_DeepTagWvsQCD->at(i) > WDiscThreshold &&
		    obj.JetsAK8_softDropMass->at(i) > 65 &&
		    obj.JetsAK8_softDropMass->at(i) < 105 );
  }// end if-else block to check for Higgs or W candidates

}// end loop over AK8 jets 

 return HiggsTags >= MinHTag && HiggsTags <= MaxHTag && WbosonTags >= MinWTag && WbosonTags <= MaxWTag ;
  }


TLorentzVector METAdd(WHBB& obj,int pdgid){
  TLorentzVector sum = {0,0,0,0};
   
     for(int pdg = 0;pdg<obj.GenParticles_PdgId->size();pdg++){

       if( abs(obj.GenParticles_PdgId->at(pdg)) == pdgid  ){
	 sum += obj.GenParticles->at(pdg);    
       }
     }
  return sum;
 }

void CutFlow(TString file_name, double weight, int pdgid, TH1F* hist, TH1F* hist2, TH1F* hist3,TString hist_name){

  TString file_path = "/Users/jsewell/Documents/ROOT_documents/EW_SUSY/";
  TString file = file_path + file_name;

  TFile* tf = new TFile(file,"r");

  TTree* tr = (TTree*) tf->Get("TreeMaker2/PreSelection");

  WHBB obj(tr);
  
  Long64_t nentries = tr->GetEntriesFast();
  Long64_t nentries_ = tr->GetEntries();

    for(Long64_t jentry=0;jentry<nentries;jentry++){
    
    Long64_t ientry = obj.LoadTree(jentry);
    if (ientry < 0) break;
   
    obj.GetEntry(jentry);
   
    TLorentzVector MET4 = {0,0,0,0};
    MET4.SetPtEtaPhiE(obj.MET,0,obj.METPhi,0);

    TLorentzVector METSum = METAdd(obj,pdgid);
    double DPHIMET = MET4.DeltaPhi(METSum);

    if(obj.Jets->size() == 0){ continue ; }
    
    if(obj.JetsAK8->size() == 0){ continue; }
      

    if( NVetos(obj) && TrackVetos(obj) && HTPTCut(obj) && AK4JetsCut(obj) && AK8JetsCut(obj) && AK4DeltaPhiCut(obj) && AK8DeltaPhiCut(obj) && TwoAK8Jets(obj) ){

      //WH SR
      if(WHTag(1,999,1,999,obj)){ hist->Fill(DPHIMET,weight/nentries_); }
      
      //H SR
      if(WHTag(0,0,1,999,obj)){ hist2->Fill(DPHIMET,weight/nentries_); }
      
      //W SR
      if(WHTag(1,999,0,0,obj)){ hist3->Fill(DPHIMET,weight/nentries_); }
              
     }//end if statement--------------------
   }//end for loop================================

    trf->WriteObject(hist,"WH SR "+hist_name);
    trf->WriteObject(hist2,"H SR "+hist_name);
    trf->WriteObject(hist3,"W SR "+hist_name);

    cout<<"Wrote "<<prod_method+bb_or_glgl<<"_"<<hist_name<<"..."<<endl;
}



void MET_DPHIv3(){

  //CN500
    TH1F* WH_MET5 = new TH1F("WH_MET5",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET5 = new TH1F("W_MET5",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET5 = new TH1F("H_MET5",";MET;Events",24,-M_PI,M_PI);
  //CN600
    TH1F* WH_MET6 = new TH1F("WH_MET6",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET6 = new TH1F("W_MET6",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET6 = new TH1F("H_MET6",";MET;Events",24,-M_PI,M_PI);
  //CN750
    TH1F* WH_MET7 = new TH1F("WH_MET7",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET7 = new TH1F("W_MET7",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET7 = new TH1F("H_MET7",";MET;Events",24,-M_PI,M_PI);
  //CN925
    TH1F* WH_MET9 = new TH1F("WH_MET9",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET9 = new TH1F("W_MET9",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET9 = new TH1F("H_MET9",";MET;Events",24,-M_PI,M_PI);

  //CutFlow(TString file_name, TTree* tree, double weight, int pdgid, TH1F* WH_hist, TH1F* W_hist, TH1F* H_hist, TString hist_name)
    CutFlow("CN500_"+prod_method+"_sgino100_sget90_"+bb_or_glgl+".root", Scale5, pdg_id, WH_MET5, H_MET5, W_MET5, particle_name+"5DPHI");
    CutFlow("CN600_"+prod_method+"_sgino100_sget90_"+bb_or_glgl+".root", Scale6, pdg_id, WH_MET6, H_MET6, W_MET6, particle_name+"6DPHI");
    CutFlow("CN750_"+prod_method+"_sgino100_sget90_"+bb_or_glgl+".root", Scale7, pdg_id, WH_MET7, H_MET7, W_MET7, particle_name+"7DPHI");
    CutFlow("CN925_"+prod_method+"_sgino100_sget90_"+bb_or_glgl+".root", Scale9, pdg_id, WH_MET9, H_MET9, W_MET9, particle_name+"9DPHI");

    trf->Close();
    
}
