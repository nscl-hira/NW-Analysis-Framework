#ifndef NWPULSEHEIGHTCALIBRATION_H
#define NWPULSEHEIGHTCALIBRATION_H

#include <string>
#include <fstream>
#include <sstream>
#include <TRandom3.h>

class NWPulseHeightCalibration
{
public :
  NWPulseHeightCalibration(int TotNumBars);
  ~NWPulseHeightCalibration();

  int LoadMatching(const char *);
  int LoadCalibration(const char *);

  double GetLeftMatched(double ch, int numbar) const;
  double GetRightMatched(double ch, int numbar) const;

private :
  int fNumBars;
  double * fRightMatchingParameters;
  double * fLeftMatchingParameters;

  bool fMatchingLoaded;
  bool fCalibrationLoaded;
  bool fPositionCorrectionLoaded;

};

#endif
