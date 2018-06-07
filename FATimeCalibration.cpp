#include "include/FATimeCalibration.h"

//____________________________________________________
FATimeCalibration::FATimeCalibration(int num_dets) :
fNumDetectors(num_dets),
fTimeOffset(0),
fCalibrationLoaded(false)
{
  fTimeOffset=new double[fNumDetectors];
}

//____________________________________________________
FATimeCalibration::~FATimeCalibration()
{
  if(fTimeOffset) delete [] fTimeOffset;
}

//____________________________________________________
int FATimeCalibration::LoadCalibration(const char * file_name)
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

    int det_num;
    double offset;

    LineStream>>det_num>>offset;

    fTimeOffset[det_num-1]=offset;

    NRead++;
  }

  NRead>0 ? fCalibrationLoaded=true : fCalibrationLoaded=false;
  return NRead;
}

//____________________________________________________
double FATimeCalibration::GetTimeOffset(int num_det) const
{
  return fCalibrationLoaded ? fTimeOffset[num_det-1] : 0;
}
