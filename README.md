# Tutorial

## Data
The data to be **classified** in this tutorial is the _MAGIC Gamma Telescope Data Set_ provided by https://archive.ics.uci.edu/ml/datasets/magic+gamma+telescope consisting of 19020 events in total.  
The data are MC generated to simulate registration of high energy gamma particles in a ground-based atmospheric Cherenkov gamma telescope using the imaging technique.  
  
The available information consists of pulses left by the incoming Cherenkov photons on the photomultiplier tubes, arranged in a plane, the camera. Depending on the energy of the primary gamma, a total of few hundreds to some 10000 Cherenkov photons get collected, in patterns (called the shower image), allowing to discriminate statistically those caused by **primary gammas (signal)** from the images of **hadronic showers** initiated by cosmic rays in the upper atmosphere **(background)**.  
  
The simple classification accuracy is **not** meaningful for this data, since classifying a background event as signal is worse than classifying a signal event as background. For comparison of different classifiers an ROC curve has to be used. The relevant points on this curve are those, where the probability of accepting a background event as signal is below one of the following thresholds: 0.01, 0.02, 0.05, 0.1, 0.2 depending on the required quality of the sample of the accepted events for different experiments.  
Please read https://archive.ics.uci.edu/ml/datasets/magic+gamma+telescope for more information and references.  

## Features:
1. fLength: (continuous) major axis of ellipse [mm] 
2. fWidth: (continuous) minor axis of ellipse [mm] 
3. fSize: (continuous) 10-log of sum of content of all pixels [in #phot] 
4. fConc: (continuous) ratio of sum of two highest pixels over fSize [ratio] 
5. fConc1: (continuous) ratio of highest pixel over fSize [ratio] 
6. fAsym: (continuous) distance from highest pixel to center, projected onto major axis [mm] 
7. fM3Long: (continuous) 3rd root of third moment along major axis [mm] 
8. fM3Trans: (continuous) 3rd root of third moment along minor axis [mm] 
9. fAlpha: (continuous) angle of major axis with vector to origin [deg] 
10. fDist: (continuous) distance from origin to center of ellipse [mm] 
11. class: 1 for gamma (signal), 0 for hadron (background) 
  
12332 gamma (signal) events. 
6688 hadron (background) events.

## Exercices
1. Start by cloning this repo: `git clone https://github.com/rabah-khalek/TMVA_tutorials`.  
2. 1. Step1: `git checkout step1` and try to complete `step1_GenerateTTrees.C`.  
In this step you will learn how to load a txt file into a TTree object.
   2. Check the solution with: `git checkout step1_solution`.  
Compile solution via `root -l step1_solution.C`.  
3. 1. Step2: `git checkout step2` and try to complete `step2_Classification.C`.
In this step you will learn how to build your own classifier (Neural Network) as a start, train it and test it.
   2. Check the solution with: `git checkout step2_solution`.  
Compile solution via `root -l step2_solution.C`.  
4. 1. Step3: `git checkout step3` and try to complete `step3_Application.C`.
In this final step you will learn how to apply your classifier on a validation set and check its performance.
   2. Check the solution with: `git checkout step3_solution`.  
   Compile solution via `root -l step3_solution.C`.  
5. To compare between different methods (BDT, DNN, SVM, etc.) provided by TMVA: `git checkout full_version`.  
Tune `MAGIC_Classification.C` and `MAGIC_Application.C` to choose as many methods to compare.


# TMVA installation  
 TMVA Toolkit for Multivariate Data Analysis with ROOT
  
## Step 1 - Check ROOT version
Eventhough the TMVA toolkit is supported by ROOT_VERSION >= 5.34/11 , it has been under a lot of developpement and changes.
For the topical lectures we will work with **ROOT_VERSION >= 6.08/07** which has the needed TMVA built-in.

- Check your ROOT version with: `root-config --version`  
if ROOT_VERSION < 6.08/07 go to step 2.  
  
- Check if you have the right TMVA installed:
In your terminal type:  
```ruby
$ root -l
root [0] TMVA::DataLoader test;
```
If you get `Error: Invalid type 'DataLoader' in declaration of 'test'` go to step 2.  
Otherwise you're **ready for the tutorials**.

## Step 2 - Install root

### MacOS X:
Via brew:
- Install root: `brew install root`.  
- If you don’t have brew type:  
`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"` 
(see : https://brew.sh for more information).  
- If you have root but version < 6.08/07: `brew upgrade root`. 

### UNIX & MacOS X:
see instruction on: http://root.cern.ch/git/root.git

## Step 2' - Install root (old way)
  
### UNIX & MacOS X: 
#### GCC:
- Check the version of gcc, type in terminal `gcc —v`  
- If GCC_VERSION < 4.8.1, you need to update your gcc to at least 4.8.1  
- Check http://luiarthur.github.io/gccinstall to install gcc locally.  

#### ROOT:
To install root with TMVA (locally) (linux or Mac):  
- `git clone http://root.cern.ch/git/root.git`  
- `cd root` 
- `git checkout origin/v6-12-00-patches`
- 1. For a local installation: `./configure -—prefix=path/to/installation` (follow step 3)  
- 2. For a global installation: `./configure`  
- `make`  
- `make install`  
  
## Step 3 - Case of local installation
Add to your ~/.bashrc:
```ruby
INSTALL_DIR=path/to/installation
export ROOTPATH=$INSTALL_DIR/lib/root/:$INSTALL_DIR:$ROOTPATH
export PATH=$INSTALL_DIR/bin:$INSTALL_DIR:$PATH
export LD_LIBRARY_PATH=$INSTALL_DIR/lib/root/:$INSTALL_DIR/lib:$LD_LIBRARY_PATH
```
Close and open your terminal, or type bash or source ~/.bashrc  
Than `which root` should give you: path/to/installation.  
Verify with step1.
