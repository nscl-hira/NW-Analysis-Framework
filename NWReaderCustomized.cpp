#include "include/NWReader.h"

//____________________________________________________
void NWReader::CreateNWCosmicsUsefulPlots(const char * file_name, Long64_t evt_amount)
{
  // this method builds histograms of useful quantities for
  // cosmic ray data position and time calibrations within a wall.
  TFile * FileOut = new TFile(file_name, "RECREATE");

  int TimeReferenceBar=12;

  TH2D * NWAHitPattern = new TH2D("NWAHitPattern","",200,-150,150,25,-0.5,24.5);
  TH2D * NWBHitPattern = new TH2D("NWBHitPattern","",200,-150,150,25,-0.5,24.5);
  TH2D * NWATimeReferenceDiff=new TH2D ("NWATimeReferenceDiff","",200,-20,20,25,-0.5,24.5);
  TH2D * NWBTimeReferenceDiff=new TH2D ("NWBTimeReferenceDiff","",200,-20,20,25,-0.5,24.5);
  TH1D * NWAPositionPredictedCalculatedDiff[NUM_BARS_NWA];
  TH1D * NWBPositionPredictedCalculatedDiff[NUM_BARS_NWB];
  TH1D * NWATimePredictedCalculatedDiff[NUM_BARS_NWA];
  TH1D * NWBTimePredictedCalculatedDiff[NUM_BARS_NWB];
  for(int i=0; i<NUM_BARS_NWA; i++) {
    NWAPositionPredictedCalculatedDiff[i]=new TH1D (Form("NWAPositionPredictedCalculatedDiff_%02d", i),"",200,-20,20);
    NWATimePredictedCalculatedDiff[i]=new TH1D (Form("NWATimePredictedCalculatedDiff_%02d", i),"",200,-20,20);
  }
  for(int i=0; i<NUM_BARS_NWB; i++) {
    NWBPositionPredictedCalculatedDiff[i]=new TH1D (Form("NWBPositionPredictedCalculatedDiff_%02d", i),"",200,-20,20);
    NWBTimePredictedCalculatedDiff[i]=new TH1D (Form("NWBTimePredictedCalculatedDiff_%02d", i),"",200,-20,20);
  }

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fNWReader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      printf("Percentage = %.2f %%\n", 100*double(jentry)/nentries);
    }

    NeutronWallCalibratedData * NWA = fNWACal->Get();
    NeutronWallCalibratedData * NWB = fNWBCal->Get();

    double XPos[25];
    double YPos[25];
    double TMean[25];
    int numbar[25];
    double ReferenceTime=0;
    int numhits=0;
    bool IsReferenceHit=false;

