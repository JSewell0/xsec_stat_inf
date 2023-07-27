#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <TGraph.h>
#include <TSpline.h>
#include <TCanvas.h>

using namespace std;

// Function to split a string into tokens based on a delimiter
vector<string> split(string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

TSpline3* file_process(string file_name){
    ifstream file1(file_name);  
    vector<double> col1_data;  // Vector to store the first column data
    vector<double> col2_data;  // Vector to store the second column data

    string line1;
    int count = 0;
    while (getline(file1, line1)) {
  
      vector<string> tokens1 = split(line1, ',');
  
        if (tokens1.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            col1_data.push_back(stod(tokens1[0]));
            col2_data.push_back(stod(tokens1[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries1 = col1_data.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray1 = new double[numEntries1];
    double* dynamicArray2 = new double[numEntries1];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i < numEntries1; ++i) {
        dynamicArray1[i] = col1_data[i];
        dynamicArray2[i] = col2_data[i];
    }

    TSpline3* spline1 = new TSpline3("spline1", dynamicArray1, dynamicArray2, numEntries1);
    
    return spline1;
   
}

//void graph_draw(TGraph* graph1, TString graph_title, TString x_title, TString y_title, TString out_file, TString option, TString last_on_canvas){
  
//TCanvas* canvas = new TCanvas("Xsection vs mu", "Xsection vs mu", 800, 800);
  //gPad->SetLogy();
  
  //graph1->Draw(option);
  //graph1->SetTitle(graph_title);
// graph1->GetXaxis()->SetTitle(x_title);
//  graph1->GetYaxis()->SetTitle(y_title);

// graph1->SetLineWidth(3);
// graph1->SetLineStyle(1);
// graph1->SetLineColor(kBlue-4);
// gPad->SetLogy();
//}

void graph_draw(TGraph* graph1, TString graph_title, TString x_title, TString y_title, int color, TString option,TString logscale,int linestyle){
  
  // TCanvas* canvas = new TCanvas("Rates vs #mu", "Rates vs #mu", 1200, 1200); 
  //gPad->SetLogy();
  
  graph1->Draw(option);
  graph1->SetTitle(graph_title);
  graph1->GetXaxis()->SetTitle(x_title);
  graph1->GetYaxis()->SetTitle(y_title);

  graph1->SetLineWidth(3);
  graph1->SetLineStyle(1);
  graph1->SetLineColor(color);
  if (logscale == "Yes")
    {gPad->SetLogy();}
  if (logscale == "No")
    {gPad->SetLogy(0);}
  graph1->SetLineStyle(linestyle);
}

//void spline_draw(TSpline3* spline1, TString graph_title, TString x_title, TString y_title, TString out_file){
  
//TCanvas* canvas = new TCanvas("Xsection vs mu", "Xsection vs mu", 800, 800);
  //gPad->SetLogy();
  
  //spline1->Draw("AL");
  //spline1->SetTitle(graph_title);
  //spline1->GetXaxis()->SetTitle(x_title);
  //spline1->GetYaxis()->SetTitle(y_title);

  //spline1->SetLineWidth(3);
  //spline1->SetLineStyle(1);
  //spline1->SetLineColor(kBlue-4);
  //gPad->SetLogy();
  //canvas->SaveAs(out_file);
  //delete canvas;
  
//}


  void Xsectiongraph4() {

  //file_process(string file_name)
  TSpline3* N2N3 = file_process("N2N3.csv");
  TSpline3* N2C1 = file_process("N2C1.csv");
  TSpline3* N3C1 = file_process("N3C1.csv");
  TSpline3* C1C1 = file_process("C1C1.csv");
  TSpline3* N2N1hpos = file_process("N2,N1h+mu.csv");
  TSpline3* N2N1hneg = file_process("N2,N1h-mu.csv");
  TSpline3* N2N1Zpos = file_process("N2,N1Z+mu.csv");
  TSpline3* N2N1Zneg = file_process("N2,N1Z-mu.csv");
  TSpline3* N3N1hpos = file_process("N3,N1h+mu.csv");
  TSpline3* N3N1hneg = file_process("N3,N1h-mu.csv");
  TSpline3* N3N1Zpos = file_process("N3,N1Z+mu.csv");
  TSpline3* N3N1Zneg = file_process("N3,N1Z-mu.csv");
  TSpline3* Mass1 = file_process("N1.csv");
  TSpline3* Mass2 = file_process("MassN2C1.csv");
  TSpline3* Mass3 = file_process("N3.csv");
  

  //spline_draw(N2N3,"N2N3","mu GEV","XSection","n2n3spline1.png");
  // spline_draw(N2C1,"N2C1","mu GEV","XSection","n2c1spline1.png");
  //spline_draw(N3C1,"N3C1","mu GEV","XSection","n3c1spline1.png");
  //spline_draw(C1C1,"C1C1","mu GEV","XSection","c1c1spline1.png");
  //spline_draw(N2N1hpos,"N2N1hpos","mu GEV","ratio","n2n1hpspline1.png");
  //spline_draw(N2N1hneg,"N2N1hneg","mu GEV","ratio","n2n1hnspline1.png");
  //spline_draw(N2N1Zpos,"N2N1Zpos","mu GEV","ratio","n2n1zpspline1.png");
  //spline_draw(N2N1Zneg,"N2N1zneg","mu GEV","ratio","n2n1znspline1.png");
  //spline_draw(N3N1hpos,"N3N1hpos","mu GEV","ratio","n3n1hpspline1.png");
  ///spline_draw(N3N1hneg,"N3N1hneg","mu GEV","ratio","n3n1hnspline1.png");
  //spline_draw(N3N1Zpos,"N3N1Zpos","mu GEV","ratio","n3n1zpspline1.png");
  // spline_draw(N3N1Zneg,"N3N1Zneg","mu GEV","ratio","n3n1znspline1.png");
  //spline_draw(Mass1,"N1 Mass","#mu GEV","mass GEV","1bN1mass.png");
  //spline_draw(Mass2,"N2/C1 Mass","mu GEV","mass GEV","1bN2C1mass.png");
  //spline_draw(Mass3,"N3 Mass","#mu GEV","mass Gev","1bN3mass.png");
  
  //define final state cross sections for pos and neg mu:
     int size1 = 20;
     double p1[size1]; //<-WZ+MET
     double p2[size1]; //<-Wh+MET
     double p3[size1]; //<-WW+MET
     double p4[size1]; //<-ZZ+MET
     double p5[size1]; //<-hZ+MET
     double p6[size1]; //<-hh+MET
     double n1[size1]; //<-WZ+MET
     double n2[size1]; //<-Wh+MET
     double n3[size1]; //<-WW+MET
     double n4[size1]; //<-ZZ+MET
     double n5[size1]; //<-hZ+MET
     double n6[size1]; //<-hh+MET
     double x[size1];
     double m1[size1];
     double m2[size1];
     double m3[size1];
     double yN2N3[size1];
     double yN2C1[size1];
     double yN3C1[size1];
     double yC1C1[size1];
     double yN2N1hpos[size1];
     double yN2N1hneg[size1];
     double yN2N1Zpos[size1];
     double yN2N1Zneg[size1];
     double yN3N1hpos[size1];
     double yN3N1hneg[size1];
     double yN3N1Zpos[size1];
     double yN3N1Zneg[size1];
     
     for (int i = 0; i < size1; i++)
      {
	int j = i * 25 + 325;
	x[i] = j;
	
	yN2N3[i] = N2N3->Eval(j);
	yN2C1[i] = N2C1->Eval(j);
	yN3C1[i] = N3C1->Eval(j);
	yC1C1[i] = C1C1->Eval(j);
	yN2N1hpos[i] = N2N1hpos->Eval(j);
	yN2N1hneg[i] = N2N1hneg->Eval(j);
	yN2N1Zpos[i] = N2N1Zpos->Eval(j);
	yN2N1Zneg[i] = N2N1Zneg->Eval(j);
	yN3N1hpos[i] = N3N1hpos->Eval(j);
	yN3N1hneg[i] = N3N1hneg->Eval(j);
	yN3N1Zpos[i] = N3N1Zpos->Eval(j);
	yN3N1Zneg[i] = N3N1Zneg->Eval(j);
	m1[i] = Mass1->Eval(j);
	m2[i] = Mass2->Eval(j);
	m3[i] = Mass3->Eval(j);

	//if (i==0)
	// {cout<<"mu, WZ+, WZ-, Wh+, Wh-, WW, ZZ+, ZZ-, hZ+, hZ-, hh+, hh-, mass"<<endl;}
	// cout<<"yN2N3: "<<yN2N3<<endl;
	// cout<<"yN2C1: "<<yN2C1<<endl;
	// cout<<"yN3C1: "<<yN3C1<<endl;
	// cout<<"yC1C1: "<<yC1C1<<endl;
	// cout<<"yN2N1hpos: "<<yN2N1hpos<<endl;
	// cout<<"yN2N1hneg: "<<yN2N1hneg<<endl;
	// cout<<"yN2N1Zpos: "<<yN2N1Zpos<<endl;
	// cout<<"yN2N1Zneg: "<<yN2N1Zneg<<endl;
	// cout<<"yN3N1hpos: "<<yN3N1hpos<<endl;
	// cout<<"yN3N1hneg: "<<yN3N1hneg<<endl;
	// cout<<"yN3N1Zpos: "<<yN3N1Zpos<<endl;
	// cout<<"yN3N1Zneg: "<<yN3N1Zneg<<endl<<endl;
	
	p1[i] = yN2C1[i] * yN2N1Zpos[i] + yN3C1[i] * yN3N1Zpos[i];
	p2[i] = yN2C1[i] * yN2N1hpos[i] + yN3C1[i] * yN3N1hpos[i];
	p3[i] = yC1C1[i];
	p4[i] = yN2N3[i] * yN2N1Zpos[i] * yN3N1Zpos[i];
	p5[i] = yN2N3[i] * yN2N1Zpos[i] * yN3N1hpos[i] + yN2N3[i] * yN2N1hpos[i] * yN3N1Zpos[i];
	p6[i] = yN2N3[i] * yN2N1hpos[i] * yN3N1hpos[i];

	n1[i] = yN2C1[i] * yN2N1Zneg[i] + yN3C1[i] * yN3N1Zneg[i];
	n2[i] = yN2C1[i] * yN2N1hneg[i] + yN3C1[i] * yN3N1hneg[i];
	n3[i] = yC1C1[i];
	n4[i] = yN2N3[i] * yN2N1Zneg[i] * yN3N1Zneg[i];
	n5[i] = yN2N3[i] * yN2N1Zneg[i] * yN3N1hneg[i] + yN2N3[i] * yN2N1hneg[i] * yN3N1Zneg[i];
	n6[i] = yN2N3[i] * yN2N1hneg[i] * yN3N1hneg[i];
	
	//	cout<<j<<", "<<p1[i]<<", "<<n1[i]<<", "<<p2[i]<<", "<<n2[i]<<", "<<p3[i]<<", "<<p4[i]<<", "<<n4[i]<<", "<<p5[i]<<", "<<n5[i]<<", "<<p6[i]<<", "<<n6[i]<<", "<<mass<<endl;

      }

    TCanvas* canvas = new TCanvas("Rates vs #mu", "Rates vs #mu", 1200, 1200);
    TGraph* WZp = new TGraph(size1, x, p1);
    TGraph* Whp = new TGraph(size1, x, p2);
    TGraph* WWp = new TGraph(size1, x, p3);
    TGraph* ZZp = new TGraph(size1, x, p4);
    TGraph* hZp = new TGraph(size1, x, p5);
    TGraph* hhp = new TGraph(size1, x, p6);
    TGraph* WZn = new TGraph(size1, x, n1);
    TGraph* Whn = new TGraph(size1, x, n2);
    TGraph* WWn = new TGraph(size1, x, n3);
    TGraph* ZZn = new TGraph(size1, x, n4);
    TGraph* hZn = new TGraph(size1, x, n5);
    TGraph* hhn = new TGraph(size1, x, n6);
    TGraph* N1 = new TGraph(size1, x,  m1);
    TGraph* N2C1m = new TGraph(size1, x, m2);
    TGraph* N3 = new TGraph(size1, x, m3);
    TGraph* N2N3pp = new TGraph(size1, x, yN2N3);
    TGraph* N2C1pp = new TGraph(size1, x, yN2C1);
    TGraph* N3C1pp = new TGraph(size1, x, yN3C1);
    TGraph* C1C1pp = new TGraph(size1, x, yC1C1);
    TGraph* N2N1hpbr = new TGraph(size1, x, yN2N1hpos);
    TGraph* N2N1hnbr = new TGraph(size1, x, yN2N1hneg);
    TGraph* N2N1Zpbr = new TGraph(size1, x, yN2N1Zpos);
    TGraph* N2N1Znbr = new TGraph(size1, x, yN2N1Zneg);
    TGraph* N3N1hpbr = new TGraph(size1, x, yN3N1hpos);
    TGraph* N3N1hnbr = new TGraph(size1, x, yN3N1hneg);
    TGraph* N3N1Zpbr = new TGraph(size1, x, yN3N1Zpos);
    TGraph* N3N1Znbr = new TGraph(size1, x, yN3N1Zneg); 
    

    //graph_draw(TGraph* graph1,TString graph_title,TString x_title,TString y_title,TString out_file)    
    graph_draw(WZp,"WZ+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",30,"AP","Yes",1);
    graph_draw(Whp,"Wh+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",36,"P","Yes",1);
    graph_draw(WWp,"WW+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",38,"P","Yes",1);
    graph_draw(ZZp,"ZZ+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",41,"P","Yes",1);
    graph_draw(hZp,"hZ+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",44,"P","Yes",1);
    graph_draw(hhp,"hh+MET (#mu > 0)","#mu mass [GEV]","Effective Rate [pb]",46,"P","Yes",1);
    graph_draw(WZn,"WZ+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",30,"AP","Yes",2);
    graph_draw(Whn,"Wh+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",36,"P","Yes",2);
    graph_draw(WWn,"WW+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",38,"P","Yes",2);
    graph_draw(ZZn,"ZZ+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",41,"P","Yes",2);
    graph_draw(hZn,"hZ+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",44,"P","Yes",2);
    graph_draw(hhn,"hh+MET (#mu < 0)","#mu mass [GEV]","Effective Rate [pb]",46,"P","Yes",2);
    
    graph_draw(N2N3pp,"N2N3 XSection","mu mass [GEV]","Cross Section [pb]",30,"AP","Yes",1);
    graph_draw(N2C1pp,"N2C1 XSection","mu mass [GEV]","Cross Section [pb]",36,"P","Yes",1);
    graph_draw(N3C1pp,"N3C1 XSection","mu mass [GEV]","Cross Section [pb]",38,"P","Yes",1);
    graph_draw(C1C1pp,"C1C1 XSection","mu mass [GEV]","Cross Section [pb]",41,"P","Yes",1);

    graph_draw(N2N1hpbr,"N2-> N1 + h (#mu > 0)","mu mass [GEV]","branching ratio",30,"AP","Yes",1);
    graph_draw(N2N1hnbr,"N2-> N1 + h (#mu < 0)","mu mass [GEV]","branching ratio",30,"P","Yes",2);
    graph_draw(N2N1Zpbr,"N2-> N1 + Z (#mu > 0)","mu mass [GEV]","branching ratio",38,"P","Yes",1);
    graph_draw(N2N1Znbr,"N2-> N1 + Z (#mu < 0)","mu mass [GEV]","branching ratio",38,"P","Yes",2);
    graph_draw(N3N1hpbr,"N3-> N1 + h (#mu > 0)","mu mass [GEV]","branching ratio",30,"AP","Yes",1);
    graph_draw(N3N1hnbr,"N3-> N1 + h (#mu < 0)","mu mass [GEV]","branching ratio",30,"P","Yes",2);
    graph_draw(N3N1Zpbr,"N3-> N1 + Z (#mu > 0)","mu mass [GEV]","branching ratio",38,"P","Yes",1);
    graph_draw(N3N1Znbr,"N3-> N1 + Z (#mu < 0)","mu mass [GEV]","branching ratio",38,"P","Yes",2);

    TMultiGraph* pprate = new TMultiGraph();
    pprate->SetTitle("Model 1b Pair Production Cross Sections vs #mu;#mu mass [GEV];Cross Section [pb]");
    pprate->Add(N2N3pp);
    pprate->Add(N2C1pp);
    pprate->Add(N3C1pp);
    pprate->Add(C1C1pp);
    pprate->Draw("apl");
    canvas->BuildLegend();
    canvas->SetGrid();
    canvas->SaveAs("1bppXsections.png");


    TMultiGraph* n2br = new TMultiGraph();
    n2br->SetTitle("Model 1b N2 Branching Ratios vs #mu;#mu mass [GEV];Branching Ratio [%]");
    n2br->Add(N2N1hpbr);
    n2br->Add(N2N1Zpbr);
    n2br->Add(N2N1hnbr);
    n2br->Add(N2N1Znbr);
    n2br->GetYaxis()->SetRangeUser(.01,1);
    n2br->Draw("apl");
    canvas->BuildLegend();	
    canvas->SetGrid();
    canvas->SaveAs("1bN2br.png");


    TMultiGraph* n3br = new TMultiGraph();
    n3br->SetTitle("Model 1b N3 Branching Ratios vs #mu;#mu mass [GEV];Branching Ratio [%]");
    n3br->Add(N3N1hpbr);
    n3br->Add(N3N1Zpbr);
    n3br->Add(N3N1hnbr);
    n3br->Add(N3N1Znbr);
    n3br->GetYaxis()->SetRangeUser(.01,1);
    n3br->Draw("apl");
    canvas->BuildLegend();	
    canvas->SetGrid();
    canvas->SaveAs("1bN3br.png");

    TMultiGraph* prates = new TMultiGraph();
    prates->SetTitle("Model 1b Final State Rates (#mu > 0) vs #mu;#mu mass [GEV];Effective Rate [pb]");
    prates->Add(WZp);
    prates->Add(Whp);
    prates->Add(WWp);
    prates->Add(ZZp);
    prates->Add(hZp);
    prates->Add(hhp);
    prates->Draw("apl");
    canvas->BuildLegend();
    canvas->SetGrid();
    canvas->SaveAs("1bprates.png");
    //delete canvas;
    //TCanvas* canvas = new TCanvas("Rates vs #mu", "Rates vs #mu", 1200, 1200);
    TMultiGraph* nrates = new TMultiGraph();
    nrates->SetTitle("Model 1b Final State Rates (#mu < 0) vs #mu;#mu mass [GEV];Effective Rate [pb]");
    nrates->Add(WZn);
    nrates->Add(Whn);
    nrates->Add(WWn);
    nrates->Add(ZZn);
    nrates->Add(hZn);
    nrates->Add(hhn);
    nrates->Draw("apl");
    canvas->SetGrid();
    canvas->BuildLegend();
    canvas->SaveAs("1bnrates.png");
    //    delete canvas;
    TMultiGraph* trates = new TMultiGraph();
    trates->SetTitle("Model 1b Final State Rates vs #mu;#mu mass [GEV];Effective Rate [pb]");
    trates->Add(WZp);
    trates->Add(Whp);
    trates->Add(WWp);
    trates->Add(ZZp);
    trates->Add(hZp);
    trates->Add(hhp);
    trates->Add(WZn);
    trates->Add(Whn);
    trates->Add(WWn);
    trates->Add(ZZn);
    trates->Add(hZn);
    trates->Add(hhn);
    trates->Draw("apl");
    canvas->SetGrid();
    canvas->BuildLegend();
    canvas->SaveAs("1brates.png");
    
    //    TCanvas* canvas = new TCanvas("Mass vs #mu", "Mass vs #mu", 1200, 1200);
    graph_draw(N1,"N1 Mass","#mu mass [GEV]","#chi mass [GEV]",46,"AL","No", 1);
    graph_draw(N2C1m,"N2C1 Mass","#mu mass [GEV]","#chi mass [GEV]",38,"L","No",1);
    graph_draw(N3,"N3 Mass","#mu mass [GEV]","#chi mass [GEV]",30,"L","No",1);
    TMultiGraph* mass = new TMultiGraph();
    mass->SetTitle("Model 1b SUSY Mass vs #mu;#mu mass [GEV];#chi mass [GEV]");
    mass->Add(N1);
    mass->Add(N2C1m);
    mass->Add(N3);
    mass->Draw("apl");
    canvas->BuildLegend();
    canvas->SaveAs("1bmasses.png");
    canvas->SetGrid();
    delete canvas;
    

   
    //  return 0;
 }
  
