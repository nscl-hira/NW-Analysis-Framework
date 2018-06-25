#include "include/shared.h"

void macro_ForwardArrayPulseHeightTimeDependence ()
{
  //This macro finds the pulse height dependence of FA time by
  //inspecting calibrated histograms (where FA elements have been already
  //corrected in time)

  TCanvas * c1 = new TCanvas("c1","",1280,768);
  c1->Divide(2,1);

  ofstream FileOut("calibrations/FA_PulseHeightCorrection_run2523_tobedeleted.dat");
  FileOut<<"* FA Pulse Height correction with a [0]-[1]*exp(-[2]*x) formula\n";
  FileOut<<"*" << setw(5) << "sector" << setw(15) << "a0" << setw(15) << "a1" << setw(15) << "a2" << endl;

  TFile * FileIn = new TFile("output/FANW_ToFHistograms_Ca40Merged.root");
  if(!FileIn->IsOpen()) {
    printf("Error while attaching ROOT files\n");
    return;
  }

  TH2D * FAWBWToFvsE[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FAWBWToFvsE[i] = (TH2D *)FileIn->Get(Form("FA%02dNWBToFvsE", i+1));
  }

  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FAWBWToFvsE[i]->Rebin2D(1,4);

    int NPoints=0;
    double XEnergy[200];
    double YToF[200];

    int RoySize=20;
    for(int EneCh=FAWBWToFvsE[i]->GetYaxis()->FindBin(300); EneCh<FAWBWToFvsE[i]->GetNbinsY(); EneCh+=RoySize)
    {
      c1->cd(1);
      FAWBWToFvsE[i]->Draw("colz");
      double EneMin=FAWBWToFvsE[i]->GetYaxis()->GetBinCenter(EneCh<FAWBWToFvsE[i]->GetNbinsY() ? EneCh : FAWBWToFvsE[i]->GetNbinsY()-1);
      double EneMax=FAWBWToFvsE[i]->GetYaxis()->GetBinCenter(EneCh+RoySize<FAWBWToFvsE[i]->GetNbinsY() ? EneCh+RoySize : FAWBWToFvsE[i]->GetNbinsY()-1);
      double EneMean=FAWBWToFvsE[i]->GetYaxis()->GetBinCenter(EneCh+RoySize/2);
      if(EneMin==EneMax) continue;
      TH1D * ProjToF = FAWBWToFvsE[i]->ProjectionX("ProjToF",EneCh,EneCh+RoySize);
      ProjToF->Rebin(10);
      ProjToF->SetTitle(Form("ToF Projection %.2f<fE<%.2f",EneMin, EneMax));
      TLine *LineMin = new TLine(-150,EneMin,150,EneMin);
      TLine *LineMax = new TLine(-150,EneMax,150,EneMax);
      LineMin->SetLineColor(kRed);
      LineMax->SetLineColor(kRed);
      LineMin->SetLineWidth(2);
      LineMax->SetLineWidth(2);
      LineMin->Draw("SAME");
      LineMax->Draw("SAME");
      gPad->Modified();
      gPad->Update();

      c1->cd(2);
      ProjToF->Draw();
      ProjToF->Fit("gaus","","",-3.5,1.5);
      TF1 * FitFunc = ProjToF->GetFunction("gaus");
      if(FitFunc==0) continue;
      if(FitFunc->GetParameter(0)<10) continue;
      XEnergy[NPoints]=EneMean;
      YToF[NPoints]=FitFunc->GetParameter(1);
      NPoints++;
      gPad->Modified();
      gPad->Update();
    }

    NPoints--;
    TGraph * PulseHeightDependenceGraph = new TGraph(NPoints, XEnergy, YToF);
    TGraph * PulseHeightDependenceCheck = new TGraph(NPoints, YToF, XEnergy);

    c1->cd(1);
    PulseHeightDependenceCheck->Draw("SAME *");
    PulseHeightDependenceCheck->SetMarkerColor(kRed);
    gPad->Modified();
    gPad->Update();

    c1->cd(2);
    PulseHeightDependenceGraph->Draw("A *");
    PulseHeightDependenceGraph->SetMarkerColor(kRed);
    TF1 * FitCorrection = new TF1("FitCorrection","[0]-[1]*exp(-[2]*x)",0,4096);
    FitCorrection->SetParameters(1.16,1,0.005);
    FitCorrection->SetParLimits(0,0.8,1.5);
    PulseHeightDependenceGraph->Fit("FitCorrection");
    //FitCorrection->Draw("SAME");

    gPad->Modified();
    gPad->Update();
    getchar();

    c1->cd(1);
    int NpointsDisplay=100;
    double correctedXEnergy[NpointsDisplay];
    double correcteddYToF[NpointsDisplay];
    for(int i=0; i<NpointsDisplay; i++)
    {
      correctedXEnergy[i]=4096.*i/NpointsDisplay;
      correcteddYToF[i]=FitCorrection->Eval(correctedXEnergy[i]);
    }
    TGraph * GraphCheck = new TGraph(NpointsDisplay,correcteddYToF,correctedXEnergy);
    FAWBWToFvsE[i]->Draw("colz");
    GraphCheck->SetLineColor(kRed);
    GraphCheck->SetLineWidth(2);
    GraphCheck->Draw("SAME L");
    gPad->Modified();
    gPad->Update();

    TCanvas * c2 = new TCanvas("c2", "", 800,600);
    c2->SetLogz(true);
    gStyle->SetOptStat(0);
    FAWBWToFvsE[i]->Rebin2D(4,4);
    FAWBWToFvsE[i]->Draw("colz");
    FAWBWToFvsE[i]->SetTitle(Form("FA%02dNWB_PulseHeightToFCorrection", i+1));
    FAWBWToFvsE[i]->GetXaxis()->SetRange(FAWBWToFvsE[i]->GetXaxis()->FindBin(-10), FAWBWToFvsE[i]->GetXaxis()->FindBin(10));
    GraphCheck->Draw("SAME L");
    gPad->Modified();
    gPad->Update();
    getchar();
    continue;
    c2->Print(Form("pictures/FA%02dNWB_PulseHeightToFCorrection.png", i+1));

    FileOut<< setw(5) << i+1 << setw(15) << FitCorrection->GetParameter(0) << setw(15) << FitCorrection->GetParameter(1) << setw(15) << FitCorrection->GetParameter(2) << endl;

  }
}
