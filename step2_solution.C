#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

void step2_solution()
{

   // This loads the library
   TMVA::Tools::Instance();

//===================================TODO=======================================
//==============================================================================
/*------------------------------------------------------------------------------
  1) Open signal.root and background.root and load them into two
     different TTrees: signalTree and BackgroundTree
     | example |
     |> TFile * file;
     |> file = TFile::Open("data/signal.root" );
     |> TTree * signalTree = (TTree*)signal_file->Get("tree");
     ------------------------------------------------------------------------------*/
      TFile * signal_file;
      signal_file = TFile::Open("data/signal.root" );

      TFile * bkg_file;
      bkg_file = TFile::Open("data/background.root" );


      // Register the training and test trees
      TTree *signalTree     = (TTree*)signal_file->Get("tree");
      TTree *backgroundTree    = (TTree*)bkg_file->Get("tree");

/*------------------------------------------------------------------------------
  2) Create and open an output file : Classification_output.root
     where TMVA will store ntuples, histograms, etc.
     | example |
     |> TFile * file = 0;
     |> file = TFile::Open("signal.root","RECREATE");
     ------------------------------------------------------------------------------*/

     TString outfileName = "Classification_output.root";
     TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

/*------------------------------------------------------------------------------
   3) Create the factory object. Later you can choose the methods
      whose performance you'd like to investigate. The factory is
      the only TMVA object you have to interact with

      The first argument is the base of the name of all the
      weightfiles in the directory weight/: "TMVAClassification"

      The second argument is the output file for the training results
      All TMVA output can be suppressed by removing the "!" (not) in
      front of the "Silent" argument in the option string

      See reference: https://root.cern.ch/doc/v608/classTMVA_1_1Factory.html
     ------------------------------------------------------------------------------*/

     TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                                 "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

/*------------------------------------------------------------------------------
   4) Create the DataLoader object. Dataloader is the tool used to deal
      with data.
     ------------------------------------------------------------------------------*/

     TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

/*------------------------------------------------------------------------------
   5) Define the input variables that shall be used for the MVA training
      note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
      [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

      our variables list : fLength,fWidth,fSize,fConc,fConc1,fAsym,fM3Long,fM3Trans,fAlpha,fDist;
      | example |
      |> dataloader->AddVariable( "x", 'F');
     ------------------------------------------------------------------------------*/

     dataloader->AddVariable( "fLength", 'F');
     dataloader->AddVariable( "fWidth", 'F');
     dataloader->AddVariable( "fSize", 'F');
     dataloader->AddVariable( "fConc", 'F');
     dataloader->AddVariable( "fConc1", 'F');
     dataloader->AddVariable( "fAsym", 'F');
     dataloader->AddVariable( "fM3Long", 'F');
     dataloader->AddVariable( "fM3Trans", 'F');
     dataloader->AddVariable( "fAlpha", 'F');
     dataloader->AddVariable( "fDist", 'F');

/*------------------------------------------------------------------------------
   6) Add the signal and background TTree to the dataloader.
   | example |
   |> dataloader->AddSignalTree( signalTree );
  ------------------------------------------------------------------------------*/

   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   dataloader->AddSignalTree    ( signalTree,     signalWeight );
   dataloader->AddBackgroundTree( backgroundTree, backgroundWeight );

/*------------------------------------------------------------------------------
   7) Tell the dataloader how to use the training and testing events

      If no numbers of events are given, half of the events in the tree are used
      for training, and the other half for testing:

         dataloader->PrepareTrainingAndTestTree( "", "SplitMode=random:!V" );

      To specify the number of testing events, use something like:

         dataloader->PrepareTrainingAndTestTree( mycut,
              "nTrain_Signal=NeventsToTrain:nTrain_Background=NeventsToTrain:SplitMode=Random:NormMode=NumEvents:!V" );

      MAGIC Data Set :
      g = gamma (signal): 12332 --> 50% = 6166, 70% = 8632 for training
      h = hadron (background): 6688 --> 50% = 3344, 70% = 4681 for training
      no need to specify the number of events to test, dataloader will do it for you once you specify the amount of training events

      | example |
      |> dataloader->PrepareTrainingAndTestTree( "", "",
      |> "nTrain_Signal=NeventsToTrain:nTrain_Background=NeventsToTrain:SplitMode=Random:NormMode=NumEvents:!V" );
      | where NeventsToTrain is a number you specify
      | where SplitMode=Random means that these events are taken randomly from the corresponding TTree
     ------------------------------------------------------------------------------*/

     dataloader->PrepareTrainingAndTestTree( "", "",
                                          "nTrain_Signal=8632:nTrain_Background=4681:SplitMode=Random:NormMode=NumEvents:!V" );

/*------------------------------------------------------------------------------
   8) Book the MVA method you want (start with MLP: Multilayer Perceptron)
      | example |
      |> factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "option")
      |where option defines the structure of your Neural Network
      |See: http://tmva.sourceforge.net/optionRef.html#MVA::MLP
      |for example "option"="NeuronType=tanh:HiddenLayers=N+5: etc..."
     ------------------------------------------------------------------------------*/

     factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

/*------------------------------------------------------------------------------
   9) Tell the factory to train, test, and evaluate the MVAs
      see https://root.cern.ch/doc/v606/classTMVA_1_1Factory.html
     ------------------------------------------------------------------------------*/

     factory->TrainAllMethods();
     factory->TestAllMethods();
     factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

}
