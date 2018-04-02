# TMVA installation  
 TMVA Toolkit for Multivariate Data Analysis with ROOT
  
## Step 1 - Check ROOT version
Eventhough the TMVA toolkit is supported by ROOT_VERSION >= 5.34/11 , it has been under a lot of developpement and changes.
For the topical lectures we will work with ROOT_VERSION >= 6.08/07 which has the needed TMVA built-in.

1) Check your ROOT version with: `root-config --version`  
if ROOT_VERSION < 6.08/07 go to step 2.  
  
2) Check if you have the right TMVA installed:  
In your terminal type:  
```ruby
$ root -l
root [0] TMVA::DataLoader test;
```
If you get `Error: Invalid type 'DataLoader' in declaration of 'test'` go to step 2.  
Otherwise you're ready for the tutorials.

## Step 2 - Install root.
### MacOS X:
Via brew:
1. If you don’t have brew type `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"` (see : https://brew.sh for more information).  
2. If you have root but version < 6.08/07: `brew upgrade root`. 
3. Install root: `brew install root`.
  
### UNIX & MacOS X: 
#### GCC:
1. Check the version of gcc: type in terminal `gcc —v`  
2. If GCC_VERSION < 4.8.1, you need to update your gcc to at least 4.8.1  

#### ROOT:
To install root with TMVA (locally) (linux or Mac):  
1. `git clone http://root.cern.ch/git/root.git`  
2. `cd root`  
3.a. For a local installation: `./configure —prefix=path/to/installation` (follow step 3)  
3.b. For a global installation: `./configure`  
4. `make`  
5. `make install`  
  
Step 3 - Case of local installation
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
