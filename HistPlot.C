TString inFileName ="/Users/jsewell/Documents/ROOT_documents/Autumn18Fast.NiramaySUSY_CN925_sgino100_sget90_sgetBB_7_RA2AnalysisTree.root";


void HistPlot()
{
  // Open the root file
  TFile* tf = new TFile(inFileName,"r");

  // look for a TTree object in the root file
  TTree* tr = (TTree*) tf->Get("TreeMaker2/PreSelection");

  // Define variables which will store the values read from the root file
  Int_t EvtVal;                  // This will store a single float value per event read
  vector<int>* TriggerPrescales{0};      // This will store a std::vector of integers per event read
  
  TString Leaf = "NMuons";

  TCanvas* tc = new TCanvas("aa","bb",800,600); 
  TH1F* h1 = new TH1F("h1","title",10,0,10);
  
  // declare which branches to read, and where to store the data read
  tr->SetBranchAddress(Leaf,&EvtVal);
  tr->SetBranchAddress("TriggerPrescales",&TriggerPrescales);

  // Read each event
  for(int evt=0;evt<tr->GetEntries();evt++){
    tr->GetEntry(evt);          // This will read evt'th entry, and store the data
  
    h1->Fill(EvtVal);        
  
  }
  
  h1->Draw();

  h1->SetTitle(Leaf );
  h1->SetLineColor(kViolet+5);
  h1->SetLineWidth(2);
  
  tc->SetGrid();
  tc->SaveAs(Leaf+".png");
  delete tc;
}



