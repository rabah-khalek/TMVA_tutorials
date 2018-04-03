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
#### GCC:
- Check the version of gcc, type in terminal `gcc —v`  
- If GCC_VERSION < 4.8.1, you need to update your gcc to at least 4.8.1  
- Check http://luiarthur.github.io/gccinstall to install gcc locally.  

#### ROOT:
To install root with TMVA (locally) (linux or Mac):  
- `git clone http://root.cern.ch/git/root.git`  
- `cd root`  
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