/*
    //Neutron Wall A
    if(NWA->fmulti<6) continue;
    numhits=0;
    for(int i=0; i<NWA->fmulti; i++) {
      NWAHitPattern->Fill(NWA->fXcm[i], NWA->fnumbar[i]);
      if(NWA->fnumbar[i]==TimeReferenceBar) {
        IsReferenceHit=true;
        ReferenceTime=NWA->fTimeMean[i];
      }
      TMean[numhits]=NWA->fTimeMean[i];
      XPos[numhits]=NWA->fXcm[i];
      YPos[numhits]=NWA->fnumbar[i]*fNWAarHigh;
      numbar[numhits]=NWA->fnumbar[i];
      numhits++;
    }
    TGraph NWAtrack (numhits, YPos, XPos);
    NWAtrack.Fit("pol1", "q");
    TF1 * NWAtrackFunc = NWAtrack.GetFunction("pol1");
    double NWAtrackAngle=atan(NWAtrackFunc->GetParameter(1));
    for(int hit=0; hit<numhits; hit++) {
      if(IsReferenceHit) {
        NWATimeReferenceDiff->Fill(TMean[hit]-ReferenceTime,numbar[hit]);
      }
      NWAPositionPredictedCalculatedDiff[numbar[hit]]->Fill(NWAtrackFunc->Eval(YPos[hit])-XPos[hit]);
      if(hit>1) {
        NWATimePredictedCalculatedDiff[numbar[hit]]->Fill((numbar[hit]-numbar[hit-1])*fNWAarHigh/(cos(NWAtrackAngle)*fSpeedOfLight)-(TMean[hit]-TMean[hit-1]));
      }
    }
    */

    //Neutron Wall B
    if(NWB->fmulti<6) continue;
    numhits=0;
    for(int i=0; i<NWB->fmulti; i++) {
      NWBHitPattern->Fill(NWB->fXcm[i], NWB->fnumbar[i]);
      if(NWB->fnumbar[i]==TimeReferenceBar) {
        IsReferenceHit=true;
        ReferenceTime=NWB->fTimeMean[i];
      }
      TMean[numhits]=NWB->fTimeMean[i];
      XPos[numhits]=NWB->fXcm[i];
      YPos[numhits]=NWB->fnumbar[i]*fNWBarHigh;
      numbar[numhits]=NWB->fnumbar[i];
      numhits++;
    }
    TGraph NWBtrack (numhits, YPos, XPos);
    NWBtrack.Fit("pol1", "q");
    TF1 * NWBtrackFunc = NWBtrack.GetFunction("pol1");
    double NWBtrackAngle=atan(NWBtrackFunc->GetParameter(1));
    for(int hit=0; hit<numhits; hit++) {
      if(IsReferenceHit) {
        NWBTimeReferenceDiff->Fill(TMean[hit]-ReferenceTime,numbar[hit]);
      }
      NWBPositionPredictedCalculatedDiff[numbar[hit]]->Fill(NWBtrackFunc->Eval(YPos[hit])-XPos[hit]);
      if(hit>1) {
        NWBTimePredictedCalculatedDiff[numbar[hit]]->Fill((numbar[hit]-numbar[hit-1])*fNWBarHigh/(cos(NWBtrackAngle)*fSpeedOfLight)-(TMean[hit]-TMean[hit-1]));
      }
    }


    jentry++;
  }

  //Saving histograms to file
  FileOut->WriteTObject(NWAHitPattern, NWAHitPattern->GetName());
  FileOut->WriteTObject(NWATimeReferenceDiff, NWATimeReferenceDiff->GetName());
  for(int i=0; i<NUM_BARS_NWA; i++) {
    FileOut->WriteTObject(NWAPositionPredictedCalculatedDiff[i], NWAPositionPredictedCalculatedDiff[i]->GetName());
    FileOut->WriteTObject(NWATimePredictedCalculatedDiff[i], NWATimePredictedCalculatedDiff[i]->GetName());
  }
  FileOut->WriteTObject(NWBHitPattern, NWBHitPattern->GetName());
  FileOut->WriteTObject(NWBTimeReferenceDiff, NWBTimeReferenceDiff->GetName());
  for(int i=0; i<NUM_BARS_NWB; i++) {
    FileOut->WriteTObject(NWBPositionPredictedCalculatedDiff[i], NWBPositionPredictedCalculatedDiff[i]->GetName());
    FileOut->WriteTObject(NWBTimePredictedCalculatedDiff[i], NWBTimePredictedCalculatedDiff[i]->GetName());
  }

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void NWReader::CreateNWToFPlots(const char * file_name, Long64_t evt_amount)
{
  // this method creates histograms containing FA-NWB ToF spectra
  TFile * FileOut = new TFile(file_name, "RECREATE");

  TH1D * FANWBToF[NUM_DETECTORS_FA];
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FANWBToF[i] = new TH1D(Form("FA%02dNWBToF", i),"",1000,-150,150);
  }

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  for(;fNWReader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      printf("Percentage = %.2f %%\n", 100*double(jentry)/nentries);
    }

    NeutronWallCalibratedData * NWA = fNWACal->Get();
    NeutronWallCalibratedData * NWB = fNWBCal->Get();
    ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();

    for(int FAhit=0; FAhit<ForwardArray->fmulti; FAhit++)
    {
      if(ForwardArray->fE[FAhit]<300) continue;
      for(int NWhit=0; NWhit<NWB->fmulti; NWhit++) {
        FANWBToF[ForwardArray->fnumdet[FAhit]-1]->Fill(NWB->fTimeMean[NWhit]-ForwardArray->fTime[FAhit]);
      }
    }
  }

  //Saving histograms to file
  for(int i=0; i<NUM_DETECTORS_FA; i++) {
    FileOut->WriteTObject(FANWBToF[i], FANWBToF[i]->GetName());
  }

  // closing output file
  FileOut->Close();
}
