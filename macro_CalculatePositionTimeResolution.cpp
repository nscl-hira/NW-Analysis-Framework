void macro_CalculatePositionTimeResolution()
{
  TFile * FileIn = new TFile("output/NW_CosmicTimePositionHistograms_3014_3014.root");

  TCanvas * c1 = new TCanvas("c1", "", 1024, 768);
  gStyle->SetOptStat(0);

  TH1D * NWAPositionPredictedCalculatedDiff[25];
  TH1D * NWBPositionPredictedCalculatedDiff[25];
  TH1D * NWATimePredictedCalculatedDiff[25];
  TH1D * NWBTimePredictedCalculatedDiff[25];

  for(int i=0; i<25; i++)
  {
    NWAPositionPredictedCalculatedDiff[i] = (TH1D*)FileIn->Get(Form("NWAPositionPredictedCalculatedDiff_%02d",i));
    NWBPositionPredictedCalculatedDiff[i] = (TH1D*)FileIn->Get(Form("NWBPositionPredictedCalculatedDiff_%02d",i));
    NWATimePredictedCalculatedDiff[i]     = (TH1D*)FileIn->Get(Form("NWATimePredictedCalculatedDiff_%02d",i));
    NWBTimePredictedCalculatedDiff[i]     = (TH1D*)FileIn->Get(Form("NWBTimePredictedCalculatedDiff_%02d",i));
  }

  TH1D * NWBFWHM_Pos = new TH1D ("NWBFWHM_Pos", "NWBFWHM_Pos", 100, 5,15);
  TH1D * NWBFWHM_Time = new TH1D ("NWBFWHM_Time", "NWBFWHM_Time", 100, 0,5);
  for(int i=0; i<25; i++) {
    NWBPositionPredictedCalculatedDiff[i]->Draw();
    NWBPositionPredictedCalculatedDiff[i]->GetXaxis()->SetLabelSize(0.05);
    NWBPositionPredictedCalculatedDiff[i]->GetXaxis()->SetTitleSize(0.05);
    NWBPositionPredictedCalculatedDiff[i]->GetXaxis()->SetTitle("X_{calc}-X_{measured} (cm)");
    NWBPositionPredictedCalculatedDiff[i]->GetXaxis()->CenterTitle(true);
    NWBPositionPredictedCalculatedDiff[i]->GetYaxis()->SetLabelSize(0.05);
    NWBPositionPredictedCalculatedDiff[i]->GetYaxis()->SetTitleSize(0.05);
    NWBPositionPredictedCalculatedDiff[i]->GetYaxis()->SetTitle("counts");
    NWBPositionPredictedCalculatedDiff[i]->GetYaxis()->CenterTitle(true);
    NWBPositionPredictedCalculatedDiff[i]->SetLineWidth(2);
    NWBPositionPredictedCalculatedDiff[i]->SetTitle(NWBPositionPredictedCalculatedDiff[i]->GetName());
    c1->Print(Form("pictures/NWB_CheckOnPositions_%02d.png", i));
    if(NWBPositionPredictedCalculatedDiff[i]->GetStdDev()>0) NWBFWHM_Pos->Fill(NWBPositionPredictedCalculatedDiff[i]->GetStdDev()*2.75);
    NWBTimePredictedCalculatedDiff[i]->Draw();
    NWBTimePredictedCalculatedDiff[i]->GetXaxis()->SetLabelSize(0.05);
    NWBTimePredictedCalculatedDiff[i]->GetXaxis()->SetTitleSize(0.05);
    NWBTimePredictedCalculatedDiff[i]->GetXaxis()->SetTitle("T_{calc}-T_{measured} (ns)");
    NWBTimePredictedCalculatedDiff[i]->GetXaxis()->CenterTitle(true);
    NWBTimePredictedCalculatedDiff[i]->GetYaxis()->SetLabelSize(0.05);
    NWBTimePredictedCalculatedDiff[i]->GetYaxis()->SetTitleSize(0.05);
    NWBTimePredictedCalculatedDiff[i]->GetYaxis()->SetTitle("counts");
    NWBTimePredictedCalculatedDiff[i]->GetYaxis()->CenterTitle(true);
    NWBTimePredictedCalculatedDiff[i]->SetLineWidth(2);
    NWBTimePredictedCalculatedDiff[i]->SetTitle(NWBTimePredictedCalculatedDiff[i]->GetName());
    c1->Print(Form("pictures/NWB_CheckOnTimes_%02d.png", i));
    printf("bar %d -> %f\n", i, NWBTimePredictedCalculatedDiff[i]->GetStdDev()*2.75);
    if(NWBTimePredictedCalculatedDiff[i]->GetStdDev()>0) NWBFWHM_Time->Fill(NWBTimePredictedCalculatedDiff[i]->GetStdDev()*2.75);
  }
  NWBFWHM_Pos->Draw();
  NWBFWHM_Pos->GetXaxis()->SetLabelSize(0.05);
  NWBFWHM_Pos->GetXaxis()->SetTitleSize(0.05);
  NWBFWHM_Pos->GetXaxis()->SetTitle("FWHM of position deviation (cm)");
  NWBFWHM_Pos->GetXaxis()->CenterTitle(true);
  NWBFWHM_Pos->GetYaxis()->SetLabelSize(0.05);
  NWBFWHM_Pos->GetYaxis()->SetTitleSize(0.05);
  NWBFWHM_Pos->GetYaxis()->SetTitle("counts");
  NWBFWHM_Pos->GetYaxis()->CenterTitle(true);
  NWBFWHM_Pos->SetLineWidth(2);
  printf("NWB position deviation = %f +- %f\n", NWBFWHM_Pos->GetMean(), NWBFWHM_Pos->GetStdDev());
  c1->Print(Form("pictures/NWB_FWHMPositions.png"));
  NWBFWHM_Time->Draw();
  NWBFWHM_Time->GetXaxis()->SetLabelSize(0.05);
  NWBFWHM_Time->GetXaxis()->SetTitleSize(0.05);
  NWBFWHM_Time->GetXaxis()->SetTitle("FWHM of time deviation (ns)");
  NWBFWHM_Time->GetXaxis()->CenterTitle(true);
  NWBFWHM_Time->GetYaxis()->SetLabelSize(0.05);
  NWBFWHM_Time->GetYaxis()->SetTitleSize(0.05);
  NWBFWHM_Time->GetYaxis()->SetTitle("counts");
  NWBFWHM_Time->GetYaxis()->CenterTitle(true);
  NWBFWHM_Time->SetLineWidth(2);
  printf("NWB time deviation = %f +- %f\n", NWBFWHM_Time->GetMean(), NWBFWHM_Time->GetStdDev());
  c1->Print(Form("pictures/NWB_FWHMTimes.png"));
}
