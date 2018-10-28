#object_files (testEffi.o)
OBJECTS := $(wildcard *.o)

#root_stuff (root libraries and needed root options)
ROOTLIBS := $(shell root-config --glibs)
ROOTFLAGS := $(shell root-config --cflags --libs) -lRooFit -lRooFitCore
ROOTCINT := $(shell which rootcint)

#exe_files
EXECUTABLE0 := testEffi
EXECUTABLE1 := testGene
EXECUTABLE2 := testGeneReFit
EXMAKEHIST  := testEffi3DB0-2016-makeHisto
CLASS1       := RooGenePdf
CLASSDICT1   := $(CLASS1)Dictionary.cxx
CLASS2       := RooBernsteinEffi
CLASSDICT2   := $(CLASS2)Dictionary.cxx

#compiling options
DEBUGFLAGS := -O3 -Wall -std=c++11
CXXFLAGS := $(DEBUGFLAGS) 

#compile class
LIBS1 := $(CLASS1).cxx  $(CLASSDICT1)
LIBS2 := $(CLASS2).cxx  $(CLASSDICT2)

	
all: $(CLASSDICT1) $(CLASSDICT2) $(EXECUTABLE0)  $(EXECUTABLE1)  $(EXECUTABLE2) $(EXMAKEHIST)

dict: $(CLASSDICT)

hist: $(EXMAKEHIST)

$(CLASSDICT1): $(CLASS1).h $(CLASS1)LinkDef.h
	@echo "Generating dictionary $@ using rootcint ..."
	$(ROOTCINT) -f $@ -c $^

$(CLASSDICT2): $(CLASS2).h $(CLASS2)LinkDef.h
	@echo "Generating dictionary $@ using rootcint ..."
	$(ROOTCINT) -f $@ -c $^

$(CLASSDICT3): $(CLASS3).h $(CLASS3)LinkDef.h
	@echo "Generating dictionary $@ using rootcint ..."
	$(ROOTCINT) -f $@ -c $^


$(EXECUTABLE0): $(EXECUTABLE0).cc 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS2) $(ROOTLIBS) $(ROOTFLAGS) -I.

$(EXECUTABLE1): $(EXECUTABLE1).cc 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS1) $(LIBS2) $(ROOTLIBS) $(ROOTFLAGS) -I.

$(EXECUTABLE2): $(EXECUTABLE2).cc 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS1) $(LIBS2) $(ROOTLIBS) $(ROOTFLAGS) -I.

$(EXMAKEHIST): $(EXMAKEHIST).cc 
	$(CXX) $(CXXFLAGS)  -o $@  $^ $(ROOTLIBS) $(ROOTFLAGS) -I.



#cleaning options
.PHONY: clean cleanall
clean:
	rm -f $(OBJECTS) && rm -f $(EXECUTABLE0) $(EXECUTABLE1)  $(EXECUTABLE2) $(EXMAKEHIST) $(CLASSDICT1) $(CLASSDICT2)
cleanhist:
	rm -f  $(EXMAKEHIST)

