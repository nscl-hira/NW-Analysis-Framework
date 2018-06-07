#ifndef NWREADER_H
#define NWREADER_H

#include <string.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TChain.h>
#include <TMath.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TCutG.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TCanvas.h>
#include "HTNeutronWallRootEvent.h"
#include "HTForwardArrayRootEvent.h"
#include "HTVetoWallRootEvent.h"
#include "NWPositionCalibration.h"
#include "NWCosmicRayManager.h"
#include "NWCalibratedRootEvent.h"
#include "NWTimeCalibration.h"
#include "FATimeCalibration.h"

#include "shared.h"


class NWReader
{
public :
  NWReader(TChain * Chain=0, bool IsDataCalibrated=0);
  ~NWReader();

  int LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWPulseHeightCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWCosmicRayPosition(const char *, const char * WallToCalibrate);
  int LoadFATimeCalibration(const char * file_name);

  double GetNWAXcm(int num_bar, double tleft, double tright) const;
  double GetNWBXcm(int num_bar, double tleft, double tright) const;
  double GetNWACosmicCenter(int num_bar) const;
  double GetNWACosmicStartingPoint(int num_bar) const;
  double GetNWBCosmicCenter(int num_bar) const;
  double GetNWBCosmicStartingPoint(int num_bar) const;
  double GetNWATimeMean(int num_bar, double tleft, double tright) const;
  double GetNWBTimeMean(int num_bar, double tleft, double tright) const;
  double GetFATimeOffset(int num_det) const;

  // Examples
  void   Loop(const char *, Long64_t evt_amount=0);
  void   LoopOnCalibratedData(const char *, Long64_t evt_amount=0);

  // Output data methods
  void   BuildCosmicRayData(const char *, Long64_t evt_amount=0);
  void   BuildCalibratedTree(const char *, Long64_t evt_amount=0);
  void   BuildCalibratedEvent();

  // Customized methods
  void   CreateNWCosmicsUsefulPlots(const char *, Long64_t evt_amount=0);
  void   CreateNWToFPlots(const char *, Long64_t evt_amount=0);

private :
  TTreeReader * fNWReader;
  TTreeReaderValue<HTNeutronWallData> *fNWA;
  TTreeReaderValue<HTNeutronWallData> *fNWB;
  TTreeReaderValue<HTForwardArrayData> *fForwardArray;
  TTreeReaderValue<HTVetoWallData> *fVetoWall;
  TTreeReaderValue<NeutronWallCalibratedData> *fNWACal;
  TTreeReaderValue<NeutronWallCalibratedData> *fNWBCal;
  TTreeReaderValue<ForwardArrayCalibratedData> *fForwardArrayCal;

  NeutronWallCalibratedData fNWACalibratedData;
  NeutronWallCalibratedData fNWBCalibratedData;
  ForwardArrayCalibratedData fForwardArrayCalibratedData;

  TChain      * fChain;

  double fDegToRad;
  double fRadToDeg;
  double fSpeedOfLight;    //cm/ns
  double fNWBarLength;     //cm
  double fNWBarHigh;       //cm
  double fNWBarThickness;  //cm

  bool fIsDataCalibrated;
  bool fNWAPositionCalibrated;
  bool fNWBPositionCalibrated;
  bool fNWTimeCalibrated;
  bool fNWPulseHeightCalibrated;
  bool fNWACosmicRayPositionLoaded;
  bool fNWBCosmicRayPositionLoaded;
  bool fNWATimeCalibrated;
  bool fNWBTimeCalibrated;
  bool fFATimeCalibrated;

  NWPositionCalibration * fNWBPositionCalibration;
  NWPositionCalibration * fNWAPositionCalibration;
  NWCosmicRayManager    * fNWACosmicRayInfo;
  NWCosmicRayManager    * fNWBCosmicRayInfo;
  NWTimeCalibration     * fNWATimeCalibration;
  NWTimeCalibration     * fNWBTimeCalibration;
  FATimeCalibration     * fFATimeCalibration;
};

#endif
