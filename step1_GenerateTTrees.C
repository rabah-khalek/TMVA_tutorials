#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <iostream>
#include "TString.h"

//Declaring the function
void Generate(TString);

//The main function (Do not change it)
void step1_GenerateTTrees(){
  Generate("signal");
  Generate("background");
  Generate("validation");
  gSystem->Exec("mv *.root data/.");
}

//The only function to generate the three sets: signal, background, validation (see data/ directory)
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

  //NOTE
  //Write part 1) here

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

  //NOTE
  //Write part 2) here

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

  //NOTE
  //Write part 3) here

  /*------------------------------------------------------------------------------
4) Write the TTree into a new file
  | example |
  |> TFile * file = 0;
  |> file = TFile::Open("signal.root","RECREATE");
  |> tree->Print();
  |> tree->Write();
  |> delete file;
  ------------------------------------------------------------------------------*/

  //NOTE
  //Write part 4) here

}
