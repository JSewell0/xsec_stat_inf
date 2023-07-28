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

TSpline5* file_process(string file_name){
    ifstream file1(file_name);  

    vector<double> col1_data;  // Vector to store the first column data
    vector<double> col2_data;  // Vector to store the second column data

    string line1;
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

    TSpline5* spline1 = new TSpline5("spline1", dynamicArray1, dynamicArray2, numEntries1);

    return spline1;
   
}

void graph_draw(TGraph* graph1, TString graph_title, TString x_title, TString y_title, TString out_file){
  
  TCanvas* canvas = new TCanvas("Xsection vs mu", "Xsection vs mu", 800, 800);
  //gPad->SetLogy();
  
  graph1->Draw("AL");
  graph1->SetTitle(graph_title);
  //graph1->GetXaxis()->SetTitle(x_title);
  //graph1->GetYaxis()->SetTitle(y_title);

  graph1->SetLineWidth(3);
  graph1->SetLineStyle(1);
  graph1->SetLineColor(kBlue-4);
  gPad->SetLogy(0);
  canvas->SaveAs(out_file);
  delete canvas;
  
}

void spline_draw(TSpline5* spline1, TString graph_title, TString x_title, TString y_title, TString out_file){
  
  TCanvas* canvas = new TCanvas("Xsection vs mu", "Xsection vs mu", 800, 800);
  //gPad->SetLogy();
  
  spline1->Draw("AL");
  // spline1->SetTitle(graph_title);
  //spline1->GetXaxis()->SetTitle(x_title);
  //spline1->GetYaxis()->SetTitle(y_title);

  spline1->SetLineWidth(3);
  spline1->SetLineStyle(1);
  spline1->SetLineColor(kBlue-4);
  gPad->SetLogy();
  canvas->SaveAs(out_file);
  delete canvas;
  
}


