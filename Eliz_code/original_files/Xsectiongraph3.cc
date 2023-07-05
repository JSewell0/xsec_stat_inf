#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <TGraph.h>
#include <TSpline.h>
#include <TCanvas.h>

// Function to split a string into tokens based on a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
  
    std::ifstream file1("N2N3.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2N31;  // Vector to store the first column data
    std::vector<double> N2N32;  // Vector to store the second column data

    std::string line1;
    while (getline(file1, line1)) {
        std::vector<std::string> tokens1 = split(line1, ',');
        if (tokens1.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2N31.push_back(std::stod(tokens1[0]));
            N2N32.push_back(std::stod(tokens1[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries1 = N2N31.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray1 = new double[numEntries1];
    double* dynamicArray2 = new double[numEntries1];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i < numEntries1; ++i) {
        dynamicArray1[i] = N2N31[i];
        dynamicArray2[i] = N2N32[i];
    }
    TGraph* test1 = new TGraph(numEntries1, dynamicArray1, dynamicArray2);
    TCanvas* canvas1 = new TCanvas("1Xsection vs mu", "1Xsection vs mu", 800, 800);

    test1->Draw("AP");
    canvas1->SaveAs("test1.png");

    TSpline3* N2N3 = new TSpline3("spline1", &dynamicArray1[10], &dynamicArray2[10], numEntries1);
    N2N3->Draw("AP");
    canvas1->SaveAs("test2.png");
      // Deallocate the dynamic arrays
    //delete[] dynamicArray1;
    //delete[] dynamicArray2;

    std::ifstream file2("N2C1.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2C11;  // Vector to store the first column data
    std::vector<double> N2C12;  // Vector to store the second column data

    std::string line2;
    while (getline(file2, line2)) {
        std::vector<std::string> tokens2 = split(line2, ',');
        if (tokens2.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2C11.push_back(std::stod(tokens2[0]));
            N2C12.push_back(std::stod(tokens2[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries2 = N2C11.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray3 = new double[numEntries2];
    double* dynamicArray4 = new double[numEntries2];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries2; ++i) {
        dynamicArray3[i] = N2C11[i];
        dynamicArray4[i] = N2C12[i];
    }
    
    TSpline3* N2C1 = new TSpline3("spline2", &dynamicArray3[0], &dynamicArray4[0], numEntries2);
    // Deallocate the dynamic arrays
    // delete[] dynamicArray3;
    //delete[] dynamicArray4;

    std::ifstream file3("N3C1.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N3C11;  // Vector to store the first column data
    std::vector<double> N3C12;  // Vector to store the second column data

    std::string line3;
    while (getline(file3, line3)) {
        std::vector<std::string> tokens3 = split(line3, ',');
        if (tokens3.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N3C11.push_back(std::stod(tokens3[0]));
            N3C12.push_back(std::stod(tokens3[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries3 = N3C11.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray5 = new double[numEntries3];
    double* dynamicArray6 = new double[numEntries3];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries3; ++i) {
        dynamicArray5[i] = N3C11[i];
        dynamicArray6[i] = N3C12[i];
    }
    
    TSpline3* N3C1 = new TSpline3("spline3", &dynamicArray5[10], &dynamicArray6[10], numEntries3);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray5;
    //delete[] dynamicArray6;

     std::ifstream file4("C1C1.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> C1C11;  // Vector to store the first column data
    std::vector<double> C1C12;  // Vector to store the second column data

    std::string line4;
    while (getline(file4, line4)) {
        std::vector<std::string> tokens4 = split(line4, ',');
        if (tokens4.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            C1C11.push_back(std::stod(tokens4[0]));
            C1C12.push_back(std::stod(tokens4[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries4 = C1C11.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray7 = new double[numEntries4];
    double* dynamicArray8 = new double[numEntries4];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries4; ++i) {
        dynamicArray7[i] = C1C11[i];
        dynamicArray8[i] = C1C12[i];
    }
    
    TSpline3* C1C1 = new TSpline3("spline4", &dynamicArray7[10], &dynamicArray8[10], numEntries4);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray7;
    //delete[] dynamicArray8;

    std::ifstream file5("N2,N1h+mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2N1hpos1;  // Vector to store the first column data
    std::vector<double> N2N1hpos2;  // Vector to store the second column data

    std::string line5;
    while (getline(file5, line5)) {
        std::vector<std::string> tokens5 = split(line5, ',');
        if (tokens5.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2N1hpos1.push_back(std::stod(tokens5[0]));
            N2N1hpos2.push_back(std::stod(tokens5[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries5 = N2N1hpos1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray9 = new double[numEntries5];
    double* dynamicArray10 = new double[numEntries5];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries5; ++i) {
        dynamicArray9[i] = N2N1hpos1[i];
        dynamicArray10[i] = N2N1hpos2[i];
    }
    
    TSpline3* N2N1hpos = new TSpline3("spline5", &dynamicArray9[10], &dynamicArray10[10], numEntries5);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray9;
    //delete[] dynamicArray10;

    std::ifstream file6("N2,N1h-mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2N1hneg1;  // Vector to store the first column data
    std::vector<double> N2N1hneg2;  // Vector to store the second column data

    std::string line6;
    while (getline(file6, line6)) {
        std::vector<std::string> tokens6 = split(line6, ',');
        if (tokens6.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2N1hneg1.push_back(std::stod(tokens6[0]));
            N2N1hneg2.push_back(std::stod(tokens6[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries6 = N2N1hneg1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray11 = new double[numEntries6];
    double* dynamicArray12 = new double[numEntries6];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries6; ++i) {
        dynamicArray11[i] = N2N1hneg1[i];
        dynamicArray12[i] = N2N1hneg2[i];
    }
    
    TSpline3* N2N1hneg = new TSpline3("spline6", &dynamicArray11[10], &dynamicArray12[10], numEntries6);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray11;
    //delete[] dynamicArray12;


    std::ifstream file7("N2,N1Z+mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2N1Zpos1;  // Vector to store the first column data
    std::vector<double> N2N1Zpos2;  // Vector to store the second column data

    std::string line7;
    while (getline(file7, line7)) {
        std::vector<std::string> tokens7 = split(line7, ',');
        if (tokens7.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2N1Zpos1.push_back(std::stod(tokens7[0]));
            N2N1Zpos2.push_back(std::stod(tokens7[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries7 = N2N1Zpos1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray13 = new double[numEntries7];
    double* dynamicArray14 = new double[numEntries7];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries7; ++i) {
        dynamicArray13[i] = N2N1Zpos1[i];
        dynamicArray14[i] = N2N1Zpos2[i];
    }
    
    TSpline3* N2N1Zpos = new TSpline3("spline7", &dynamicArray13[10], &dynamicArray14[10], numEntries7);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray13;
    //delete[] dynamicArray14;



    std::ifstream file8("N2,N1Z-mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N2N1Zneg1;  // Vector to store the first column data
    std::vector<double> N2N1Zneg2;  // Vector to store the second column data

    std::string line8;
    while (getline(file8, line8)) {
        std::vector<std::string> tokens8 = split(line8, ',');
        if (tokens8.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N2N1Zneg1.push_back(std::stod(tokens8[0]));
            N2N1Zneg2.push_back(std::stod(tokens8[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries8 = N2N1Zneg1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray15 = new double[numEntries8];
    double* dynamicArray16 = new double[numEntries8];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries8; ++i) {
        dynamicArray15[i] = N2N1Zneg1[i];
        dynamicArray16[i] = N2N1Zneg2[i];
    }
    
    TSpline3* N2N1Zneg = new TSpline3("spline8", &dynamicArray15[0], &dynamicArray16[0], numEntries8);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray15;
    //delete[] dynamicArray16;


    std::ifstream file9("N3,N1h+mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N3N1hpos1;  // Vector to store the first column data
    std::vector<double> N3N1hpos2;  // Vector to store the second column data

    std::string line9;
    while (getline(file9, line9)) {
        std::vector<std::string> tokens9 = split(line9, ',');
        if (tokens9.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N3N1hpos1.push_back(std::stod(tokens9[0]));
            N3N1hpos2.push_back(std::stod(tokens9[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries9 = N3N1hpos1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray17 = new double[numEntries9];
    double* dynamicArray18 = new double[numEntries9];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries9; ++i) {
        dynamicArray17[i] = N3N1hpos1[i];
        dynamicArray18[i] = N3N1hpos2[i];
    }
    
    TSpline3* N3N1hpos = new TSpline3("spline9", &dynamicArray17[10], &dynamicArray18[10], numEntries9);
    // Deallocate the dynamic arrays
    // delete[] dynamicArray17;
    //delete[] dynamicArray18;


    std::ifstream file10("N3,N1h-mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N3N1hneg1;  // Vector to store the first column data
    std::vector<double> N3N1hneg2;  // Vector to store the second column data

    std::string line10;
    while (getline(file10, line10)) {
        std::vector<std::string> tokens10 = split(line10, ',');
        if (tokens10.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N3N1hneg1.push_back(std::stod(tokens10[0]));
            N3N1hneg2.push_back(std::stod(tokens10[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries10 = N3N1hneg1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray19 = new double[numEntries10];
    double* dynamicArray20 = new double[numEntries10];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries10; ++i) {
        dynamicArray19[i] = N3N1hneg1[i];
        dynamicArray20[i] = N3N1hneg2[i];
    }
    
    TSpline3* N3N1hneg = new TSpline3("spline10", &dynamicArray19[10], &dynamicArray20[10], numEntries10);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray19;
    //delete[] dynamicArray20;

    std::ifstream file11("N3,N1Z+mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N3N1Zpos1;  // Vector to store the first column data
    std::vector<double> N3N1Zpos2;  // Vector to store the second column data

    std::string line11;
    while (getline(file11, line11)) {
        std::vector<std::string> tokens11 = split(line11, ',');
        if (tokens11.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N3N1Zpos1.push_back(std::stod(tokens11[0]));
            N3N1Zpos2.push_back(std::stod(tokens11[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries11 = N3N1Zpos1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray21 = new double[numEntries11];
    double* dynamicArray22 = new double[numEntries11];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries11; ++i) {
        dynamicArray21[i] = N3N1Zpos1[i];
        dynamicArray22[i] = N3N1Zpos2[i];
    }
    
    TSpline3* N3N1Zpos = new TSpline3("spline11", &dynamicArray21[10], &dynamicArray22[10], numEntries11);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray21;
    //delete[] dynamicArray22;

        std::ifstream file12("N3,N1Z-mu.csv");  // Replace "data.csv" with the path to your CSV file

    std::vector<double> N3N1Zneg1;  // Vector to store the first column data
    std::vector<double> N3N1Zneg2;  // Vector to store the second column data

    std::string line12;
    while (getline(file12, line12)) {
        std::vector<std::string> tokens12 = split(line12, ',');
        if (tokens12.size() >= 2) {
            // Convert each token to double and store in the respective arrays
            N3N1Zneg1.push_back(std::stod(tokens12[0]));
            N3N1Zneg2.push_back(std::stod(tokens12[1]));
        }
    }

    // Determine the number of entries
    size_t numEntries12 = N3N1Zneg1.size();

    // Create dynamic arrays based on the number of entries
    double* dynamicArray23 = new double[numEntries12];
    double* dynamicArray24 = new double[numEntries12];

    // Copy the data from the vectors to the dynamic arrays
    for (size_t i = 0; i > numEntries12; ++i) {
        dynamicArray23[i] = N3N1Zneg1[i];
        dynamicArray24[i] = N3N1Zneg2[i];
    }
    
    TSpline3* N3N1Zneg = new TSpline3("spline12", &dynamicArray23[10], &dynamicArray24[10], numEntries12);
    // Deallocate the dynamic arrays
    //delete[] dynamicArray23;
    //delete[] dynamicArray24;
    
    //define final state cross sections for pos and neg mu:
     int size1 = 31;
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
     
     
     for (int i = 0; i < 30; i++)
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
	std::cout <<  "x = " << x[i] << std::endl;
	std::cout << yN2N3 << std::endl;
	std::cout << "hi" <<std::endl;

	p1[j] = yN2C1 * yN2N1Zpos + yN3C1 * yN3N1Zpos;
	p2[j] = yN2C1 * yN2N1hpos + yN3C1 * yN3N1hpos;
	p3[j] = yC1C1;
	p4[j] = yN2N3 * yN2N1Zpos * yN3N1Zpos;
	p5[j] = yN2N3 * yN2N1Zpos * yN3N1hpos + yN2N3 * yN2N1hpos * yN3N1Zpos;
	p6[j] = yN2N3 * yN2N1hpos * yN3N1hpos;

	n1[j] = yN2C1 * yN2N1Zneg + yN3C1 * yN3N1Zneg;
	n2[j] = yN2C1 * yN2N1hneg + yN3C1 * yN3N1hneg;
	n3[j] = yC1C1;
	n4[j] = yN2N3 * yN2N1Zneg * yN3N1Zneg;
	n5[j] = yN2N3 * yN2N1Zneg * yN3N1hneg + yN2N3 * yN2N1hneg * yN3N1Zneg;
	n6[j] = yN2N3 * yN2N1hneg * yN3N1hneg;

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

    TCanvas* canvas = new TCanvas("Xsection vs mu", "Xsection vs mu", 800, 800);

    WZp->Draw("AP");
    WZp->SetTitle("WZ+MET,+mu;mu GeV; XSection");
    canvas->SaveAs("WZ+mu.png");

//   Whp->Draw("AP");
    // Whp->SetTitle("Wh+MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("Wh+mu.png");

    // WWp->Draw("AP");
    //    WWp->SetTitle("WW+MET,+mu;mu GeV; XSection");
    // canvas->SaveAs("WW+mu.png");

    //ZZp->Draw("AP");
    //ZZp->SetTitle("ZZ+MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("ZZ+mu.png");

    //hZp->Draw("AP");
    //hZp->SetTitle("hZ+MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("hZ+mu.png");

    //hhp->Draw("AP");
    //hhp->SetTitle("hh+MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("hh+mu.png");

    //WZn->Draw("AP");
    //WZn->SetTitle("WZ-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("WZ-mu.png");

    //Whn->Draw("AP");
    //Whn->SetTitle("Wh-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("Wh-mu.png");

    //    WWn->Draw("AP");
    //WWn->SetTitle("WW-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("WW-mu.png");

    //ZZn->Draw("AP");
    //ZZn->SetTitle("ZZ-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("ZZ-mu.png");

    //hZn->Draw("AP");
    //hZn->SetTitle("hZ-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("hZ-mu.png");

    // hhn->Draw("AP");
    // hhn->SetTitle("hh-MET,+mu;mu GeV; XSection");
    //canvas->SaveAs("hh-mu.png");
    
    return 0;
}
