#ifndef NWCALIBRATEDROOTEVENT_H
#define NWCALIBRATEDROOTEVENT_H

#include <TROOT.h>

class NeutronWallCalibratedData
{
public:
  Int_t    fmulti;
  Int_t    *fnumbar;      //[fmulti]
  Short_t  *fLeft;        //[fmulti]
  Short_t  *fRight;       //[fmulti]
  Short_t  *ffastLeft;    //[fmulti]
  Short_t  *ffastRight;   //[fmulti]
  Double_t *fTimeLeft;    //[fmulti]
  Double_t *fTimeRight;   //[fmulti]
  Double_t *fGeoMean;     //[fmulti]
  Double_t *ffastGeoMean; //[fmulti]

  Double_t *fTimeMean;    //[fmulti]
  Double_t *fCalGeoMean;  //[fmulti]
  Double_t *fMatchedLeft; //[fmulti]
  Double_t *fMatchedRight;//[fmulti]
  Double_t *fXcm;         //[fmulti]

  NeutronWallCalibratedData(int);
  NeutronWallCalibratedData();
  virtual ~NeutronWallCalibratedData();

  ClassDef(NeutronWallCalibratedData,1);
};

class ForwardArrayCalibratedData
{
public:
  Int_t    fmulti;
  Int_t    *fnumdet;      //[fmulti]
  Short_t  *fE;           //[fmulti]
  Double_t *fTime;        //[fmulti]

  Double_t *fECal;        //[fmulti]

  Double_t fTimeMean;
  Double_t fTimeStart;


  ForwardArrayCalibratedData(int);
  ForwardArrayCalibratedData();
  virtual ~ForwardArrayCalibratedData();

  ClassDef(ForwardArrayCalibratedData,1);
};

#endif