int main(int argc,char **argv) {

  //file_process(string file_name)
  TSpline5* N2N3 = file_process("N2N3.csv");
  TSpline5* N2C1 = file_process("N2C1.csv");
  TSpline5* N3C1 = file_process("N3C1.csv");
  TSpline5* C1C1 = file_process("C1C1.csv");
  TSpline5* N2N1hpos = file_process("N2,N1h+mu.csv");
  TSpline5* N2N1hneg = file_process("N2,N1h-mu.csv");
  TSpline5* N2N1Zpos = file_process("N2,N1Z+mu.csv");
  TSpline5* N2N1Zneg = file_process("N2,N1Z-mu.csv");
  TSpline5* N3N1hpos = file_process("N3,N1h+mu.csv");
  TSpline5* N3N1hneg = file_process("N3,N1h-mu.csv");
  TSpline5* N3N1Zpos = file_process("N3,N1Z+mu.csv");
  TSpline5* N3N1Zneg = file_process("N3,N1Z-mu.csv");


  spline_draw(N2N3,"N2N3","mu GEV","XSection","n2n3spline1.png");
  spline_draw(N2C1,"N2C1","mu GEV","XSection","n2c1spline1.png");
  spline_draw(N3C1,"N3C1","mu GEV","XSection","n3c1spline1.png");
  spline_draw(C1C1,"C1C1","mu GEV","XSection","c1c1spline1.png");
  spline_draw(N2N1hpos,"N2N1hpos","mu GEV","ratio","n2n1hpspline1.png");
  spline_draw(N2N1hneg,"N2N1hneg","mu GEV","ratio","n2n1hnspline1.png");
  spline_draw(N2N1Zpos,"N2N1Zpos","mu GEV","ratio","n2n1zpspline1.png");
  spline_draw(N2N1Zneg,"N2N1zneg","mu GEV","ratio","n2n1znspline1.png");
  spline_draw(N3N1hpos,"N3N1hpos","mu GEV","ratio","n3n1hpspline1.png");
  spline_draw(N3N1hneg,"N3N1hneg","mu GEV","ratio","n3n1hnspline1.png");
  spline_draw(N3N1Zpos,"N3N1Zpos","mu GEV","ratio","n3n1zpspline1.png");
  spline_draw(N3N1Zneg,"N3N1Zneg","mu GEV","ratio","n3n1znspline1.png");
  
  //define final state cross sections for pos and neg mu:
    int size1 = 22;
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
     
     
     for (int i = 0; i < size1; i++)
      {
	int j = i * 25 + 250;
	x[i] = j;
	
	double yN2N3 = N2N3->Eval(j);
	double yN2C1 = N2C1->Eval(j);
	double yN3C1 = N3C1->Eval(j);
	double yC1C1 = C1C1->Eval(j);
	double yN2N1hpos = N2N1hpos->Eval(j);
	double yN2N1hneg = N2N1hneg->Eval(j);
	double yN2N1Zpos = N2N1Zpos->Eval(j);
	double yN2N1Zneg = N2N1Zneg->Eval(j);
	double yN3N1hpos = N3N1hpos->Eval(j);
	double yN3N1hneg = N3N1hneg->Eval(j);
	double yN3N1Zpos = N3N1Zpos->Eval(j);
	double yN3N1Zneg = N3N1Zneg->Eval(j);

	// cout<<j<<endl;
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
	
	p1[i] = yN2C1 * yN2N1Zpos + yN3C1 * yN3N1Zpos;
	p2[i] = yN2C1 * yN2N1hpos + yN3C1 * yN3N1hpos;
	p3[i] = yC1C1;
	p4[i] = yN2N3 * yN2N1Zpos * yN3N1Zpos;
	p5[i] = yN2N3 * yN2N1Zpos * yN3N1hpos + yN2N3 * yN2N1hpos * yN3N1Zpos;
	p6[i] = yN2N3 * yN2N1hpos * yN3N1hpos;

	n1[i] = yN2C1 * yN2N1Zneg + yN3C1 * yN3N1Zneg;
	n2[i] = yN2C1 * yN2N1hneg + yN3C1 * yN3N1hneg;
	n3[i] = yC1C1;
	n4[i] = yN2N3 * yN2N1Zneg * yN3N1Zneg;
	n5[i] = yN2N3 * yN2N1Zneg * yN3N1hneg + yN2N3 * yN2N1hneg * yN3N1Zneg;
	n6[i] = yN2N3 * yN2N1hneg * yN3N1hneg;

      }

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

    //graph_draw(TGraph* graph1,TString graph_title,TString x_title,TString y_title,TString out_file)    
    graph_draw(WZp,"WZ+MET+mu","mu GEV","XSection","WZ+mu1.png");
    graph_draw(Whp,"Wh+MET+mu","mu GEV","XSection","Wh+mu1.png");
    graph_draw(WWp,"WW+MET+mu","mu GEV","XSection","WW+mu1.png");
    graph_draw(ZZp,"ZZ+MET+mu","mu GEV","XSection","ZZ+mu1.png");
    graph_draw(hZp,"hZ+MET+mu","mu GEV","XSection","hZ+mu1.png");
    graph_draw(hhp,"hh+MET+mu","mu GEV","XSection","hh+mu1.png");
    graph_draw(WZn,"WZ+MET-mu","mu GEV","XSection","WZ-mu1.png");
    graph_draw(Whn,"Wh+MET-mu","mu GEV","XSection","Wh-mu1.png");
    graph_draw(WWn,"WW+MET-mu","mu GEV","XSection","WW-mu1.png");
    graph_draw(ZZn,"ZZ+MET-mu","mu GEV","XSection","ZZ-mu1.png");
    graph_draw(hZn,"hZ+MET-mu","mu GEV","XSection","hZ-mu1.png");
    graph_draw(hhn,"hh+MET-mu","mu GEV","XSection","hh-mu1.png");


    return 0;
 }
