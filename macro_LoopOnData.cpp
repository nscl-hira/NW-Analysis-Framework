#include "include/NWReader.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

void macro_LoopOnData(int first_run, int last_run=-1, int evt_amount=0)
{
  std::string data_path("/mnt/analysis/e15190/HiRAEVTMapper_rootfiles/");
  TChain *dataChain = (TChain*) new TChain("E15190");
  if(last_run==-1) {
    last_run=first_run;
  }
  // Adding all the files to the TChain ================================
  for(int i=first_run; i<=last_run; i++)
  {
    char file_evt[100];
    sprintf (file_evt,"run-%04d*.root",i);
    std::string file_evt_string(file_evt);
    std::string path_to_evt_file(data_path+file_evt_string);
    int n_files = dataChain->Add((data_path+file_evt).c_str());
    printf("%d Root files added to chain for run %d\n", n_files, i);
  }


  NWReader NWAnalyzer(dataChain);

  std::string FileOutName(Form("output/output_%04d_%04d.root", first_run, last_run));

  NWAnalyzer.Loop(FileOutName.c_str(), evt_amount);

  return;
}
