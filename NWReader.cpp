#include "include/NWReader.h"

//____________________________________________________
NWReader::NWReader(TChain *Chain, const char * DataType, bool IsDataCalibrated) :
fChain(Chain),
fDegToRad(TMath::Pi()/180.),
fRadToDeg(180./TMath::Pi()),
fSpeedOfLight(29.9792),
fNWBarLength(200),
fNWBarHigh(7.62),
fNWBarThickness(6.35),
fIsNWA(false),
fIsNWB(false),
fIsFA(false),
fIsVW(false),
fIsDataCalibrated(IsDataCalibrated),
fNWAPositionCalibrated(false),
fNWBPositionCalibrated(false),
fNWTimeCalibrated(false),
fNWPulseHeightCalibrated(false),
fNWACosmicRayPositionLoaded(false),
fNWBCosmicRayPositionLoaded(false),
fNWATimeCalibrated(false),
fNWBTimeCalibrated(false),
fNWAGeometryCalibrated(false),
fNWBGeometryCalibrated(false),
fNWAPulseHeightMatched(false),
fNWBPulseHeightMatched(false),
fNWAPulseHeightCalibrated(false),
fNWBPulseHeightCalibrated(false),
fFATimeCalibrated(false),
fNWAPositionCalibration(new NWPositionCalibration(NUM_BARS_NWA)),
fNWBPositionCalibration(new NWPositionCalibration(NUM_BARS_NWB)),
fNWACosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWA)),
fNWBCosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWB)),
fNWATimeCalibration(new NWTimeCalibration(NUM_BARS_NWA)),
fNWBTimeCalibration(new NWTimeCalibration(NUM_BARS_NWB)),
fNWAGeometry(new NWGeometry(NUM_BARS_NWA)),
fNWBGeometry(new NWGeometry(NUM_BARS_NWB)),
fNWAPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWA)),
fNWBPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWB)),
fFATimeCalibration(new FATimeCalibration(NUM_DETECTORS_FA))
{
  //Parsing DataType string to allocate specific detectors
  std::string DetectorsIncluded(DataType);
  std::istringstream StreamDetectorsIncluded(DetectorsIncluded);
  std::string DetectorToAdd;
  while (StreamDetectorsIncluded>>DetectorToAdd) {
    if(DetectorToAdd.compare("NWA")==0) fIsNWA=true;
    if(DetectorToAdd.compare("NWB")==0) fIsNWB=true;
    if(DetectorToAdd.compare("FA")==0) fIsFA=true;
    if(DetectorToAdd.compare("VW")==0) fIsVW=true;
  }

  if(fChain!=0) {
    fNWReader = new TTreeReader(fChain);
    if(!fIsDataCalibrated) {
      if(fIsNWA) fNWA = new TTreeReaderValue<HTNeutronWallData>(*fNWReader, "NWA.");
      if(fIsNWB) fNWB = new TTreeReaderValue<HTNeutronWallData>(*fNWReader, "NWB.");
      if(fIsFA) fForwardArray = new TTreeReaderValue<HTForwardArrayData>(*fNWReader, "ForwardArray.");
      if(fIsVW) fVetoWall = new TTreeReaderValue<HTVetoWallData>(*fNWReader, "VetoWall.");
    } else {
      if(fIsNWA) fNWACal = new TTreeReaderValue<NeutronWallCalibratedData>(*fNWReader, "NWA.");
      if(fIsNWB) fNWBCal = new TTreeReaderValue<NeutronWallCalibratedData>(*fNWReader, "NWB.");
      if(fIsFA) fForwardArrayCal = new TTreeReaderValue<ForwardArrayCalibratedData>(*fNWReader, "ForwardArray.");
      if(fIsVW) fVetoWallCal = new TTreeReaderValue<VetoWallCalibratedData>(*fNWReader, "VetoWall.");
    }
  }
}

