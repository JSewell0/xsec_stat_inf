float GetAngle(float M0, float E0, float m);
float GetAngleGeneral(float M0, float E0, float m, float boost_angle); // Just like the function above, but for boost in any general direction

void Prog1()
{
  float M_Mother = 400;
  float M_Daughter = 4;
  vector<float>energy,angle90,angle0,angle45,angle30,angle60,angle120,angle135,angle150,angle180;
  
  for(float E = 100;E<1e3;E+=10){
    // cout<<E<<"\t"<<GetAngle(M_Mother,E,M_Daughter)<<endl;
    energy.push_back(E);
  angle0.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,M_PI/(1e3)));
  angle45.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,M_PI/4));
  angle90.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,M_PI/2));
  angle30.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,M_PI/6));
  angle60.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,M_PI/3));
  angle120.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,2*M_PI/3));
  angle135.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,3*M_PI/4));
  angle150.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,5*M_PI/6));
  angle180.push_back(GetAngleGeneral(M_Mother,E,M_Daughter,179*M_PI/180));
  }

  TGraph* tg0 = new TGraph(energy.size(),&energy[0],&angle0[0]); tg0->SetTitle("0");
  TGraph* tg45 = new TGraph(energy.size(),&energy[0],&angle45[0]); tg45->SetTitle("45"); 
  TGraph* tg90 = new TGraph(energy.size(),&energy[0],&angle90[0]); tg90->SetTitle("90");
  TGraph* tg30 = new TGraph(energy.size(),&energy[0],&angle30[0]); tg30->SetTitle("30");
  TGraph* tg60 = new TGraph(energy.size(),&energy[0],&angle60[0]); tg60->SetTitle("60");
  TGraph* tg120 = new TGraph(energy.size(),&energy[0],&angle120[0]); tg120->SetTitle("120");
  TGraph* tg135 = new TGraph(energy.size(),&energy[0],&angle135[0]); tg135->SetTitle("135");
  TGraph* tg150 = new TGraph(energy.size(),&energy[0],&angle150[0]); tg150->SetTitle("150");
  TGraph* tg180 = new TGraph(energy.size(),&energy[0],&angle180[0]); tg180->SetTitle("180");
  
  TCanvas* tc = new TCanvas("aa","bb",800,600);
  TMultiGraph* tmg = new TMultiGraph();

  // tmg->Add(tg0,"pl");		// tg0->SetLine
  // tmg->Add(tg45,"pl");
  // tmg->Add(tg90,"pl");
  // // tg0->Draw("apl");
  // TString title = Form("Mother mass %.0f | Daughter mass %.0f;Energy of parent; Opening angle",M_Mother,M_Daughter);
  // tg0->SetTitle(title);
  // tc->SetGrid();
  // tmg->Draw("apl");
  // tc->BuildLegend(.7,.7,.9,.9);

  tg0->Draw("apl");
  tg0->SetLineWidth(2);
  tg0->SetLineColor(1);

  tg30->Draw("p*l");
  tg30->SetLineWidth(2);
  tg30->SetLineColor(2);

  tg45->Draw("p*l");
  tg45->SetLineWidth(2);
  tg45->SetLineColor(3);

  tg60->Draw("p*l");
  tg60->SetLineWidth(2);
  tg60->SetLineColor(4);

  tg90->Draw("pl");
  tg90->SetLineWidth(2);
  tg90->SetLineColor(6);
  
  tg120->Draw("pl");
  tg120->SetLineWidth(2);
  tg120->SetLineColor(7);
   
  tg135->Draw("pl");
  tg135->SetLineWidth(2);
  tg135->SetLineColor(8);

  tg150->Draw("pl");
  tg150->SetLineWidth(2);
  tg150->SetLineColor(9);

  tg180->Draw("pl");
  tg180->SetLineWidth(2);
  tg180->SetLineColor(46);

  tg0->GetYaxis()->SetRangeUser(0,M_PI);
  TString title = Form("Mother mass %.0f | Daughter mass %.0f | Inclination angle %.0f;Energy of parent; Opening angle",M_Mother,M_Daughter,0.);

  tg0->SetTitle(title);
  //gPad->BuildLegend();

  auto legend = new TLegend(0.9,0.5,1.1,0.9);
  legend->SetHeader("Theta (Degrees)","C");
  legend->SetTextSize(0.025);
  legend->AddEntry(tg0,"0","l");
  legend->AddEntry(tg30,"30","lp");
  legend->AddEntry(tg45,"45","lp");
  legend->AddEntry(tg60,"60","lp");
  legend->AddEntry(tg90,"90","l");
  legend->AddEntry(tg120,"120","lp");
  legend->AddEntry(tg135,"135","lp");
  legend->AddEntry(tg150,"150","lp");
  legend->AddEntry(tg180,"180","l");
  legend->Draw();

  tc->SetGrid();
  tc->SaveAs("tgAll.png");
  delete tc;
}

float GetAngle(float M0, float E0, float m)
{
  float gamma = E0/M0;
  float mu = 2*m/M0;		// range 0 to 1
  mu = pow(mu,2);
  gamma = pow(gamma,2);
  // mu = pow(mu,2);
  // float cos_theta = (mu-gamma)/(4-2*gamma-2*mu);
  // return acos(cos_theta);

  return 2*atan(pow((1-mu)/(gamma-1),.5));
}

// M0 = rest mass of the mother particle
// E0 = energy of the mother particle in lab frame
// m = rest mass of the daughter particles
// boost angle = angle between X-axes of COM and lab frames.
float GetAngleGeneral(float M0, float E0, float m, float boost_angle)
{
  TLorentzVector v1,v2;		// 4-momenta of the daughters.
  float P_daughter = sqrt(M0*M0/4-m*m);
  float gamma = E0/M0;
  float boost_mag = pow(1-1/(gamma*gamma),.5);

  // Center of mass frame
  v1.SetPxPyPzE(P_daughter,0,0,M0/2); // momentum along +X direction
  v2.SetPxPyPzE(-P_daughter,0,0,M0/2); // momentum along -X direction

  // Go to lab frame
  v1.Boost(boost_mag*cos(boost_angle),boost_mag*sin(boost_angle),0);
  v2.Boost(boost_mag*cos(boost_angle),boost_mag*sin(boost_angle),0);

  // Get momentum 3-vectors
  float v1_[4]; v1.GetXYZT(v1_);
  float v2_[4]; v2.GetXYZT(v2_);

  // calculate angle in between
  float cos_theta = (v1_[0]*v2_[0]+v1_[1]*v2_[1])/(pow(v1_[0]*v1_[0]+v1_[1]*v1_[1],.5)*pow(v2_[0]*v2_[0]+v2_[1]*v2_[1],.5));
  // cout<<cos_theta<<endl;
  return acos(cos_theta);
}
