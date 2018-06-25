#include <NWReader.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

int main (int argc, char ** argv)
{
  if(argc<=1) return -1;
  std::string data_path("./output/");
  TChain *dataChain = (TChain*) new TChain("E15190");
  Long64_t evt_amount=0;
  if(argc==3) {
    evt_amount=atoi(argv[2]);
  }
  int n_files = dataChain->Add(argv[1]);
  if(n_files<1) return -1;
  printf("Root file %s added to chain\n", argv[1]);
  std::string file_name(argv[1]);
  std::string run_range(file_name.substr(file_name.find(".root")-10, 10));

  NWReader NWAnalyzer(dataChain, "NWB FA", 1);

  std::string FileOutName(Form("output/FANW_ToFHistograms%s.root", run_range.c_str()));
  NWAnalyzer.CreateNWToFPlots(FileOutName.c_str(), evt_amount);

  return 0;
}
