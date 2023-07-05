#include "TCanvas.h"
#include <iostream>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include "autumnclass.C"
#include "WZBB.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector> +;
#pragma link C++ class vector<vector<short> >+;
#endif

using namespace std;

//unique_ptr<TFile> trf( TFile::Open("MET_S1DPHI_WZBB.root", "RECREATE") );

//File initialization
TString File1 ="/Users/jsewell/Documents/ROOT_documents/EW_SUSY/CN500_WZ_sgino100_sget90_BB.root";
TString File2 ="/Users/jsewell/Documents/ROOT_documents/EW_SUSY/CN600_WZ_sgino100_sget90_BB.root";
TString File3 ="/Users/jsewell/Documents/ROOT_documents/EW_SUSY/CN750_WZ_sgino100_sget90_BB.root";
TString File4 ="/Users/jsewell/Documents/ROOT_documents/EW_SUSY/CN925_WZ_sgino100_sget90_BB.root";

TFile* tf1 = new TFile(File1,"r");
TFile* tf2 = new TFile(File2,"r");
TFile* tf3 = new TFile(File3,"r");
TFile* tf4 = new TFile(File4,"r");

TTree* tr1 = (TTree*) tf1->Get("TreeMaker2/PreSelection");
TTree* tr2 = (TTree*) tf2->Get("TreeMaker2/PreSelection");
TTree* tr3 = (TTree*) tf3->Get("TreeMaker2/PreSelection");
TTree* tr4 = (TTree*) tf4->Get("TreeMaker2/PreSelection");

WZBB c1(tr1);
WZBB c2(tr2);
WZBB c3(tr3);
WZBB c4(tr4);

//Cut values & Weights
TLorentzVector MET4;
vector<double> AK4DPhi = {1.5,0.5,0.3,0.3};
vector<double> AK8DPhi = {1.5,0.5};

double WZBB5Weight = 2.05777e-06;
double WZBB6Weight = 4.53489e-07;
double WZBB7Weight = 3.04765e-07;
double WZBB9Weight = 5.57407e-08;

double WHBB5Weight = 1.01343e-06;
double WHBB6Weight = 4.45119e-07;
double WHBB7Weight = 1.52922e-07;
double WHBB9Weight = 5.14554e-08;

double HHBB5Weight = 9.85737e-07;
double HHBB6Weight = 4.36664e-07;
double HHBB7Weight = 1.43046e-07;
double HHBB9Weight = 4.72025e-08;

double WZGLGL5Weight = 1.03433e-06;
double WZGLGL6Weight = 5.25858e-07;
double WZGLGL7Weight = 1.53118e-07;
double WZGLGL9Weight = 5.65055e-08;

double WHGLGL5Weight = 1.02747e-06;
double WHGLGL6Weight = 4.45247e-07;
double WHGLGL7Weight = 1.53311e-07;
double WHGLGL9Weight = 5.18325e-08;

double HHGLGL5Weight = 1.11994e-06;
double HHGLGL6Weight = 4.35597e-07;
double HHGLGL7Weight = 1.43343e-07;
double HHGLGL9Weight = 4.67219e-08;

double scale5 = (46.3533e-3 * 137000);
double scale6 = (20.1372e-3 * 137000);
double scale7 = (6.69356e-3 * 137000);
double scale9 = (2.12907e-3 * 137000);

