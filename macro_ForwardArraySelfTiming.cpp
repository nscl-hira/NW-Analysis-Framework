#include "include/shared.h"

void macro_ForwardArraySelfTiming()
{
  TFile * FileIn = new TFile("output/FANW_ToFHistograms_Ca40Merged.root");
  if(!FileIn->IsOpen()) {
    printf("Error while attaching ROOT files\n");
    return;
  }

  TH1D * FANWBToF[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FANWBToF[i] = (TH1D *)FileIn->Get(Form("FA%02dNWBToF", i+1));
  }

  ofstream FileOut("calibrations/FA_Time_Offset_run2523.dat");

  FileOut<<"* Forward Array time offsets\n";
  FileOut<<"*"<<setw(10)<<"numdet"<<setw(20)<<"offset (ns)"<< endl;

  TSpectrum PeakFinder(1);
  for(int i=0; i<NUM_DETECTORS_FA; i++)
  {
    FANWBToF[i]->Draw();
    PeakFinder.Search(FANWBToF[i], 2, "", 1);
    double * PeakCenter=PeakFinder.GetPositionX();

    FileOut << setw(10) << i+1 << " " << setw(20) << -(*PeakCenter) << endl;

    gPad->Modified();
    gPad->Update();
    getchar();
  }

  FileOut.close();
  FileIn->Close();

  return;
}