//____________________________________________________
NWReader::~NWReader()
{
  if(fChain!=0) {
    delete fNWReader;
    if(!fIsDataCalibrated) {
      if (fIsNWA) delete fNWA;
      if (fIsNWB) delete fNWB;
      if (fIsFA) delete fForwardArray;
      if (fIsVW) delete fVetoWall;
    } else {
      if (fIsNWA) delete fNWACal;
      if (fIsNWB) delete fNWBCal;
      if (fIsFA) delete fForwardArrayCal;
      if (fIsVW) delete fVetoWallCal;
    }
  }

  if(fNWAPositionCalibration) delete fNWAPositionCalibration;
  if(fNWBPositionCalibration) delete fNWBPositionCalibration;
  if(fNWACosmicRayInfo) delete fNWACosmicRayInfo;
  if(fNWBCosmicRayInfo) delete fNWBCosmicRayInfo;
  if(fNWATimeCalibration) delete fNWATimeCalibration;
  if(fNWBTimeCalibration) delete fNWBTimeCalibration;
  if(fFATimeCalibration) delete fFATimeCalibration;
  if(fNWAGeometry) delete fNWAGeometry;
  if(fNWBGeometry) delete fNWBGeometry;
}

//____________________________________________________
int NWReader::LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWAPositionCalibrated=true;
      printf("Loaded position calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWAPositionCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBPositionCalibrated=true;
      printf("Loaded position calibration for NWB %s\n", file_name);
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
      printf("Loaded cosmics calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWACosmicRayPositionLoaded=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBCosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWBCosmicRayPositionLoaded=true;
      printf("Loaded cosmics calibration for NWB %s\n", file_name);
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
      printf("Loaded time calibration for NWA %s\n", file_name);
      return NLines;
    }
    fNWATimeCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBTimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBTimeCalibrated=true;
      printf("Loaded time calibration for NWB %s\n", file_name);
      return NLines;
    }
    fNWBTimeCalibrated=false;
  }

  printf("Error: Error while loading NW time calibration %s\n", file_name);
  return -1;
}

//____________________________________________________
int NWReader::LoadNWGeometryFiducialPoints(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    int NLines=fNWAGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWAGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWA %s\n", file_name);
      return NLines;
    }
    fNWAGeometryCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    int NLines=fNWBGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWBGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWB %s\n", file_name);
      return NLines;
    }
    fNWBGeometryCalibrated=false;
  }

  printf("Error: Error while loading NW geometry fiducial points %s\n", file_name);
  return -1;
}

//____________________________________________________
int NWReader::LoadFATimeCalibration(const char * file_name)
{
  int NLines=fFATimeCalibration->LoadCalibration(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time calibration for FA %s\n", file_name);
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int NWReader::LoadFATimePulseHeightCorrection(const char * file_name)
{
  int NLines=fFATimeCalibration->LoadPulseHeightCorrection(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time pulse height correction for FA %s\n", file_name);
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
double NWReader::GetNWATheta(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWAPhi(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWAThetaRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWAPhiRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWADistance(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWADistanceRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBTheta(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBPhi(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBThetaRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBPhiRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBDistance(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetNWBDistanceRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double NWReader::GetFATimePulseHeightCorrection(int num_det, double pulse_height) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimePulseHeightCorrection(num_det, pulse_height) : 0;
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

    if (fIsNWA) {
      NeutronWallCalibratedData * NWA = fNWACal->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      NeutronWallCalibratedData * NWB = fNWBCal->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      HTForwardArrayData * ForwardArray = fForwardArray->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      HTVetoWallData * VetoWall = fVetoWall->Get();
      //Insert VetoWall code here
    }

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

    if (fIsNWA) {
      NeutronWallCalibratedData * NWA = fNWACal->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      NeutronWallCalibratedData * NWB = fNWBCal->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      VetoWallCalibratedData * VetoWall = fVetoWallCal->Get();
      //Insert VetoWall code here
    }

    // Insert here code

    jentry++;
  }

  // closing output file
  FileOut->Close();
}
