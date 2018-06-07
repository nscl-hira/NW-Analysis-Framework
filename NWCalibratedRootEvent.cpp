#include <NWCalibratedRootEvent.h>

//________________________________________________
NeutronWallCalibratedData::NeutronWallCalibratedData(int num_bars) :
fmulti(0)
{
  fnumbar      =new Int_t   [num_bars];
  fLeft        =new Short_t [num_bars];
  fRight       =new Short_t [num_bars];
  ffastLeft    =new Short_t [num_bars];
  ffastRight   =new Short_t [num_bars];
  fTimeLeft    =new Double_t[num_bars];
  fTimeRight   =new Double_t[num_bars];
  fGeoMean     =new Double_t[num_bars];
  ffastGeoMean =new Double_t[num_bars];

  fTimeMean    =new Double_t[num_bars];
  fCalGeoMean  =new Double_t[num_bars];
  fMatchedLeft =new Double_t[num_bars];
  fMatchedRight=new Double_t[num_bars];
  fXcm         =new Double_t[num_bars];
}

//________________________________________________
NeutronWallCalibratedData::NeutronWallCalibratedData() :
fmulti(0)
{
  fnumbar      =new Int_t   [25];
  fLeft        =new Short_t [25];
  fRight       =new Short_t [25];
  ffastLeft    =new Short_t [25];
  ffastRight   =new Short_t [25];
  fTimeLeft    =new Double_t[25];
  fTimeRight   =new Double_t[25];
  fGeoMean     =new Double_t[25];
  ffastGeoMean =new Double_t[25];

  fTimeMean    =new Double_t[25];
  fCalGeoMean  =new Double_t[25];
  fMatchedLeft =new Double_t[25];
  fMatchedRight=new Double_t[25];
  fXcm         =new Double_t[25];
}

//________________________________________________
NeutronWallCalibratedData::~NeutronWallCalibratedData()
{
  delete [] fnumbar   ;
  delete [] fLeft     ;
  delete [] fRight    ;
  delete [] ffastLeft ;
  delete [] ffastRight;
  delete [] fTimeLeft ;
  delete [] fTimeRight;
  delete [] fGeoMean  ;
  delete [] ffastGeoMean;

  delete [] fTimeMean;
  delete [] fCalGeoMean;
  delete [] fMatchedLeft;
  delete [] fMatchedRight;
  delete [] fXcm;
}

//________________________________________________
ForwardArrayCalibratedData::ForwardArrayCalibratedData(int num_dets) :
fmulti(0)
{
  fnumdet      =new Int_t   [num_dets];
  fE           =new Short_t [num_dets];
  fTime        =new Double_t[num_dets];

  fECal        =new Double_t[num_dets];
}

//________________________________________________
ForwardArrayCalibratedData::ForwardArrayCalibratedData() :
fmulti(0)
{
  fnumdet      =new Int_t   [18];
  fE           =new Short_t [18];
  fTime        =new Double_t[18];

  fECal        =new Double_t[18];
}

//________________________________________________
ForwardArrayCalibratedData::~ForwardArrayCalibratedData()
{
  delete [] fnumdet;
  delete [] fE;
  delete [] fTime;

  delete [] fECal;
}
