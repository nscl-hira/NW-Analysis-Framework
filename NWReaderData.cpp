#include "include/NWReader.h"

//____________________________________________________
void NWReader::BuildCalibratedEvent()
{
  if(fIsNWA) {
    HTNeutronWallData * NWA = fNWA->Get();
    //Filling calibrated data structures
    fNWACalibratedData.fmulti=0;
    for(int i=0; i<NWA->fmulti; i++)
    {
      if(1) {
        fNWACalibratedData.fnumbar[fNWACalibratedData.fmulti]      =NWA->fnumbar[i];
        fNWACalibratedData.fLeft[fNWACalibratedData.fmulti]        =NWA->fLeft[i];
        fNWACalibratedData.fRight[fNWACalibratedData.fmulti]       =NWA->fRight[i];
        fNWACalibratedData.ffastLeft[fNWACalibratedData.fmulti]    =NWA->ffastLeft[i];
        fNWACalibratedData.ffastRight[fNWACalibratedData.fmulti]   =NWA->ffastRight[i];
        fNWACalibratedData.fTimeLeft[fNWACalibratedData.fmulti]    =NWA->fTimeLeft[i];
        fNWACalibratedData.fTimeRight[fNWACalibratedData.fmulti]   =NWA->fTimeRight[i];
        fNWACalibratedData.fGeoMean[fNWACalibratedData.fmulti]     =NWA->fGeoMean[i];
        fNWACalibratedData.ffastGeoMean[fNWACalibratedData.fmulti] =NWA->ffastGeoMean[i];
        fNWACalibratedData.fTimeMean[fNWACalibratedData.fmulti]    =GetNWATimeMean(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
        fNWACalibratedData.fCalGeoMean[fNWACalibratedData.fmulti]  =-9999;
        fNWACalibratedData.fMatchedLeft[fNWACalibratedData.fmulti] =-9999;
        fNWACalibratedData.fMatchedRight[fNWACalibratedData.fmulti]=-9999;
        fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]         =GetNWAXcm(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
        fNWACalibratedData.fTheta[fNWACalibratedData.fmulti]       =GetNWATheta(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fPhi[fNWACalibratedData.fmulti]         =GetNWAPhi(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fThetaRan[fNWACalibratedData.fmulti]    =GetNWAThetaRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fPhiRan[fNWACalibratedData.fmulti]      =GetNWAPhiRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fDistcm[fNWACalibratedData.fmulti]      =GetNWADistance(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fDistRancm[fNWACalibratedData.fmulti]   =GetNWADistanceRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fmulti++;
      }
    }
  }

  if(fIsNWB) {
    HTNeutronWallData * NWB = fNWB->Get();
    fNWBCalibratedData.fmulti=0;
    for(int i=0; i<NWB->fmulti; i++)
    {
      if(1) {
        fNWBCalibratedData.fnumbar[fNWBCalibratedData.fmulti]      =NWB->fnumbar[i];
        fNWBCalibratedData.fLeft[fNWBCalibratedData.fmulti]        =NWB->fLeft[i];
        fNWBCalibratedData.fRight[fNWBCalibratedData.fmulti]       =NWB->fRight[i];
        fNWBCalibratedData.ffastLeft[fNWBCalibratedData.fmulti]    =NWB->ffastLeft[i];
        fNWBCalibratedData.ffastRight[fNWBCalibratedData.fmulti]   =NWB->ffastRight[i];
        fNWBCalibratedData.fTimeLeft[fNWBCalibratedData.fmulti]    =NWB->fTimeLeft[i];
        fNWBCalibratedData.fTimeRight[fNWBCalibratedData.fmulti]   =NWB->fTimeRight[i];
        fNWBCalibratedData.fGeoMean[fNWBCalibratedData.fmulti]     =NWB->fGeoMean[i];
        fNWBCalibratedData.ffastGeoMean[fNWBCalibratedData.fmulti] =NWB->ffastGeoMean[i];
        fNWBCalibratedData.fTimeMean[fNWBCalibratedData.fmulti]    =GetNWBTimeMean(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
        fNWBCalibratedData.fCalGeoMean[fNWBCalibratedData.fmulti]  =-9999;
        fNWBCalibratedData.fMatchedLeft[fNWBCalibratedData.fmulti] =-9999;
        fNWBCalibratedData.fMatchedRight[fNWBCalibratedData.fmulti]=-9999;
        fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]         =GetNWBXcm(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
        fNWBCalibratedData.fTheta[fNWBCalibratedData.fmulti]       =GetNWBTheta(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fPhi[fNWBCalibratedData.fmulti]         =GetNWBPhi(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fThetaRan[fNWBCalibratedData.fmulti]    =GetNWBThetaRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fPhiRan[fNWBCalibratedData.fmulti]      =GetNWBPhiRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fDistcm[fNWBCalibratedData.fmulti]      =GetNWBDistance(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fDistRancm[fNWBCalibratedData.fmulti]   =GetNWBDistanceRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fmulti++;
      }
    }
  }

  if(fIsVW) {
    HTVetoWallData * VetoWall = fVetoWall->Get();
    fVetoWallCalibratedData.fmulti=0;
    fVetoWallCalibratedData.fidmulti=0;
    for(int i=0; i<VetoWall->fmulti; i++)
    {
      if(1) {
        fVetoWallCalibratedData.fnumbar[fVetoWallCalibratedData.fmulti]     =VetoWall->fnumbar[i];
        fVetoWallCalibratedData.fTop[fVetoWallCalibratedData.fmulti]        =VetoWall->fTop[i];
        fVetoWallCalibratedData.fBottom[fVetoWallCalibratedData.fmulti]     =VetoWall->fBottom[i];
        fVetoWallCalibratedData.fTimeTop[fVetoWallCalibratedData.fmulti]    =VetoWall->fTimeTop[i];
        fVetoWallCalibratedData.fTimeBottom[fVetoWallCalibratedData.fmulti] =VetoWall->fTimeBottom[i];
        fVetoWallCalibratedData.fGeoMean[fVetoWallCalibratedData.fmulti]    =VetoWall->fGeoMean[i];
        fVetoWallCalibratedData.fZ[fVetoWallCalibratedData.fmulti]          =-1;
        fVetoWallCalibratedData.fA[fVetoWallCalibratedData.fmulti]          =-1;
        fVetoWallCalibratedData.fmulti++;
      }
    }
    for(int i=0; i<fVetoWallCalibratedData.fmulti; i++) {
      if(0) {
        fVetoWallCalibratedData.fidmulti++;
      }
    }
  }

  if(fIsFA) {
    HTForwardArrayData * ForwardArray = fForwardArray->Get();
    fForwardArrayCalibratedData.fmulti=0;
    for(int i=0; i<ForwardArray->fmulti; i++)
    {
      if(1) {
        fForwardArrayCalibratedData.fnumdet[fForwardArrayCalibratedData.fmulti]    = ForwardArray->fnumdet[i];
        fForwardArrayCalibratedData.fE[fForwardArrayCalibratedData.fmulti]         = ForwardArray->fE[i];
        fForwardArrayCalibratedData.fTime[fForwardArrayCalibratedData.fmulti]      = ForwardArray->fTime[i]-GetFATimeOffset(ForwardArray->fnumdet[i])+GetFATimePulseHeightCorrection(ForwardArray->fnumdet[i], ForwardArray->fE[i]);
        fForwardArrayCalibratedData.fECal[fForwardArrayCalibratedData.fmulti]      = -9999;
        fForwardArrayCalibratedData.fmulti++;
      }
    }
    //FA tmean and tmin are here calculated. They correspond, respectively to the minimum FA time of the matched times and the
    //time average between any other time which differs for less than 3ns with the minumum
    fForwardArrayCalibratedData.fTimeMin = *std::min_element(fForwardArrayCalibratedData.fTime, fForwardArrayCalibratedData.fTime+fForwardArrayCalibratedData.fmulti);
    double ttolerance=3; //time mean is found within the elements that differ for less than 3 ns from the minimum
    int tgood=0; //number of FA elements giving a time within the tolerance limit
    fForwardArrayCalibratedData.fTimeMean=0;
    for(int i=0; i<fForwardArrayCalibratedData.fmulti; i++) {
      if(fabs(fForwardArrayCalibratedData.fTime[i]-fForwardArrayCalibratedData.fTimeMin) < ttolerance) {
        fForwardArrayCalibratedData.fTimeMean+=fForwardArrayCalibratedData.fTime[i];
        tgood++;
      }
    }
    fForwardArrayCalibratedData.fTimeMean/=tgood;
  }
}

//____________________________________________________
void NWReader::BuildCosmicRayData(const char * file_name, Long64_t evt_amount)
{
  // this method constructs data for cosmic rays
  // to remove the low energy noise a cut in proximity of
  // cosmic peaks is made.
  if(!fNWACosmicRayPositionLoaded && !fNWBCosmicRayPositionLoaded) {
    printf("Error: Cosmic Ray position not loaded\n");
    return;
  }

  TFile * FileOut = new TFile(file_name, "RECREATE");
  if(FileOut->IsZombie()) {
    printf("Error: Cannot create file %s\n", file_name);
    return;
  }
  //Initizalizing output data structures
  NeutronWallCalibratedData * NWACalibrated = new NeutronWallCalibratedData();
  NeutronWallCalibratedData * NWBCalibrated = new NeutronWallCalibratedData();
  // Initializing output TTree
  TTree * TreeOut = new TTree ("E15190", "NW Cosmic Ray Tree");
  if(fIsNWA) TreeOut->Branch("NWA.","NeutronWallCalibratedData",NWACalibrated,32000,2);
  if(fIsNWB) TreeOut->Branch("NWB.","NeutronWallCalibratedData",NWBCalibrated,32000,2);
  TreeOut->SetAutoSave(5000000);

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

    if(fIsNWA) {
      HTNeutronWallData * NWA = fNWA->Get();
      //Filling calibrated data structures
      NWACalibrated->fmulti=0;
      for(int i=0; i<NWA->fmulti; i++)
      {
        if(NWA->fGeoMean[i]>GetNWACosmicStartingPoint(NWA->fnumbar[i])) {
          NWACalibrated->fnumbar[NWACalibrated->fmulti]      =NWA->fnumbar[i];
          NWACalibrated->fLeft[NWACalibrated->fmulti]        =NWA->fLeft[i];
          NWACalibrated->fRight[NWACalibrated->fmulti]       =NWA->fRight[i];
          NWACalibrated->ffastLeft[NWACalibrated->fmulti]    =NWA->ffastLeft[i];
          NWACalibrated->ffastRight[NWACalibrated->fmulti]   =NWA->ffastRight[i];
          NWACalibrated->fTimeLeft[NWACalibrated->fmulti]    =NWA->fTimeLeft[i];
          NWACalibrated->fTimeRight[NWACalibrated->fmulti]   =NWA->fTimeRight[i];
          NWACalibrated->fGeoMean[NWACalibrated->fmulti]     =NWA->fGeoMean[i];
          NWACalibrated->ffastGeoMean[NWACalibrated->fmulti] =NWA->ffastGeoMean[i];
          NWACalibrated->fTimeMean[NWACalibrated->fmulti]    =GetNWATimeMean(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
          NWACalibrated->fCalGeoMean[NWACalibrated->fmulti]  =-9999;
          NWACalibrated->fMatchedLeft[NWACalibrated->fmulti] =-9999;
          NWACalibrated->fMatchedRight[NWACalibrated->fmulti]=-9999;
          NWACalibrated->fXcm[NWACalibrated->fmulti]         =GetNWAXcm(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
          NWACalibrated->fmulti++;
        }
      }
    }

    if(fIsNWB) {
      HTNeutronWallData * NWB = fNWB->Get();
      NWBCalibrated->fmulti=0;
      for(int i=0; i<NWB->fmulti; i++)
      {
        if(NWB->fGeoMean[i]>GetNWBCosmicStartingPoint(NWB->fnumbar[i])) {
          NWBCalibrated->fnumbar[NWBCalibrated->fmulti]      =NWB->fnumbar[i];
          NWBCalibrated->fLeft[NWBCalibrated->fmulti]        =NWB->fLeft[i];
          NWBCalibrated->fRight[NWBCalibrated->fmulti]       =NWB->fRight[i];
          NWBCalibrated->ffastLeft[NWBCalibrated->fmulti]    =NWB->ffastLeft[i];
          NWBCalibrated->ffastRight[NWBCalibrated->fmulti]   =NWB->ffastRight[i];
          NWBCalibrated->fTimeLeft[NWBCalibrated->fmulti]    =NWB->fTimeLeft[i];
          NWBCalibrated->fTimeRight[NWBCalibrated->fmulti]   =NWB->fTimeRight[i];
          NWBCalibrated->fGeoMean[NWBCalibrated->fmulti]     =NWB->fGeoMean[i];
          NWBCalibrated->ffastGeoMean[NWBCalibrated->fmulti] =NWB->ffastGeoMean[i];
          NWBCalibrated->fTimeMean[NWBCalibrated->fmulti]    =GetNWBTimeMean(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
          NWBCalibrated->fCalGeoMean[NWBCalibrated->fmulti]  =-9999;
          NWBCalibrated->fMatchedLeft[NWBCalibrated->fmulti] =-9999;
          NWBCalibrated->fMatchedRight[NWBCalibrated->fmulti]=-9999;
          NWBCalibrated->fXcm[NWBCalibrated->fmulti]         =GetNWBXcm(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
          NWBCalibrated->fmulti++;
        }
      }
    }

    TreeOut->Fill();
  }

  //Save Output Tree to file
  TreeOut->AutoSave();

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void NWReader::BuildCalibratedTree(const char * file_name, Long64_t evt_amount)
{
  // this method constructs a calibrated data tree

  TFile * FileOut = new TFile(file_name, "RECREATE");
  if(FileOut->IsZombie()) {
    printf("Error: Cannot create file %s\n", file_name);
    return;
  }
  // Initializing output TTree
  TTree * TreeOut = new TTree ("E15190", "Calibrated Data");
  if(fIsNWA) TreeOut->Branch("NWA.","NeutronWallCalibratedData",&fNWACalibratedData,32000,2);
  if(fIsNWB) TreeOut->Branch("NWB.","NeutronWallCalibratedData",&fNWBCalibratedData,32000,2);
  if(fIsVW) TreeOut->Branch("VetoWall.","VetoWallCalibratedData",&fVetoWallCalibratedData,32000,2);
  if(fIsFA) TreeOut->Branch("ForwardArray.","ForwardArrayCalibratedData",&fForwardArrayCalibratedData,32000,2);

  TreeOut->SetAutoSave(5000000);

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

    BuildCalibratedEvent();

    TreeOut->Fill();
  }

  //Save Output Tree to file
  TreeOut->AutoSave();

  // closing output file
  FileOut->Close();
}
