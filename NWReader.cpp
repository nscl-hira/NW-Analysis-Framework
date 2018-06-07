#include "include/NWReader.h"

//____________________________________________________
NWReader::NWReader(TChain *Chain, bool IsDataCalibrated) :
fChain(Chain),
fDegToRad(TMath::Pi()/180.),
fRadToDeg(180./TMath::Pi()),
fSpeedOfLight(29.9792),
fNWBarLength(200),
fNWBarHigh(7.62),
fNWBarThickness(6.35),
fIsDataCalibrated(IsDataCalibrated),
fNWAPositionCalibrated(false),
fNWBPositionCalibrated(false),
fNWTimeCalibrated(false),
fNWPulseHeightCalibrated(false),
fNWACosmicRayPositionLoaded(false),
fNWBCosmicRayPositionLoaded(false),
fNWATimeCalibrated(false),
fNWBTimeCalibrated(false),
fNWAPositionCalibration(0),
fNWBPositionCalibration(0),
fNWACosmicRayInfo(0),
fNWBCosmicRayInfo(0),
fNWATimeCalibration(0),
fNWBTimeCalibration(0)
{
  if(fChain!=0) {
    fNWReader = new TTreeReader(fChain);
    if(!fIsDataCalibrated) {
      fNWA = new TTreeReaderValue<HTNeutronWallData>(*fNWReader, "NWA.");
      fNWB = new TTreeReaderValue<HTNeutronWallData>(*fNWReader, "NWB.");
      fForwardArray = new TTreeReaderValue<HTForwardArrayData>(*fNWReader, "ForwardArray.");
      fVetoWall = new TTreeReaderValue<HTVetoWallData>(*fNWReader, "VetoWall.");
    } else {
      fNWACal = new TTreeReaderValue<NeutronWallCalibratedData>(*fNWReader, "NWA.");
      fNWBCal = new TTreeReaderValue<NeutronWallCalibratedData>(*fNWReader, "NWB.");
      fForwardArrayCal = new TTreeReaderValue<ForwardArrayCalibratedData>(*fNWReader, "ForwardArray.");
    }
  }
  fNWAPositionCalibration = new NWPositionCalibration(NUM_BARS_NWA);
  fNWBPositionCalibration = new NWPositionCalibration(NUM_BARS_NWB);
  fNWACosmicRayInfo = new NWCosmicRayManager(NUM_BARS_NWA);
  fNWBCosmicRayInfo = new NWCosmicRayManager(NUM_BARS_NWB);
  fNWATimeCalibration = new NWTimeCalibration(NUM_BARS_NWA);
  fNWBTimeCalibration = new NWTimeCalibration(NUM_BARS_NWB);
  fFATimeCalibration = new FATimeCalibration(NUM_DETECTORS_FA);
}

//____________________________________________________
NWReader::~NWReader()
{
  if(fChain!=0) {
    if(!fIsDataCalibrated) {
      delete fNWReader;
      delete fNWA;
      delete fNWB;
      delete fForwardArray;
      delete fVetoWall;
    } else {
      delete fNWACal;
      delete fNWBCal;
    }
  }

  if(fNWAPositionCalibration) delete fNWAPositionCalibration;
  if(fNWBPositionCalibration) delete fNWBPositionCalibration;
  if(fNWACosmicRayInfo) delete fNWACosmicRayInfo;
  if(fNWBCosmicRayInfo) delete fNWBCosmicRayInfo;
  if(fNWATimeCalibration) delete fNWATimeCalibration;
  if(fNWBTimeCalibration) delete fNWBTimeCalibration;
  if(fFATimeCalibration) delete fFATimeCalibration;
}

//____________________________________________________
int NWReader::LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWAPositionCalibrated=true;
      return NLines;
    }
    fNWAPositionCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBPositionCalibrated=true;
      return NLines;
    }
    fNWBPositionCalibrated=false;
  }

  printf("Error: Error while loading NW Position calibration file %s\n", file_name);
  return -1;
}

//____________________________________________________
int NWReader::LoadNWCosmicRayPosition(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWACosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWACosmicRayPositionLoaded=true;
      return NLines;
    }
    fNWACosmicRayPositionLoaded=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBCosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWBCosmicRayPositionLoaded=true;
      return NLines;
    }
    fNWBCosmicRayPositionLoaded=false;
  }

  printf("Error: Error while loading NW cosmic ray positions %s\n", file_name);
  return -1;
}

//____________________________________________________
int NWReader::LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWATimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWATimeCalibrated=true;
      return NLines;
    }
    fNWATimeCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBTimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBTimeCalibrated=true;
      return NLines;
    }
    fNWBTimeCalibrated=false;
  }

  printf("Error: Error while loading NW time calibration %s\n", file_name);
  return -1;
}

//____________________________________________________
int NWReader::LoadFATimeCalibration(const char * file_name)
{
  int NLines=fFATimeCalibration->LoadCalibration(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
double NWReader::GetNWAXcm(int num_bar, double tleft, double tright) const
{
  return fNWAPositionCalibrated ? fNWAPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double NWReader::GetNWBXcm(int num_bar, double tleft, double tright) const
{
  return fNWBPositionCalibrated ? fNWBPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double NWReader::GetNWACosmicCenter(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetNWACosmicStartingPoint(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetNWBCosmicCenter(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetNWBCosmicStartingPoint(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetNWATimeMean(int num_bar, double tleft, double tright) const
{
  return fNWATimeCalibrated ? 0.5*(tleft+tright)-fNWATimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetNWBTimeMean(int num_bar, double tleft, double tright) const
{
  return fNWBTimeCalibrated ? 0.5*(tleft+tright)-fNWBTimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double NWReader::GetFATimeOffset(int num_det) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimeOffset(num_det) : 0;
}

//____________________________________________________
void NWReader::Loop(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

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

    HTNeutronWallData * NWA = fNWA->Get();
    HTNeutronWallData * NWB = fNWB->Get();
    HTVetoWallData * VetoWall = fVetoWall->Get();
    HTForwardArrayData * ForwardArray = fForwardArray->Get();

    // Insert here code

    jentry++;
  }

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void NWReader::LoopOnCalibratedData(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

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

    // Insert here code

    jentry++;
  }

  // closing output file
  FileOut->Close();
}
