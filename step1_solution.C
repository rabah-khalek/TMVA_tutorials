//===============TOPICAL LECTURES AT NIKHEF - TMVA TUTORIAL ====================
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <iostream>
#include "TString.h"

//Declaring the function
void Generate(TString);

//The main function (Do not change it)
void step1_solution(){
  Generate("signal");
  Generate("background");
  Generate("validation");
  gSystem->Exec("mv *.root data/.");
}

//The only function to generate the three sets: signal, background,
//validation (see data/ directory)
void Generate(TString fname)
{
  /*
  Description of all the variables provided by the dataset
  --------------------------------------------------------
  1. fLength: (continuous) major axis of ellipse [mm]
  2. fWidth:  (continuous) minor axis of ellipse [mm]
  3. fSize:   (continuous) 10-log of sum of content of all pixels [in #phot]
  4. fConc:   (continuous) ratio of sum of two highest pixels over fSize [ratio]
  5. fConc1:  (continuous) ratio of highest pixel over fSize [ratio]
  6. fAsym:   (continuous) distance from highest pixel to center, projected onto major axis [mm]
  7. fM3Long: (continuous) 3rd root of third moment along major axis [mm]
  8. fM3Trans:(continuous) 3rd root of third moment along minor axis [mm]
  9. fAlpha:  (continuous) angle of major axis with vector to origin [deg]
  10. fDist:  (continuous) distance from origin to center of ellipse [mm]
  11. id:     (discontinuous) 1 if gamma (signal), 0 if hadron (background)
  */

  Float_t fLength,fWidth,fSize,fConc,fConc1,fAsym,fM3Long,fM3Trans,fAlpha,fDist;
  int id;

  //===================================TODO=====================================
  //============================================================================
  
  /*------------------------------------------------------------------------------
1) Open the file according to fname in data/
  | example |
  |> FILE *f = fopen("data/signal.data,"r");
  ------------------------------------------------------------------------------*/

  FILE *fp = fopen("data/"+fname+".data","r");

  /*------------------------------------------------------------------------------
2) Create TTree called "tree" and initiate branches for each variable
  | example |
  |
  |> TTree * tree = new TTree("tree","tree");
  |> float x;
  |> tree->Branch("x",&x,"x/F");
  |
  | according to tree->Branch("variable_name",&variable_name,"variable_name/variable_type");
  ------------------------------------------------------------------------------*/

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

  /*------------------------------------------------------------------------------
3) Fill the tree from the according .data file in data/
  | example |
  | Suppose your txt (something.data) file contains these 2 lines:
  |  0.1, 0.1, 0.1, 1
  |  0.2, 0.2, 0.2, 0
  | to load this file into a tree:
  |
  |> char line[n] \\where n is the maximum number of characters one can find in all lines
  |> while(fgets(line,n,f)) \\ where f is the FILE you created
  |> {sscanf(&line[0],"%f, %f, %f, %d ", &var1,  &var2,  &var3,  &var4);
  |> tree->Fill();}
  |
  | sscanf will scan the values in the txt file according to their types (f for float, d for integer)
  ------------------------------------------------------------------------------*/

  char line[100];
  while (fgets(line,100,fp))
  {
    sscanf(&line[0],"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d ",
    &fLength,&fWidth,&fSize,&fConc,&fConc1,&fAsym,&fM3Long,&fM3Trans,&fAlpha,&fDist,&id);
    tree->Fill();
  }

  /*------------------------------------------------------------------------------
4) Write the TTree into a new file
  | example |
  |> TFile * file = 0;
  |> file = TFile::Open("signal.root","RECREATE");
  |> tree->Print();
  |> tree->Write();
  |> delete file;
  ------------------------------------------------------------------------------*/

  TFile * file=0;
  file = TFile::Open(fname+".root","RECREATE");
  tree->Print();
  tree->Write();
  delete file;

}
