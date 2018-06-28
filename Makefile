CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore
ROOTCLINGORCINT   := rootcling

SrcSuf    := cpp
ObjSuf    := o
DepSuf    := h
PcmSuf    := _rdict.pcm

OBJS := NWReader.$(ObjSuf) NWReaderData.$(ObjSuf) NWReaderCustomized.$(ObjSuf) shared.$(ObjSuf)
OBJS += HTNeutronWallRootEvent.$(ObjSuf) HTForwardArrayRootEvent.$(ObjSuf) HTVetoWallRootEvent.$(ObjSuf)
OBJS += NWPositionCalibration.$(ObjSuf) NWCosmicRayManager.$(ObjSuf) NWTimeCalibration.$(ObjSuf) NWPulseHeightCalibration.$(ObjSuf) NWGeometry.$(ObjSuf)
OBJS += FATimeCalibration.$(ObjSuf)
OBJS += NWCalibratedRootEvent.$(ObjSuf)
DEPS := $(_OBJS:.$(ObjSuf)=.$(DepSuf))

ROOTHTNW_HDRS  := HTNeutronWallRootEvent.h HTNeutronWallLinkDef.h
ROOTHTNW_DICT  := HTNeutronWallDict.$(SrcSuf)
ROOTHTNW_DICTH := $(ROOTHTNW_DICT:.$(SrcSuf)=.h)
ROOTHTNW_DICTO := $(ROOTHTNW_DICT:.$(SrcSuf)=.$(ObjSuf))
ROOTHTNW_PCM   := HTNeutronWallDict$(PcmSuf)

ROOTHTVW_HDRS  := HTVetoWallRootEvent.h HTVetoWallLinkDef.h
ROOTHTVW_DICT  := HTVetoWallDict.$(SrcSuf)
ROOTHTVW_DICTH := $(ROOTHTVW_DICT:.$(SrcSuf)=.h)
ROOTHTVW_DICTO := $(ROOTHTVW_DICT:.$(SrcSuf)=.$(ObjSuf))
ROOTHTVW_PCM   := HTVetoWallDict$(PcmSuf)

ROOTHTFA_HDRS  := HTForwardArrayRootEvent.h HTForwardArrayLinkDef.h
ROOTHTFA_DICT  := HTForwardArrayDict.$(SrcSuf)
ROOTHTFA_DICTH := $(ROOTHTFA_DICT:.$(SrcSuf)=.h)
ROOTHTFA_DICTO := $(ROOTHTFA_DICT:.$(SrcSuf)=.$(ObjSuf))
ROOTHTFA_PCM   := HTForwardArrayDict$(PcmSuf)

ROOTNWCALIBRATED_HDRS  := NWCalibratedRootEvent.h NWCalibratedLinkDef.h
ROOTNWCALIBRATED_DICT  := NWCalibratedDict.$(SrcSuf)
ROOTNWCALIBRATED_DICTH := $(ROOTNWCALIBRATED_DICT:.$(SrcSuf)=.h)
ROOTNWCALIBRATED_DICTO := $(ROOTNWCALIBRATED_DICT:.$(SrcSuf)=.$(ObjSuf))
ROOTNWCALIBRATED_PCM   := NWCalibratedDict$(PcmSuf)

INCLUDES  := -I./include

PROG      := $(wildcard exec_*.$(SrcSuf))
PROG      := $(patsubst %.$(SrcSuf), %, $(PROG))

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3

all: $(PROG)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(PcmSuf)

$(PROG): $(OBJS) $(ROOTHTNW_DICTO) $(ROOTHTVW_DICTO) $(ROOTHTFA_DICTO) $(ROOTNWCALIBRATED_DICTO)
	$(CXX) $(CXXFLAGS) -o ${@} ${@}.cpp $^ $(SYSLIB) $(CFLAGS) $(RLIBS)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

$(ROOTHTNW_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTNW_HDRS)

$(ROOTHTVW_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTVW_HDRS)

$(ROOTHTFA_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTHTFA_HDRS)

$(ROOTNWCALIBRATED_DICT):
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $(ROOTNWCALIBRATED_HDRS)

.PHONY: clean
clean:
	@$(RM) -f $(OBJS) $(ROOTHTNW_DICT) $(ROOTHTNW_PCM) $(ROOTHTNW_DICTO) $(ROOTHTNW_DICTH) $(ROOTHTVW_DICT) $(ROOTHTVW_PCM) $(ROOTHTVW_DICTO) $(ROOTHTVW_DICTH) $(ROOTHTFA_DICT) $(ROOTHTFA_PCM) $(ROOTHTFA_DICTO) $(ROOTHTFA_DICTH) $(ROOTHTMB_DICT) $(ROOTHTMB_PCM) $(ROOTHTMB_DICTO) $(ROOTHTMB_DICTH) $(ROOTNWCALIBRATED_DICT) $(ROOTNWCALIBRATED_PCM) $(ROOTNWCALIBRATED_DICTO) $(ROOTNWCALIBRATED_DICTH)
	@echo "$(RM) -f $(OBJS) $(ROOTHTNW_DICT) $(ROOTHTNW_PCM) $(ROOTHTNW_DICTO) $(ROOTHTNW_DICTH) $(ROOTHTVW_DICT) $(ROOTHTVW_PCM) $(ROOTHTVW_DICTO) $(ROOTHTVW_DICTH) $(ROOTHTFA_DICT) $(ROOTHTFA_PCM) $(ROOTHTFA_DICTO) $(ROOTHTFA_DICTH) $(ROOTHTMB_DICT) $(ROOTHTMB_PCM) $(ROOTHTMB_DICTO) $(ROOTHTMB_DICTH) $(ROOTNWCALIBRATED_DICT) $(ROOTNWCALIBRATED_PCM) $(ROOTNWCALIBRATED_DICTO) $(ROOTNWCALIBRATED_DICTH)"
