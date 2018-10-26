=================================================================

The test code for the Class RooBernsteinEffi is C11 compliant. 
[i.e. to compile on fly in lxplus you can set:  
scl enable devtoolset-7 tcsh]

to compile all the executables (testEffi and testEffi3DB0-2016-makeHisto) && make dictionary for the RooBernsteinEffi class :
```
make all
```

to clean the directory, removing all the compiled objects :

```
make clean
```

to make just the dictionary for the class RooBernsteinEffi :
```

make dict
```

to make just the program to reproduce the histogram files [testEffi3DB0-2016-makeHisto] :
```

make hist
```

to execute the test program 'testEffi' to compare data and efficiency parametrization for a Q^2 bin:
``` 

./testEffi QBin2 [where QBin2=0,1,2,3,4,5,6,7,8]
```

i.e. the output of the command :
```

./testEffi 3 

is the test file for the Q^2 bin 3 projections:

testEffiRooFit-2016-Q2Bin-3-Bins-25-25-25-BernDeg-5-5-4.root
```

opening this file, in TCanvas "ProjEffiPlots" you can find the projections of  the efficiency in Cos(l), Cos(K) and Phi for the binning 25x25x25 and, 
superimposed, the projections of the fit with multivariate Bernstein polynomial of degree 5x5x4. 
In TCanvas "ClosurePlots" are shown the projections of the reconstructed events and, superimpose, the (generated events) x (efficiency function). 

The coefficients (180) of the  fits are stored in ASCII file: 

ListParValues-2016-Q2Bin-*-Bins-25-25-25-BernDeg-5-5-4-integraBin.plo,
where *=0,1,2,3,4,5,6,7,8.

to make the comparison with data histograms, the program testEffi read the files : 

testGoofitEffi3DB0-2016-InputHisto-Q2Bin-*-Bins-25-25-25.root 
where *=0,1,2,3,4,5,6,7,8. 



These root files are stored in /afs/cern.ch/user/d/dini/public/AngularEffi1, and can be reproduced by executing the program
testEffi3DB0-2016-makeHisto:

```

./testEffi3DB0-2016-makeHisto QBin2 [where QBin2=0,1,2,3,4,5,6,7,8] e


```

i.e. the output of the command :
```

./testEffi3DB0-2016-makeHisto 3 e

is the file  testGoofitEffi3DB0-2016-InputHisto-Q2Bin-3-Bins-25-25-25.root

N.B. the option "e" means that the ntuples input files are searched in the original directories on EOS, otherwise, 
if you have the files in your directory, simple type :

./testEffi3DB0-2016-makeHisto 3 


```


=================================================================






