#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <iostream>
#include "TString.h"

void Generate(TString);

void MAGIC_GenerateTTrees(){
  Generate("signal");
  Generate("background");
  Generate("validation");
  gSystem->Exec("mv *.root data/.");
}

void Generate(TString fname)
{
  /*
  1. fLength: continuous # major axis of ellipse [mm]
  2. fWidth: continuous # minor axis of ellipse [mm]
  3. fSize: continuous # 10-log of sum of content of all pixels [in #phot]
  4. fConc: continuous # ratio of sum of two highest pixels over fSize [ratio]
  5. fConc1: continuous # ratio of highest pixel over fSize [ratio]
  6. fAsym: continuous # distance from highest pixel to center, projected onto major axis [mm]
  7. fM3Long: continuous # 3rd root of third moment along major axis [mm]
  8. fM3Trans: continuous # 3rd root of third moment along minor axis [mm]
  9. fAlpha: continuous # angle of major axis with vector to origin [deg]
  10. fDist: continuous # distance from origin to center of ellipse [mm]
  11. class: g,h # gamma (signal), hadron (background)
  */
    Float_t fLength,fWidth,fSize,fConc,fConc1,fAsym,fM3Long,fM3Trans,fAlpha,fDist;
    int id;

    FILE *fp = fopen("data/"+fname+".data","r");

    TTree * tree = new TTree("tree","tree");
    tree->Branch("fLength",&fLength,"fLength/F");
    tree->Branch("fWidth",&fWidth,"fWidth/F");
    tree->Branch("fSize",&fSize,"fSize/F");
    tree->Branch("fConc",&fConc,"fConc/F");
    tree->Branch("fConc1",&fConc1,"fConc1/F");
    tree->Branch("fAsym",&fAsym,"fAsym/F");
    tree->Branch("fM3Long",&fM3Long,"fM3Long/F");
    tree->Branch("fM3Trans",&fM3Trans,"fM3Trans/F");
    tree->Branch("fAlpha",&fAlpha,"fAlpha/F");
    tree->Branch("fDist",&fDist,"fDist/F");
    tree->Branch("id",&id,"id/I");

    char line[100];
    while (fgets(line,100,fp)) {
      sscanf(&line[0],"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d ",
      &fLength,&fWidth,&fSize,&fConc,&fConc1,&fAsym,&fM3Long,&fM3Trans,&fAlpha,&fDist,&id);

      tree->Fill();
    }

    TFile * file=0;
    file = TFile::Open(fname+".root","RECREATE");
    tree->Print();
    tree->Write();
    delete file;
}
