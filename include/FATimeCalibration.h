#ifndef FATIMECALIBRATION_H
#define FATIMECALIBRATION_H

#include <fstream>
#include <sstream>
#include <string>

class FATimeCalibration
{
public:
  FATimeCalibration(int);
  ~FATimeCalibration();

  int LoadCalibration(const char *);

  double GetTimeOffset(int num_det) const;

private:
  int fNumDetectors;
  double *fTimeOffset;

  bool fCalibrationLoaded;

};

#endif