//Functions
void HistPlot4(TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4, TString title,  TString label1, TString label2, TString label3, TString label4, TString OutFile, bool log=true){

  TCanvas* can = new TCanvas("can","can",500,500);
  can->SetGrid();
  if(log){gPad->SetLogy();}
  
  gStyle->SetOptStat("neMi");
  
  double max1 = h1->GetMaximum();
  double max2 = h2->GetMaximum();
  double max3 = h3->GetMaximum();
  double max4 = h4->GetMaximum();
  double TrueMax = max({max1,max2,max3,max4});

  h1->SetMaximum(TrueMax + 1);
  h1->SetMinimum(0);
  
  h1->SetLineColor(kViolet+5);
  h1->SetLineWidth(2);
  // h1->Scale((scale9)(h1->GetEntries())/(tree->GetEntries()));

  h2->SetLineColor(kAzure+1);
  h2->SetLineWidth(2);
  //  h2->Scale(scale7/(h2->GetEntries()));

  h3->SetLineColor(kSpring+4);
  h3->SetLineWidth(2);
  //  h3->Scale(scale6/(h3->GetEntries()));

  h4->SetLineColor(kOrange-3);
  h4->SetLineWidth(2);
  //  h4->Scale(scale5/(h4->GetEntries()));

  h1->Draw("hist");
  h2->Draw("SAME hist");
  h3->Draw("SAME hist");
  h4->Draw("SAME hist");
  h1->GetYaxis()->SetTitle("NEvents");
  h1->GetXaxis()->SetTitle("Phi");
  h1->SetTitle(title);
  
  auto legend = new TLegend(0.45,0.8,0.75,0.9);
  legend->SetHeader("Files","C");
  legend->SetTextSize(0.025);
  legend->AddEntry(h1,label1,"l");
  legend->AddEntry(h2,label2,"l");
  legend->AddEntry(h3,label3,"l");
  legend->AddEntry(h4,label4,"l");
  legend->Draw();

  can->SaveAs(OutFile);

  delete can;
 }




