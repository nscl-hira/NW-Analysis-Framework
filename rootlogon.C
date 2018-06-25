{
  gROOT->ProcessLine(".L lib/HTNeutronWallDict.so");
  gROOT->ProcessLine(".L lib/HTVetoWallDict.so");
  gROOT->ProcessLine(".L lib/HTForwardArrayDict.so");
  gROOT->ProcessLine(".L lib/NWCalibratedDict.so");
  gROOT->ProcessLine(".L shared.cpp");
  gROOT->ProcessLine(".L NWReader.cpp");
  gROOT->ProcessLine(".L NWReaderData.cpp");
  gROOT->ProcessLine(".L NWReaderCustomized.cpp");
  gROOT->ProcessLine(".L NWCosmicRayManager.cpp");
  gROOT->ProcessLine(".L NWPositionCalibration.cpp");
  gROOT->ProcessLine(".L NWTimeCalibration.cpp");
  gROOT->ProcessLine(".L NWGeometry.cpp");
  gROOT->ProcessLine(".L FATimeCalibration.cpp");
}
