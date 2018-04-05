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

   Float_t fLength,fWidth,fSize,fConc,fConc1,fAsym,fM3Long,fM3Trans,fAlpha,fDist;
   int id;
   reader->AddVariable( "fLength", &fLength);
   reader->AddVariable( "fWidth", &fWidth);
   reader->AddVariable( "fSize", &fSize);
   reader->AddVariable( "fConc", &fConc);
   reader->AddVariable( "fConc1", &fConc1);
   reader->AddVariable( "fAsym", &fAsym);
   reader->AddVariable( "fM3Long", &fM3Long);
   reader->AddVariable( "fM3Trans", &fM3Trans);
   reader->AddVariable( "fAlpha", &fAlpha);
   reader->AddVariable( "fDist", &fDist);

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

   UInt_t nbin = 100;
   TH1F *histNn(0);
   TH1F *hist_g(0);
   TH1F *hist_h(0);

   histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, 0., 1. );
   hist_g      = new TH1F( "hist_g" ,           "hist_g" ,           nbin, 0., 1. );
   hist_h      = new TH1F( "hist_h" ,           "hist_h" ,           nbin, 0., 1. );


   /*------------------------------------------------------------------------------
   5) Open validation file data/validation.root
      and Prepare the validation input tree (see step 1 for help )
      Set Branch addresses and link them to the variables previously defined
      | example |
      |> validation_tree->SetBranchAddress("x", &x);
      | where x is the variable.
     ------------------------------------------------------------------------------*/

   TFile *input(0);
   TString fname = "data/validation.root";
   input = TFile::Open( fname );

   TTree* validation_tree = (TTree*)input->Get("tree");
   validation_tree->SetBranchAddress( "fLength", &fLength);
   validation_tree->SetBranchAddress( "fWidth", &fWidth);
   validation_tree->SetBranchAddress( "fSize", &fSize);
   validation_tree->SetBranchAddress( "fConc", &fConc);
   validation_tree->SetBranchAddress( "fConc1", &fConc1);
   validation_tree->SetBranchAddress( "fAsym", &fAsym);
   validation_tree->SetBranchAddress( "fM3Long", &fM3Long);
   validation_tree->SetBranchAddress( "fM3Trans", &fM3Trans);
   validation_tree->SetBranchAddress( "fAlpha", &fAlpha);
   validation_tree->SetBranchAddress( "fDist", &fDist);
   validation_tree->SetBranchAddress( "id", &id);

   /*------------------------------------------------------------------------------
   6) Fill the evaluation of the validation events in the three histograms accordingly:
      a. one to evaluate all the events of the validation set
      b. one to evaluate only the gamma events (signal)
      c. one to evaluate only the hadron events (background)
     ------------------------------------------------------------------------------*/

   for (Long64_t ievt=0; ievt<validation_tree->GetEntries();ievt++)
   {
     float probability;
     validation_tree->GetEntry(ievt);
     probability=reader->EvaluateMVA( "MLP method");

     histNn->Fill(probability);
     if(id==1)
        hist_g->Fill(probability);
     else
        hist_h->Fill(probability);
   }

   /*------------------------------------------------------------------------------
   7) Write the histograms in a file called "Application_output.root"
     ------------------------------------------------------------------------------*/

   TFile *target  = new TFile( "Application_output.root","RECREATE" );


   histNn     ->Write();
   hist_g     ->SetLineColor(2);
   hist_g     ->Write();

   hist_h     ->SetLineColor(4);
   hist_h     ->Write();

   delete reader;
}
