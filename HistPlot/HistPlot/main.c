TString inFileName ="/Users/jsewell/Documents/ROOT_documents/Autumn18Fast.NiramaySUSY_CN925_sgino100_sget90_sgetBB_7_RA2AnalysisTree.root";


void HistPlot()
{
  // Open the root file
  TFile* tf = new TFile(inFileName,"r");

  // look for a TTree object in the root file
  TTree* tr = (TTree*) tf->Get("TreeMaker2/PreSelection");

  // Define variables which will store the values read from the root file
  Int_t Julian_MET;                  // This will store a single float value per event read
  vector<int>* Julian_TriggerPrescales{0};      // This will store a std::vector of integers per event read

  // declare which branches to read, and where to store the data read
  tr->SetBranchAddress("MET",&Julian_MET);
  tr->SetBranchAddress("TriggerPrescales",&Julian_TriggerPrescales);

  // Read each event
  for(int evt=0;evt<tr->GetEntries();evt++){
    tr->GetEntry(evt);          // This will read evt'th entry, and store the data
    // print event number, MET, and size of TriggerPrescales vector
    
  }
}