bool AK4JetsCut(int file){
  if(file==1){
  int c = 0;
  for(int i=0;i<c1.Jets->size();i++){
    if (c1.Jets->at(i).Pt()>30 && fabs(c1.Jets->at(i).Eta())<2.4){
      c++;
   }
     }
  return !(c<2 || c>6);
    }
  if(file==2){
  int c = 0;
  for(int i=0;i<c2.Jets->size();i++){
    if (c2.Jets->at(i).Pt()>30 && fabs(c2.Jets->at(i).Eta())<2.4){
      c++;
   }
     }
  return !(c<2 || c>6);
    }
  if(file==3){
  int c = 0;
  for(int i=0;i<c3.Jets->size();i++){
    if (c3.Jets->at(i).Pt()>30 && fabs(c3.Jets->at(i).Eta())<2.4){
      c++;
   }
     }
  return !(c<2 || c>6);
    }
  if(file==4){
  int c = 0;
  for(int i=0;i<c4.Jets->size();i++){
    if (c4.Jets->at(i).Pt()>30 && fabs(c4.Jets->at(i).Eta())<2.4){
      c++;
   }
     }
  return !(c<2 || c>6);
    }
  else{return true;}
}
  
      
bool AK8JetsCut(int file){
  if(file==1){
  int c = 0;
    for(int i=0;i<c1.JetsAK8->size();i++){
      if(c1.JetsAK8->at(i).Pt()>200 && fabs(c1.JetsAK8->at(i).Eta())<2 && c1.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
     }
  return (c>=1);
  }
if(file==2){
  int c = 0;
    for(int i=0;i<c2.JetsAK8->size();i++){
      if(c2.JetsAK8->at(i).Pt()>200 && fabs(c2.JetsAK8->at(i).Eta())<2 && c2.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
     }
  return (c>=1);
  }
if(file==3){
  int c = 0;
    for(int i=0;i<c3.JetsAK8->size();i++){
      if(c3.JetsAK8->at(i).Pt()>200 && fabs(c3.JetsAK8->at(i).Eta())<2 && c3.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
     }
  return (c>=1);
  }
if(file==4){
  int c = 0;
    for(int i=0;i<c4.JetsAK8->size();i++){
      if(c4.JetsAK8->at(i).Pt()>200 && fabs(c4.JetsAK8->at(i).Eta())<2 && c4.JetsAK8_softDropMass->at(i)>50){
	c++;
	      }
     }
  return (c>=1);
  }
   else{return true;}
}

bool TwoAK8Jets(int file){
  if(file==1){
  int c = 0;
    for(int i=0;i<c1.JetsAK8->size();i++){
      if(c1.JetsAK8->at(i).Pt()>200 && fabs(c1.JetsAK8->at(i).Eta())<2 && c1.JetsAK8_softDropMass->at(i)>0){
	c++;
	      }
     }
  return (c>=2);
    }
  
  if(file==2){
  int c = 0;
    for(int i=0;i<c2.JetsAK8->size();i++){
      if(c2.JetsAK8->at(i).Pt()>200 && fabs(c2.JetsAK8->at(i).Eta())<2 && c2.JetsAK8_softDropMass->at(i)>0){
	c++;
	      }
     }
  return (c>=2);
    }
  if(file==3){
  int c = 0;
    for(int i=0;i<c3.JetsAK8->size();i++){
      if(c3.JetsAK8->at(i).Pt()>200 && fabs(c3.JetsAK8->at(i).Eta())<2 && c3.JetsAK8_softDropMass->at(i)>0){
	c++;
	      }
     }
  return (c>=2);
    }
  if(file==4){
  int c = 0;
    for(int i=0;i<c4.JetsAK8->size();i++){
      if(c4.JetsAK8->at(i).Pt()>200 && fabs(c4.JetsAK8->at(i).Eta())<2 && c4.JetsAK8_softDropMass->at(i)>0){
	c++;
	      }
     }
  return (c>=2);
    }
    else{return true;}
}
  
bool HTPTCut(int file){
  if(file==1){
  return (c1.HT>300 && c1.MET>200);
    }
  if(file==2){
    return (c2.HT>300 && c2.MET>200);
    }
  if(file==3){
    return (c3.HT>300 && c3.MET>200);
    }
  if(file==4){
    return (c4.HT>300 && c4.MET>200);
    }
    else{return true;}
}

bool AK4DeltaPhiCut(int file){
  if(file==1){
  for(int i=0;i<c1.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
      if(!(fabs(c1.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);
  }
  if(file==2){
  for(int i=0;i<c2.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
      if(!(fabs(c2.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);
  }
  if(file==3){
  for(int i=0;i<c3.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
      if(!(fabs(c3.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);
  }
  if(file==4){
  for(int i=0;i<c4.Jets->size();i++){
      if(i==AK4DPhi.size()){break;}
      if(!(fabs(c4.Jets->at(i).DeltaPhi(MET4))>AK4DPhi.at(i))){
           return (false);
    }
  }
   return (true);
  }
    else{return true;}
}

bool AK8DeltaPhiCut(int file){
  if(file==1){
    for(int i=0;i<c1.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(c1.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
  }
  if(file==2){
    for(int i=0;i<c2.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(c2.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
  }
  if(file==3){
    for(int i=0;i<c3.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(c3.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
  }
  if(file==4){
    for(int i=0;i<c4.JetsAK8->size();i++){
      if(i==AK8DPhi.size()){break;}
    if(!(fabs(c4.JetsAK8->at(i).DeltaPhi(MET4))>AK8DPhi.at(i))){
      return (false);
    }
  }
  return (true);
  }
    else{return true;}
}

bool NVetos(int file){
  if(file==1){
  return ( c1.NElectrons == 0 && c1.NMuons == 0 );
  }
  if(file==2){
  return ( c2.NElectrons == 0 && c2.NMuons == 0 );
  }
  if(file==3){
  return ( c3.NElectrons == 0 && c3.NMuons == 0 );
  }
  if(file==4){
  return ( c4.NElectrons == 0 && c4.NMuons == 0 );
  }
    else{return true;}
}

bool TrackVetos(int file){
  if(file==1){
  return ( c1.isoElectronTracks == 0 && c1.isoMuonTracks == 0 && c1.isoPionTracks == 0 );
  }
  if(file==2){
  return ( c2.isoElectronTracks == 0 && c2.isoMuonTracks == 0 && c2.isoPionTracks == 0 );
  }
  if(file==3){
  return ( c3.isoElectronTracks == 0 && c3.isoMuonTracks == 0 && c3.isoPionTracks == 0 );
  }
  if(file==4){
  return ( c4.isoElectronTracks == 0 && c4.isoMuonTracks == 0 && c4.isoPionTracks == 0 );
  }
    else{return true;}
}

//WH SR-->WHTag(1,999,1,999)
//H SR-->WHTag(0,0,1,999)
//W SR-->WHTag(1,999,0,0)

bool WHTag(int MinWTag,int MaxWTag, int MinHTag, int MaxHTag,int file){

  if( file == 1 ){
  
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
 
for( int i = 0 ; i < c1.Jets->size(); i++){
  if( c1.Jets->at(i).Pt() > AK4PtThreshold &&
      fabs(c1.Jets->at(i).Eta()) < AK4EtaThreshold &&
      c1.Jets_bJetTagDeepCSVBvsAll->at(i) > bDiscThreshold ) BtagIndices.push_back(i);
}

if( BtagIndices.size() == 0 ) return false;


for( int i = 0 ; i < c1.JetsAK8->size() ; i++){

  bool HiggsCand=false;

  for( int b = 0 ; b < BtagIndices.size() ; b++){

    if( c1.JetsAK8->at(i).DeltaR(c1.Jets->at(BtagIndices[b])) < 0.8 ){
      HiggsCand=true;
      break;
    }// end if 
  }// end loop over bjets

if( HiggsCand ){

    HiggsTags+=int(c1.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		   fabs(c1.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		   c1.JetsAK8_DeepMassDecorrelTagbbvsLight->at(i) > bbDiscThreshold &&
		   c1.JetsAK8_softDropMass->at(i) > 75 &&
		   c1.JetsAK8_softDropMass->at(i) < 140 );
  }else{

    WbosonTags+=int(c1.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		    fabs(c1.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		    c1.JetsAK8_DeepTagWvsQCD->at(i) > WDiscThreshold &&
		    c1.JetsAK8_softDropMass->at(i) > 65 &&
		    c1.JetsAK8_softDropMass->at(i) < 105 );
  }// end if-else block to check for Higgs or W candidates

}// end loop over AK8 jets 

 return HiggsTags >= MinHTag && HiggsTags <= MaxHTag && WbosonTags >= MinWTag && WbosonTags <= MaxWTag ;
  }

  if( file == 2 ){
  
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
 
for( int i = 0 ; i < c2.Jets->size(); i++){
  if( c2.Jets->at(i).Pt() > AK4PtThreshold &&
      fabs(c2.Jets->at(i).Eta()) < AK4EtaThreshold &&
      c2.Jets_bJetTagDeepCSVBvsAll->at(i) > bDiscThreshold ) BtagIndices.push_back(i);
}

if( BtagIndices.size() == 0 ) return false;


for( int i = 0 ; i < c2.JetsAK8->size() ; i++){

  bool HiggsCand=false;

  for( int b = 0 ; b < BtagIndices.size() ; b++){

    if( c2.JetsAK8->at(i).DeltaR(c2.Jets->at(BtagIndices[b])) < 0.8 ){
      HiggsCand=true;
      break;
    }// end if 
  }// end loop over bjets

if( HiggsCand ){

    HiggsTags+=int(c2.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		   fabs(c2.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		   c2.JetsAK8_DeepMassDecorrelTagbbvsLight->at(i) > bbDiscThreshold &&
		   c2.JetsAK8_softDropMass->at(i) > 75 &&
		   c2.JetsAK8_softDropMass->at(i) < 140 );
  }else{

    WbosonTags+=int(c2.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		    fabs(c2.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		    c2.JetsAK8_DeepTagWvsQCD->at(i) > WDiscThreshold &&
		    c2.JetsAK8_softDropMass->at(i) > 65 &&
		    c2.JetsAK8_softDropMass->at(i) < 105 );
  }// end if-else block to check for Higgs or W candidates

}// end loop over AK8 jets 

 return HiggsTags >= MinHTag && HiggsTags <= MaxHTag && WbosonTags >= MinWTag && WbosonTags <= MaxWTag ;
  }

  if( file == 3 ){
  
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
 
for( int i = 0 ; i < c3.Jets->size(); i++){
  if( c3.Jets->at(i).Pt() > AK4PtThreshold &&
      fabs(c3.Jets->at(i).Eta()) < AK4EtaThreshold &&
       c3.Jets_bJetTagDeepCSVBvsAll->at(i) > bDiscThreshold ) BtagIndices.push_back(i);
}

if( BtagIndices.size() == 0 ) return false;


for( int i = 0 ; i < c3.JetsAK8->size() ; i++){

  bool HiggsCand=false;

  for( int b = 0 ; b < BtagIndices.size() ; b++){

    if( c3.JetsAK8->at(i).DeltaR(c3.Jets->at(BtagIndices[b])) < 0.8 ){
      HiggsCand=true;
      break;
    }// end if 
  }// end loop over bjets

if( HiggsCand ){

    HiggsTags+=int(c3.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		   fabs(c3.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		   c3.JetsAK8_DeepMassDecorrelTagbbvsLight->at(i) > bbDiscThreshold &&
		   c3.JetsAK8_softDropMass->at(i) > 75 &&
		   c3.JetsAK8_softDropMass->at(i) < 140 );
  }else{

    WbosonTags+=int(c3.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		    fabs(c3.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		    c3.JetsAK8_DeepTagWvsQCD->at(i) > WDiscThreshold &&
		    c3.JetsAK8_softDropMass->at(i) > 65 &&
		    c3.JetsAK8_softDropMass->at(i) < 105 );
  }// end if-else block to check for Higgs or W candidates

}// end loop over AK8 jets


 return HiggsTags >= MinHTag && HiggsTags <= MaxHTag && WbosonTags >= MinWTag && WbosonTags <= MaxWTag ;
  }
  if( file == 4 ){
  
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
 
for( int i = 0 ; i < c4.Jets->size(); i++){
  if( c4.Jets->at(i).Pt() > AK4PtThreshold &&
      fabs(c4.Jets->at(i).Eta()) < AK4EtaThreshold &&
       c4.Jets_bJetTagDeepCSVBvsAll->at(i) > bDiscThreshold ) BtagIndices.push_back(i);
}

if( BtagIndices.size() == 0 ) return false;


for( int i = 0 ; i < c4.JetsAK8->size() ; i++){

  bool HiggsCand=false;

  for( int b = 0 ; b < BtagIndices.size() ; b++){

    if( c4.JetsAK8->at(i).DeltaR(c4.Jets->at(BtagIndices[b])) < 0.8 ){
      HiggsCand=true;
      break;
    }// end if 
  }// end loop over bjets

if( HiggsCand ){

    HiggsTags+=int(c4.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		   fabs(c4.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		   c4.JetsAK8_DeepMassDecorrelTagbbvsLight->at(i) > bbDiscThreshold &&
		   c4.JetsAK8_softDropMass->at(i) > 75 &&
		   c4.JetsAK8_softDropMass->at(i) < 140 );
  }else{

    WbosonTags+=int(c4.JetsAK8->at(i).Pt() > AK8PtThreshold &&
		    fabs(c4.JetsAK8->at(i).Eta()) < AK8EtaThreshold &&
		    c4.JetsAK8_DeepTagWvsQCD->at(i) > WDiscThreshold &&
		    c4.JetsAK8_softDropMass->at(i) > 65 &&
		    c4.JetsAK8_softDropMass->at(i) < 105 );
  }// end if-else block to check for Higgs or W candidates

}// end loop over AK8 jets


 return HiggsTags >= MinHTag && HiggsTags <= MaxHTag && WbosonTags >= MinWTag && WbosonTags <= MaxWTag ;
  }
 else { return true; }

}

TLorentzVector METAdd(int file,int pdgid){
  TLorentzVector sum = {0,0,0,0};
   
   if(file == 1 ){
     for(int pdg = 0;pdg<c1.GenParticles_PdgId->size();pdg++){

       if( abs(c1.GenParticles_PdgId->at(pdg)) == pdgid  ){
	 //cout<<"FOUND!"<<endl;
	 sum += c1.GenParticles->at(pdg);
       
       }
     }
   }
   
  if(file == 2 ){
     for(int pdg = 0;pdg<c2.GenParticles_PdgId->size();pdg++){

       if( abs(c2.GenParticles_PdgId->at(pdg)) == pdgid ){
	 //cout<<"FOUND!"<<endl;
	 sum += c2.GenParticles->at(pdg);
       
       }
     }
   }

  if(file == 3 ){
     for(int pdg = 0;pdg<c3.GenParticles_PdgId->size();pdg++){

       if( abs(c3.GenParticles_PdgId->at(pdg)) == pdgid ){
	 //cout<<"FOUND!"<<endl;
	 sum += c3.GenParticles->at(pdg);
       
       }
     }
   }
  if(file == 4 ){
     for(int pdg = 0;pdg<c4.GenParticles_PdgId->size();pdg++){

       if( abs(c4.GenParticles_PdgId->at(pdg)) == pdgid ){
	 //cout<<"FOUND!"<<endl;
	 sum += c4.GenParticles->at(pdg);
       
       }
     }
   }
  else { return {0,0,0,0}; }

  return sum;
 }


void MET_DPHI(){


    TH1F* WH_MET = new TH1F("WH_MET",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET = new TH1F("W_MET",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET = new TH1F("H_MET",";MET;Events",24,-M_PI,M_PI);
    TH1F* WH_MET2 = new TH1F("WH_MET2",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET2 = new TH1F("W_MET2",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET2 = new TH1F("H_MET2",";MET;Events",24,-M_PI,M_PI);
    TH1F* WH_MET3 = new TH1F("WH_MET3",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET3 = new TH1F("W_MET3",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET3 = new TH1F("H_MET3",";MET;Events",24,-M_PI,M_PI);
    TH1F* WH_MET4 = new TH1F("WH_MET4",";MET;Events",24,-M_PI,M_PI);
    TH1F*  W_MET4 = new TH1F("W_MET4",";MET;Events",24,-M_PI,M_PI);
    TH1F*  H_MET4 = new TH1F("H_MET4",";MET;Events",24,-M_PI,M_PI);

      
//File 1***************************************
    for(int evt=0;evt<tr1->GetEntries();evt++){
      
    c1.GetEntry(evt);						   
      
    MET4.SetPtEtaPhiE(c1.MET,0,c1.METPhi,0);

    TLorentzVector ZMETSum = METAdd(1,24);
    double Z_1MET = MET4.DeltaPhi(ZMETSum);

    if(c1.Jets->size() == 0){ continue ; }
    
    if(c1.JetsAK8->size() == 0){ continue; }
      

    if( NVetos(1) && TrackVetos(1) && HTPTCut(1) && AK4JetsCut(1) && AK8JetsCut(1) && AK4DeltaPhiCut(1) && AK8DeltaPhiCut(1) && TwoAK8Jets(1) ){

      //WH SR
      if(WHTag(1,999,1,999,1)){ WH_MET->Fill(Z_1MET,WZBB5Weight); }
      
      //H SR
      if(WHTag(0,0,1,999,1)){ H_MET->Fill(Z_1MET,WZBB5Weight); }
      
      //W SR
      if(WHTag(1,999,0,0,1)){ W_MET->Fill(Z_1MET,WZBB5Weight);  }
      
       
      
     }//end if statement--------------------
    }//end for loop================================
  
    
//File 2****************************************
    for(int evt=0;evt<tr2->GetEntries();evt++){
      
    c2.GetEntry(evt);

    MET4.SetPtEtaPhiE(c2.MET,0,c2.METPhi,0);

    TLorentzVector Z2METSum = METAdd(2,24);
    double Z_2MET = MET4.DeltaPhi(Z2METSum);

    if(c2.Jets->size() == 0){ continue ; }
    
    if(c2.JetsAK8->size() == 0){ continue; }
      

    if( NVetos(2) && TrackVetos(2) && HTPTCut(2) && AK4JetsCut(2) && AK8JetsCut(2) && AK4DeltaPhiCut(2) && AK8DeltaPhiCut(2) && TwoAK8Jets(2) ){

      //WH SR
      if(WHTag(1,999,1,999,2)){ WH_MET2->Fill(Z_2MET,WZBB6Weight); }
      
      //H SR
      if(WHTag(0,0,1,999,2)){ H_MET2->Fill(Z_2MET,WZBB6Weight); }
      
      //W SR
      if(WHTag(1,999,0,0,2)){ W_MET2->Fill(Z_2MET,WZBB6Weight); }
      
       
      
     }//end if statement--------------------
    }//end for loop================================

    
//File 3****************************************
    for(int evt=0;evt<tr3->GetEntries();evt++){
      
    c3.GetEntry(evt);

    MET4.SetPtEtaPhiE(c3.MET,0,c3.METPhi,0);

    TLorentzVector Z3METSum = METAdd(3,24);
    double Z_3MET = MET4.DeltaPhi(Z3METSum);

    if(c3.Jets->size() == 0){ continue; }
    
    if(c3.JetsAK8->size() == 0){ continue; }
      

    if( NVetos(3) && TrackVetos(3) && HTPTCut(3) && AK4JetsCut(3) && AK8JetsCut(3) && AK4DeltaPhiCut(3) && AK8DeltaPhiCut(3) && TwoAK8Jets(3) ){

      //WH SR
      if(WHTag(1,999,1,999,3)){ WH_MET3->Fill(Z_3MET,WZBB7Weight); }
      
      //H SR
      if(WHTag(0,0,1,999,3)){ H_MET3->Fill(Z_3MET,WZBB7Weight); }
      
      //W SR
      if(WHTag(1,999,0,0,3)){ W_MET3->Fill(Z_3MET,WZBB7Weight); }
      
       
      
     }//end if statement--------------------
    }//end for loop================================

    
//File 4****************************************
    for(int evt=0;evt<tr4->GetEntries();evt++){
      
    c4.GetEntry(evt);

    MET4.SetPtEtaPhiE(c4.MET,0,c4.METPhi,0);

    TLorentzVector Z4METSum = METAdd(4,24);
    double Z_4MET = MET4.DeltaPhi(Z4METSum);

    if(c4.Jets->size() == 0){ continue ; }
    
    if(c4.JetsAK8->size() == 0){ continue; }
      

    if( NVetos(4) && TrackVetos(4) && HTPTCut(4) && AK4JetsCut(4) && AK8JetsCut(4) && AK4DeltaPhiCut(4) && AK8DeltaPhiCut(4) && TwoAK8Jets(4) ){

      //WH SR
      if(WHTag(1,999,1,999,4)){ WH_MET4->Fill(Z_4MET,WZBB9Weight); }
      
      //H SR
      if(WHTag(0,0,1,999,4)){ H_MET4->Fill(Z_4MET,WZBB9Weight); }
      
      //W SR
      if(WHTag(1,999,0,0,4)){ W_MET4->Fill(Z_4MET,WZBB9Weight); }
      
       
      
     }//end if statement--------------------
    }//end for loop================================

    //void HistPlot4(TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4, TString title,  TString label1, TString label2, TString label3, TString label4, TString OutFile, bool log=true)

    HistPlot4(H_MET4,H_MET3,H_MET2,H_MET,"H SR W_DPHI","CN925WZBB","CN750WZBB","CN600WZBB","CN500WZBB","4RWZBB_H_WDPHI.png",false);
    HistPlot4(W_MET4,W_MET3,W_MET2,W_MET,"W SR W_DPHI","CN925WZBB","CN750WZBB","CN600WZBB","CN500WZBB","4RWZBB_W_WDPHI.png",false);
    HistPlot4(WH_MET4,WH_MET3,WH_MET2,WH_MET,"WH SR W_DPHI","CN925WZBB","CN750WZBB","CN600WZBB","CN500WZBB","4RWZBB_WH_WDPHI.png",false);

    /* trf->WriteObject(WH_MET2, "CN 925 W_MET ZDPHI"); */
    /* trf->WriteObject(H_MET2, "CN 925 H_MET ZDPHI"); */
    /* trf->WriteObject(W_MET2, "CN 925 W_MET ZDPHI"); */
    /* trf->WriteObject(WH_MET3, "CN 600 WH_MET ZDPHI"); */
    /* trf->WriteObject(H_MET3, "CN 600 H_MET ZDPHI"); */
    /* trf->WriteObject(W_MET3, "CN 600 W_MET ZDPHI"); */
    /* trf->Close(); */
}




