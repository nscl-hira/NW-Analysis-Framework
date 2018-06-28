#include "include/NWPulseHeightCalibration.h"

//____________________________________________________
NWPulseHeightCalibration::NWPulseHeightCalibration(int TotNumBars) :
fNumBars(TotNumBars),
fRightMatchingParameters(new double[fNumBars]),
fLeftMatchingParameters(new double[fNumBars]),
fMatchingLoaded(false),
fCalibrationLoaded(false),
fPositionCorrectionLoaded(false)
{}

//____________________________________________________
NWPulseHeightCalibration::~NWPulseHeightCalibration()
{
  delete [] fRightMatchingParameters;
  delete [] fLeftMatchingParameters;
}

//____________________________________________________
int NWPulseHeightCalibration::LoadMatching(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string DetName;
    double peakleft;
    double peakright;
    double requiredposition;

    LineStream>>DetName>>peakleft>>peakright>>requiredposition;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fRightMatchingParameters[NumBar]=requiredposition/peakright;
    fLeftMatchingParameters[NumBar]=requiredposition/peakleft;

    NRead++;
  }

  NRead>0 ? fMatchingLoaded=true : fMatchingLoaded=false;
  return NRead;
}

//____________________________________________________
double NWPulseHeightCalibration::GetLeftMatched(double ch, int numbar) const
{
  return fMatchingLoaded ? gRandom->Uniform(ch-0.5, ch+0.5)*fLeftMatchingParameters[numbar-1] : -9999;
}

//____________________________________________________
double NWPulseHeightCalibration::GetRightMatched(double ch, int numbar) const
{
  return fMatchingLoaded ? gRandom->Uniform(ch-0.5, ch+0.5)*fRightMatchingParameters[numbar-1] : -9999;
}
