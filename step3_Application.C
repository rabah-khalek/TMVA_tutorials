#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void step3_solution()
{

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   //===================================TODO=====================================
  /*------------------------------------------------------------------------------
  1) Create the Reader object
    ------------------------------------------------------------------------------*/

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

  /*------------------------------------------------------------------------------
  2) Create a set of variables and declare them to the reader
     the variable names MUST corresponds in name and type to those given in the weight file(s) used
     | example |
     |> float x;
     |> reader->AddVariable("x", &x);
    ------------------------------------------------------------------------------*/

    //NOTE
    //Write part 2) here

   /*------------------------------------------------------------------------------
   3) Book the MVA methods
     ------------------------------------------------------------------------------*/

   TString dir    = "dataset/weights/";
   TString prefix = "TMVAClassification";

   // Book method(s)
   TString weightfile = "dataset/weights/TMVAClassification_MLP.weights.xml";
   reader->BookMVA("MLP method",weightfile);

   /*------------------------------------------------------------------------------
   4) Create Three TH1F histograms:
      a. one to evaluate all the events of the validation set
      b. one to evaluate only the gamma events (signal)
      c. one to evaluate only the hadron events (background)

      number of bins = 100
      | example |
      |> TH1F h = new TH1F("hname","hname",100, 0., 1. );
     ------------------------------------------------------------------------------*/

     //NOTE
     //Write part 4) here


   /*------------------------------------------------------------------------------
   5) Open validation file data/validation.root
      and Prepare the validation input tree (see step 1 for help )
      Set Branch addresses and link them to the variables previously defined
      | example |
      |> validation_tree->SetBranchAddress("x", &x);
      | where x is the variable.
     ------------------------------------------------------------------------------*/

     //NOTE
     //Write part 5) here

   /*------------------------------------------------------------------------------
   6) loop over validation events and
      fill the evaluation of the validation events in the three histograms accordingly:
      a. one to evaluate all the events of the validation set
      b. one to evaluate only the gamma events (signal)
      c. one to evaluate only the hadron events (background)
     ------------------------------------------------------------------------------*/

     //NOTE
     //Write part 6) here

   /*------------------------------------------------------------------------------
   7) Write the histograms in a file called "Application_output.root"
     ------------------------------------------------------------------------------*/

   TFile *target  = new TFile( "Application_output.root","RECREATE" );


   histNn     ->Write();
   hist_g     ->Write();
   hist_h     ->Write();

   delete reader;
}
