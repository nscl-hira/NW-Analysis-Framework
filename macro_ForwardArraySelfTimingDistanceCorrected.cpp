#include "include/shared.h"

void macro_ForwardArraySelfTimingDistanceCorrected()
{
  TCanvas * c1 = new TCanvas("c1","",800,600);

  TFile * FileIn = new TFile("output/FANW_ToFHistograms_Ca48Merged.root");
  if(!FileIn->IsOpen()) {
    printf("Error while attaching ROOT files\n");
    return;
  }
  
  ofstream FileOut("calibrations/FA_Time_Offset_run4557.dat");

  FileOut<<"* Forward Array time offsets\n";
  FileOut<<"*"<<setw(10)<<"numdet"<<setw(20)<<"offset (ns)"<< endl;
  
  TH1D * FANWBToF[NUM_DETECTORS_FA];
  TH2D * FANWBToFDistance[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FANWBToF[i] = (TH1D *)FileIn->Get(Form("FA%02dNWBToF", i+1));
    FANWBToFDistance[i] = (TH2D *)FileIn->Get(Form("FA%02dNWBToFvsDist", i+1));
  }
  
  TH1D * FANWBOffsetDistribution[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FANWBOffsetDistribution[i] = new TH1D (Form("FA%02dFANWBOffsetDistribution", i+1),Form("FA%02dFANWBOffsetDistribution", i+1), 800, -5, 20);
  }

  double SpeedOfLight = 29.9792;
  TSpectrum PeakFinder(1);
  for(int i=0; i<NUM_DETECTORS_FA; i++)
  {
    FANWBToF[i]->Draw();
    PeakFinder.Search(FANWBToF[i], 2, "", 1);
    double * PeakCenter=PeakFinder.GetPositionX();
    gPad->Modified();
    gPad->Update();
    getchar();
    
    FANWBToFDistance[i]->Draw("colz");
    FANWBToFDistance[i]->SetLineColor(kBlue);
    FANWBToFDistance[i]->SetLineWidth(2);
    FANWBToFDistance[i]->GetXaxis()->SetLabelSize(0.05);
    FANWBToFDistance[i]->GetXaxis()->SetTitleSize(0.05);
    FANWBToFDistance[i]->GetXaxis()->CenterTitle(true);
    FANWBToFDistance[i]->GetXaxis()->SetTitle("NWBTimeMean - FATime (ns)");
    FANWBToFDistance[i]->GetYaxis()->SetLabelSize(0.05);
    FANWBToFDistance[i]->GetYaxis()->SetTitleSize(0.05);
    FANWBToFDistance[i]->GetYaxis()->CenterTitle(true);
    FANWBToFDistance[i]->GetYaxis()->SetTitle("Corrected Flying Path (cm)");
    FANWBToFDistance[i]->SetTitle(FANWBToFDistance[i]->GetName());
    FANWBToFDistance[i]->GetXaxis()->SetRange(FANWBToFDistance[i]->GetXaxis()->FindBin(*PeakCenter-1.2), FANWBToFDistance[i]->GetXaxis()->FindBin(*PeakCenter+1.4));
    FANWBToFDistance[i]->GetYaxis()->SetRange(FANWBToFDistance[i]->GetYaxis()->FindBin(448), FANWBToFDistance[i]->GetYaxis()->FindBin(471));
    gPad->Modified();
    gPad->Update();
    getchar();
    c1->Print(Form("pictures/FA%02dNWBToFvsDist.png", i+1));
    
    for(int bin=FANWBToFDistance[i]->GetYaxis()->FindBin(448); bin<FANWBToFDistance[i]->GetYaxis()->FindBin(471); bin++) {
      double Distance=FANWBToFDistance[i]->GetYaxis()->GetBinCenter(bin);
            
      for(int binx=FANWBToFDistance[i]->GetXaxis()->FindBin(*PeakCenter-1.2); binx<FANWBToFDistance[i]->GetXaxis()->FindBin(*PeakCenter+1.4); binx++) {
        double ToF=FANWBToFDistance[i]->GetXaxis()->GetBinCenter(binx);
	double counts = FANWBToFDistance[i]->GetBinContent(binx,bin);
	
	double Offset = ToF-Distance/SpeedOfLight;
	
	FANWBOffsetDistribution[i]->Fill(Offset,counts);
      }
    }
        
    FANWBOffsetDistribution[i]->Rebin(2);
    FANWBOffsetDistribution[i]->Draw("hist");
    FANWBOffsetDistribution[i]->SetLineColor(kBlue);
    FANWBOffsetDistribution[i]->SetLineWidth(2);
    FANWBOffsetDistribution[i]->GetXaxis()->SetLabelSize(0.05);
    FANWBOffsetDistribution[i]->GetXaxis()->SetTitleSize(0.05);
    FANWBOffsetDistribution[i]->GetXaxis()->CenterTitle(true);
    FANWBOffsetDistribution[i]->GetXaxis()->SetTitle("FA Time Offset (ns)");
    FANWBOffsetDistribution[i]->GetYaxis()->SetLabelSize(0.05);
    FANWBOffsetDistribution[i]->GetYaxis()->SetTitleSize(0.05);
    FANWBOffsetDistribution[i]->GetYaxis()->CenterTitle(true);
    FANWBOffsetDistribution[i]->GetYaxis()->SetTitle("counts");
    
    PeakFinder.Search(FANWBOffsetDistribution[i], 5, "", 1);
    double * PeakCenterOffset=PeakFinder.GetPositionX();
    gPad->Modified();
    gPad->Update();
    getchar();
    c1->Print(Form("pictures/FA%02dOffsetDistanceCorrected.png", i+1));
        
    FileOut << setw(10) << i+1 << " " << setw(20) << -(*PeakCenterOffset) << endl;
  }
  
  FileOut.close();
  FileIn->Close();
}
