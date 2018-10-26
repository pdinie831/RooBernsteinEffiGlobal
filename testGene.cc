//*******************************************************************************
//*                                                                             *
//*  test code to compare efficiency projection and fit parametrization         *
//*  using RooBernsteinClass.                                                   *
//*                                                                             *
//*  P.Dini fecit, Anno Domini MMXVIII                                          *
//*                                                                             *
//*******************************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include "Riostream.h"
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TH1F.h> 
#include <TH2F.h>
#include <TH3F.h>
#include <TH1D.h>
#include <TH2D.h>   
#include <TH3D.h>
#include <TF1.h>
#include <TF2.h>
#include <TF3.h>
#include <TROOT.h>
#include <TEnv.h>
#include <TSystem.h>
#include <TTree.h>
#include <TChain.h>
#include "TBranch.h"
#include <TCanvas.h>
#include "TAxis.h"
#include "RooPlot.h"
#include <TBranch.h>
#include <TApplication.h>
#include <TFile.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooHistPdf.h>
#include <RooAbsReal.h>
#include <RooRealProxy.h>
#include <RooCategoryProxy.h>
#include <RooAbsCategory.h>
#include <RooEffProd.h>
#include <RooProdPdf.h>
#include <RooGenericPdf.h>
#include "RooGenePdf.h"
#include <RooPlot.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooGenericPdf.h>
#include <RooAddPdf.h>
#include <RooProdPdf.h>
#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooAddModel.h>
#include <RooDecay.h>
#include <RooExponential.h>
#include <RooEffProd.h>
#include <RooPolynomial.h>
#include <RooExtendPdf.h>
#include <RooProduct.h>
#include <RooAddition.h>
#include <RooMinuit.h>
#include <RooHistPdf.h>
#include <RooFitResult.h>
#include <RooChebychev.h>
#include  <TStopwatch.h>
using namespace std;
void ReadDataGene(); 
TTree* makeGenTTree(RooDataSet* geneDataNew); 
std::map<std::string, std::string>  ReadNamelist(int argc, char** argv);

/////////////////////////
int NFact = 700;
int numParameters=8;
/////////////////////////

double Q2Min = 0.; 
double Q2Max = 0.; 
int    Q2Bin = -1;
double Q2Fake= -1.;
int    xCosLHBin =  0;
int    xCosKHBin =  0;
int    xPhiHBin  =  0;
double XMinCosThetaL = -1.;
double XMaxCosThetaL = 1.;
double XMinCosThetaK = -1.;
double XMaxCosThetaK = 1.;
double XMinPhi       = -TMath::Pi();
double XMaxPhi       = TMath::Pi();
double B0Mass	= 5.27962;
bool   wrongTagged = false;
char OutFileName[300] =  "";
char ListParName[300] =  "";
char eosRecoDir[100] = "/eos/cms/store/user/fiorendi/p5prime/2016/skims/";
char eosGeneDir[100] = "/eos/cms/store/user/fiorendi/p5prime/2016/skims/GEN/";
char RecoDir[100]    =  ".";
char GeneDir[100]    =  ".";
char OutputGeneB0TreeName[10]    = "ntuple";
char PDFNameGenePlotsPdf[50]      = "B0-Generated-PdfFit-2016-global.pdf";
char PNGNameGenePlotsPdf[50]      = "B0-Generated-PdfFit-2016-global.png";
char PDFNameGenePlotsNew[50]      = "B0-Generated-MiniMC-PdfFit-2016-global.pdf";
char PNGNameGenePlotsNew[50]      = "B0-Generated-MiniMC-PdfFit-2016-global.png";
//
RooRealVar x("x", "CosL",  XMinCosThetaL,XMaxCosThetaL);
RooRealVar y("y", "CosK",  XMinCosThetaK,XMaxCosThetaK);
RooRealVar z("z", "Phi" ,  XMinPhi,XMaxPhi);
RooDataSet  geneData("geneData", "geneData", RooArgSet(x,y,z));
// RooRealVar F_S("F_S","F_S",0., 0.,1.); 
// RooRealVar A_S("A_S","A_S",0., 0.,1.);
// RooRealVar A5S("A5S","A5S",0.,-1.,1.);

RooRealVar F_L("F_L","F_L", 0.6 , 0.,1.);
RooRealVar P_1("P_1","P_1",-0.2 ,-1.,1.);
RooRealVar P_2("P_2","P_2", 0.4 ,-1.,1.);
RooRealVar P_3("P_3","P_3", 0.0,-1.,1.);
RooRealVar P4p("P4p","P4p", 0.0,-1.,1.);
RooRealVar P5p("P5p","P5p", 0.0,-1.,1.);
RooRealVar P6p("P6p","P6p", 0.0,-1.,1.);
RooRealVar P8p("P8p","P8p", 0.0,-1.,1.);
char InputGeneB0TreeName[10]	= "tree";
TH3D* HxGene = 0;


int main (int argc, char** argv) {
 gROOT ->Reset();
//
 TStopwatch TimeWatch;
 TimeWatch.Start();
//  
//

if (argc<=1 ){
    cout<<"Q2Bin not set"<<endl;
    cout<<"Usage: "<<argv[0]<< " QBin2 [where QBin2=0,1,2,3,4,5,6,7,8]\n"<<endl;
    exit(1);
}   


 
switch ( *argv[1] ) {

  case '0' : 
   Q2Min = 1.; 
   Q2Max = 2.;
   Q2Fake= 1.5;
   Q2Bin = 0;
      xCosLHBin =  25;
      xCosKHBin =  25;
      xPhiHBin  =  25;
    break;
  case '1' : 
   Q2Min = 2.; 
   Q2Max = 4.3; 
   Q2Fake= 3.;
   Q2Bin = 1;
   xCosLHBin =  25;
   xCosKHBin =  25;
   xPhiHBin  =  25;
    break;
  case '2' : 
   Q2Min = 4.3; 
   Q2Max = 6.; 
   Q2Fake= 5.;
   Q2Bin = 2;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;
  case '3' : 
   Q2Min = 6.; 
   Q2Max = 8.68; 
   Q2Fake= 7.;
   Q2Bin = 3;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;
  case '4' : 
   Q2Min = 8.68; 
   Q2Max = 10.09; 
   Q2Fake= 9.;
   Q2Bin = 4;
   xCosLHBin =  25;
   xCosKHBin =  25;
   xPhiHBin  =  25;
    break;
  case '5' : 
   Q2Min = 10.09; 
   Q2Max = 12.86; 
   Q2Fake= 11.;
   Q2Bin = 5;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;
  case '6' : 
   Q2Min = 12.86; 
   Q2Max = 14.18; 
   Q2Fake= 13.;
   Q2Bin = 6;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;
  case '7' : 
   Q2Min = 14.18; 
   Q2Max = 16.; 
   Q2Fake= 15.;
   Q2Bin = 7;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;
  case '8' : 
   Q2Min = 16; 
   Q2Max = 19.; 
   Q2Fake= 17.;
   Q2Bin = 8;
   xCosLHBin = 25;
   xCosKHBin = 25;
   xPhiHBin  = 25;
    break;

  default : 
    // Process for all other cases.
    cout<<"Q2Bin not set correctly!!!"<<endl;
    cout<<"Usage: "<<argv[0]<< " QBin2 [where QBin2=0,1,2,3,4,5,6,7,8]\n"<<endl;
    exit(1);

}
   std::cout<<"--------------------------------------------\n"<<endl;
   std::cout<<" Setting selection for Q^2 bin: "<<*argv[1]<<" ==> "<<Q2Min<<"<Q^2<"<<Q2Max<<std::endl;
   std::cout<<"--------------------------------------------\n"<<endl;
   sprintf(OutFileName,"testGene-2016-Q2Bin-%d.root", Q2Bin);

   sprintf(PDFNameGenePlotsPdf,"B0-Generated-PdfFit-2016-Q2Bin-%d.pdf", Q2Bin); 
   sprintf(PNGNameGenePlotsPdf,"B0-Generated-PdfFit-2016-Q2Bin-%d.png", Q2Bin); 
 
   if (argc>2 && (strcmp(argv[2],"e") == 0) ){

     std::cout<<" Setting EOS ad directory files  \n"<<endl;
     memcpy ( GeneDir, eosGeneDir, strlen(eosGeneDir)+1 );
     memcpy ( RecoDir, eosRecoDir, strlen(eosRecoDir)+1 );

   }
    std::cout<<" Reading MC Reconstructed  files in directory: "<<RecoDir<<std::endl;
    std::cout<<" Reading MC Generated	   file: in directory: "<<GeneDir<<std::endl;
    std::cout<<"--------------------------------------------\n"<<endl;
    sprintf(ListParName,"ListGenValues-2016-Q2Bin-%d.txt", Q2Bin); 

   x.setBins(xCosLHBin);
   y.setBins(xCosKHBin);
   y.setBins(xPhiHBin);


   TCanvas* GenePlotsPdf = new TCanvas("GenePlotsPdf","Gene test Pdf plots",200,10,900,780);
   GenePlotsPdf->Divide(2,2);
   TCanvas* GenePlotsNew = new TCanvas("GenePlotsNew","Gene test MiniMC Pdf plots",200,10,900,780);
   GenePlotsNew->Divide(2,2);

   ReadDataGene();


   TFile*OutFile = TFile::Open(OutFileName,"RECREATE");
//   double xBinw = (XMaxCosThetaL-XMinCosThetaL)/xCosLHBin;
//   double yBinw = (XMaxCosThetaK-XMinCosThetaK)/xCosKHBin;
//   double zBinw = (XMaxPhi-XMinPhi)/xPhiHBin;


   RooArgList *coefList = new RooArgList();

  std::cout<<"Try to open list of initial parameters :"<< ListParName <<std::endl;
  std::fstream *parListInput = new std::fstream(ListParName,std::ifstream::in);
  if(parListInput->is_open()){
      char*argn[]={ListParName};
  
      std::map<std::string, std::string> mappa = ReadNamelist(1,argn );
      gSystem->Exec(Form("cp %s %s.tmp",ListParName,ListParName));
      F_L.setVal(atof (mappa["F_L"].c_str() ) );
      P_1.setVal(atof (mappa["P_1"].c_str() ) );
      P_2.setVal(atof (mappa["P_2"].c_str() ) );
//       P_3.setVal(atof (mappa["P_3"].c_str() ) );
//       P4p.setVal(atof (mappa["P4p"].c_str() ) );
//       P5p.setVal(atof (mappa["P5p"].c_str() ) );
//       P6p.setVal(atof (mappa["P6p"].c_str() ) );
//       P8p.setVal(atof (mappa["P8p"].c_str() ) );
   }else{
     std::cout<<"List of initial parameters "<< ListParName <<" not found, fit with "<<std::endl;
   }  

   coefList->add(F_L);
   coefList->add(P_1);
   coefList->add(P_2);
   coefList->add(P_3);
   coefList->add(P4p);
   coefList->add(P5p);
   coefList->add(P6p);
   coefList->add(P8p);
   RooGenePdf GenePdf("GenePdf","GenePdf",x,y,z,*coefList);
  
 
 
 
 
 
 
 
 
   RooAbsReal* nll = GenePdf.createNLL(geneData,RooFit::NumCPU(64)); 
//   RooAbsReal* nll = GenePdf.createNLL(geneData,RooFit::Extended(kTRUE),RooFit::NumCPU(64)); 
   RooMinuit Minuit(*nll) ;
     P_3.setConstant(kTRUE);
     P4p.setConstant(kTRUE);
     P5p.setConstant(kTRUE);
     P6p.setConstant(kTRUE);
     P8p.setConstant(kTRUE);
//    F_S.setConstant(kTRUE);
//    A_S.setConstant(kTRUE);
//    A5S.setConstant(kTRUE);
   Minuit.migrad() ;
   Minuit.hesse() ;
 
  std::fstream *parListOutput =  new std::fstream(ListParName,ios::out);
  if(parListOutput->is_open()){
    std::cout<<"Open: "<<ListParName<<std::endl ;

    TIterator* coefIter = coefList->createIterator() ;
    RooAbsArg* coef ;
     while((coef = (RooAbsArg*)coefIter->Next())) {
       if (!dynamic_cast<RooRealVar*>(coef)) {
    	 std::cout << coef->GetName() <<" is not of type RooAbsReal" << std::endl ;
    	 assert(0) ;
       }
       *parListOutput          <<coef->GetName() <<"="<<std::scientific<<std::setprecision(5)<<dynamic_cast<RooRealVar*>(coef)->getVal()  <<std::endl;
       *parListOutput <<"sigma"<<coef->GetName() <<"="<<std::scientific<<std::setprecision(5)<<dynamic_cast<RooRealVar*>(coef)->getError()<<std::endl;
      }
     parListOutput->close();
     std::cout<<"Close: "<<ListParName<<std::endl ;
    }else{
    if(!parListOutput->is_open()) std::cout<<"Error: can not open "<<ListParName<<std::endl ;
    exit(1);
   }
   std::cout<<"NFact (scale factor  new gene) = "<<NFact<<std::endl;
   std::cout<<"Number of     Generated Events = "<<geneData.sumEntries()<<std::endl;
   int NumGeneNew = geneData.sumEntries()*NFact;
   std::cout<<"Number of New Generated Events = "<<NumGeneNew<<std::endl;
   RooDataSet* geneDataNew = GenePdf.generate(RooArgSet(x,y,z),NumGeneNew) ;
   TTree*  GeneB0TreeOut = makeGenTTree(geneDataNew);
   
    
//    HxGene = new   TH3D( "HxGene"    , "B^{0} Gene",  xCosLHBin, XMinCosThetaL, XMaxCosThetaL,
//  						    xCosKHBin, XMinCosThetaK, XMaxCosThetaK,
// 						    xPhiHBin , XMinPhi, XMaxPhi );
    
   TH1D* HxGeneX    = (TH1D*) HxGene->ProjectionX("HxGeneX",1,HxGene->GetNbinsY(),1,HxGene->GetNbinsZ());HxGeneX->SetTitle("Gene Cos#theta_{L}");
   TH1D* HxGeneY    = (TH1D*) HxGene->ProjectionY("HxGeneY",1,HxGene->GetNbinsX(),1,HxGene->GetNbinsZ());HxGeneY->SetTitle("Gene Cos#theta_{K}");
   TH1D* HxGeneZ    = (TH1D*) HxGene->ProjectionZ("HxGeneZ",1,HxGene->GetNbinsX(),1,HxGene->GetNbinsY());HxGeneZ->SetTitle("Gene #phi");
   
   RooPlot* gxframe=x.frame(RooFit::Bins(25));
   geneData.plotOn( gxframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(   gxframe, RooFit::LineColor(kRed),RooFit::ProjWData(x,geneData));
   GenePlotsPdf->cd(1);
   gxframe->SetTitle("Generated events - Cos#theta_{L} Projection");
   gxframe->Draw();
   RooPlot* gyframe=y.frame(RooFit::Bins(25));
   geneData.plotOn( gyframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(  gyframe, RooFit::LineColor(kRed),RooFit::ProjWData(y,geneData));
   GenePlotsPdf->cd(2);
   gyframe->SetTitle("Generated events - Cos#theta_{K} Projection");
   gyframe->Draw();
   RooPlot* gzframe=z.frame(RooFit::Bins(25));
   geneData.plotOn( gzframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(  gzframe, RooFit::LineColor(kRed),RooFit::ProjWData(z,geneData));
   GenePlotsPdf->cd(3);
   gzframe->SetTitle("Generated events - #phi Projection");
   gzframe->Draw();
   gSystem->Exec(Form("mv %s %s.tmp",PDFNameGenePlotsPdf,PDFNameGenePlotsPdf));
   GenePlotsPdf->Print(PDFNameGenePlotsPdf);
   gSystem->Exec(Form("mv %s %s.tmp",PNGNameGenePlotsPdf,PNGNameGenePlotsPdf));
   GenePlotsPdf->Print(PNGNameGenePlotsPdf);

   std::cout<<"Refit MiniMC Generated Events "<<std::endl ;
   RooAbsReal* nllNew = GenePdf.createNLL(*geneDataNew,RooFit::NumCPU(64)); 
   RooMinuit MinuitNew(*nllNew) ;
     P_3.setConstant(kTRUE);
     P4p.setConstant(kTRUE);
     P5p.setConstant(kTRUE);
     P6p.setConstant(kTRUE);
     P8p.setConstant(kTRUE);
//    F_S.setConstant(kTRUE);
//    A_S.setConstant(kTRUE);
//    A5S.setConstant(kTRUE);
   MinuitNew.migrad() ;
   MinuitNew.hesse() ;
   
   RooPlot* new_gxframe=x.frame(RooFit::Bins(25));
   geneDataNew->plotOn( new_gxframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(   new_gxframe, RooFit::LineColor(kRed),RooFit::ProjWData(x,*geneDataNew));
   GenePlotsNew->cd(1);
   new_gxframe->SetTitle("MiniMC Generated events - Cos#theta_{L} Projection");
   new_gxframe->Draw();
   RooPlot* new_gyframe=y.frame(RooFit::Bins(25));
   geneDataNew->plotOn( new_gyframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(  new_gyframe, RooFit::LineColor(kRed),RooFit::ProjWData(y,*geneDataNew));
   GenePlotsNew->cd(2);
   new_gyframe->SetTitle("MiniMC Generated events - Cos#theta_{K} Projection");
   new_gyframe->Draw();
   RooPlot* new_gzframe=z.frame(RooFit::Bins(25));
   geneDataNew->plotOn( new_gzframe, RooFit::MarkerStyle(kStar));
   GenePdf.plotOn(  new_gzframe, RooFit::LineColor(kRed),RooFit::ProjWData(z,*geneDataNew));
   GenePlotsNew->cd(3);
   new_gzframe->SetTitle("MiniMC Generated events - #phi Projection");
   new_gzframe->Draw();
   gSystem->Exec(Form("mv %s %s.tmp",PDFNameGenePlotsNew,PDFNameGenePlotsNew));
   GenePlotsNew->Print(PDFNameGenePlotsNew);
   gSystem->Exec(Form("mv %s %s.tmp",PNGNameGenePlotsNew,PNGNameGenePlotsNew));
   GenePlotsNew->Print(PNGNameGenePlotsNew);
   
   HxGene->Write();
   HxGeneX->Write();
   HxGeneY->Write();
   HxGeneZ->Write();
   GenePlotsPdf->Write();
   GenePlotsNew->Write();
   gxframe->Delete();
   gyframe->Delete();
   gzframe->Delete();
   new_gxframe->Delete();
   new_gyframe->Delete();
   new_gzframe->Delete();
   GeneB0TreeOut->Write();
   OutFile->Close();

   TimeWatch.Stop();
   TimeWatch.Print();
   
   std::cout<<"======= END OF TEST ======="<<std::endl;
   return 0;
}
//========================================================================================================================================
//                 END OF TEST
//========================================================================================================================================

void ReadDataGene(){   
//======================================================================
//======================================================================
//======================================================================
//
//			      GENERATED EVENTS
//
//======================================================================
//======================================================================
//======================================================================
  HxGene = new   TH3D( "HxGene"    , "B^{0} Gene",  xCosLHBin, XMinCosThetaL, XMaxCosThetaL,
 						    xCosKHBin, XMinCosThetaK, XMaxCosThetaK,
						    xPhiHBin , XMinPhi, XMaxPhi );
  int nfile = 0;
  TChain* GeneB0Tree = new TChain();  
  nfile = GeneB0Tree->Add(Form("%s/gen_B0_miniaodWithoutGenCuts.root/%s",GeneDir,InputGeneB0TreeName));
  if( nfile==0 ||  !GeneB0Tree->GetFile() ){
    cout<<"Error:  no Gene files found!!!\n"<<endl;
    exit(1);
  }else{
    printf("Try to open %s/2016MC_GEN_LMNR_double_sub*_p*.root/%s \n",GeneDir,InputGeneB0TreeName);
    cout<<"Opening "<<nfile <<" Gene files found!!!\n"<<endl;
  }  
  if(!GeneB0Tree ){
    cout<<"TTree Gene Data: "<< InputGeneB0TreeName <<" not found!!!\n"<<endl;
    exit(1);
  }else{
    cout<<"TTree Gene Data: "<< InputGeneB0TreeName <<" OK FOUND!!!\n"<<endl;
  }  

//  double  genB0Mass	   ;
  float   gen_cos_theta_l   ;
  float   gen_cos_theta_k   ;
  float   gen_phi           ;
  float   mumu_mass         ;
  double  genQ2	            ;


//  GeneB0Tree->SetBranchAddress("genB0Mass"	   ,&genB0Mass);
  GeneB0Tree->SetBranchAddress("gen_cos_theta_l"   ,&gen_cos_theta_l);
  GeneB0Tree->SetBranchAddress("gen_cos_theta_k"   ,&gen_cos_theta_k);
  GeneB0Tree->SetBranchAddress("gen_phi"           ,&gen_phi);
  GeneB0Tree->SetBranchAddress("mumu_mass"  	   ,&mumu_mass);

  int ngentries = (int)GeneB0Tree->GetEntries();
  for (Int_t i=0;i<ngentries;i++) { 
     
     GeneB0Tree->GetEntry(i);
     genQ2= mumu_mass*mumu_mass;
// folding theta_l e phi     
//       gen_cos_theta_l = fabs(gen_cos_theta_l);
//       gen_cos_theta_k = fabs(gen_cos_theta_k);
//       gen_phi         = fabs(gen_phi);
//
//  Q^2 Bin
     if(genQ2>Q2Min&&genQ2<Q2Max){
      if(gen_cos_theta_l>=XMinCosThetaL&&gen_cos_theta_l<=XMaxCosThetaL&&
         gen_cos_theta_k>=XMinCosThetaK&&gen_cos_theta_k<=XMaxCosThetaK&&
	 gen_phi>=XMinPhi&&gen_phi<=XMaxPhi){
 	 x.setVal(double(gen_cos_theta_l));
 	 y.setVal(double(gen_cos_theta_k));
 	 z.setVal(double(gen_phi));
	 geneData.add(RooArgSet(x,y,z));
         
 	 HxGene->Fill(gen_cos_theta_l,gen_cos_theta_k,gen_phi);
      } 
     } 
  }

  char TXT[200];
  sprintf(TXT,"Mass Gen   Entries = %7f",HxGene->GetEntries());
  cout<<"***********************************\n"<<endl;
  cout<<"***** GENERATED EVENTS   **********\n"<<endl;
  cout<<"***********************************\n"<<endl;
  cout<<"GenB0Tree   Entries       = "<<ngentries<<endl;
  cout<<"RecoB0Tree  Gene Selected = "<<HxGene->GetEntries()<<endl;
  cout<<TXT<<endl;
  cout<<"\n***********************************"<<endl;
  cout<<"***********************************"<<endl;
}

TTree* makeGenTTree(RooDataSet* geneDataNew) 
{
  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y

  TTree* GeneB0TreeOut = new TTree(OutputGeneB0TreeName,OutputGeneB0TreeName) ;
  GeneB0TreeOut -> SetAutoSave(500000000);
  double  genB0Mass	    ;
  double  gen_cos_theta_l   ;
  double  gen_cos_theta_k   ;
  double  gen_phi_kst_mumu  ;
  double  genq2	    ;
  GeneB0TreeOut->Branch("genB0Mass"	    ,&genB0Mass 	,"genB0Mass/D"	       );
  GeneB0TreeOut->Branch("gen_cos_theta_l"   ,&gen_cos_theta_l   ,"gen_cos_theta_l/D"   );
  GeneB0TreeOut->Branch("gen_cos_theta_k"   ,&gen_cos_theta_k   ,"gen_cos_theta_k/D"   );
  GeneB0TreeOut->Branch("gen_phi_kst_mumu"  ,&gen_phi_kst_mumu  ,"gen_phi_kst_mumu/D"  );
  GeneB0TreeOut->Branch("genq2"	            ,&genq2             ,"genq2/D"             );
  for (int i=0 ; i<geneDataNew->sumEntries() ; i++) {
   const RooArgSet* row =  new  RooArgSet(x,y,z);       
  
   row = geneDataNew->get(i);
   genB0Mass=B0Mass;
   gen_cos_theta_l =row->getRealValue("x");
   gen_cos_theta_k =row->getRealValue("y");
   gen_phi_kst_mumu=row->getRealValue("z");
   genq2=sqrt(Q2Fake);
   GeneB0TreeOut->Fill() ;
  
  }
  return GeneB0TreeOut ;
}
//=========================================================================================
//
// Namelist Routine
//
std::map<std::string, std::string> ReadNamelist(int argc, char** argv){
//    if ( argc>=1 && (strcmp(argv[0],"ListGenValues-2016-Q2Bin-")>=0) ){
//      std::cout<<"Defined namelist: "<<argv[0]<<std::endl;
//    }else{
//      std::cout<<"Namelist:"<<argv[0]<<"  should be named/renamed ListGenValues-2016-Q2Bin-*.txt "<<argc<<std::endl;
//      exit(1);
//    }
   vector<string> split( char *str, char c = ' ');
   ifstream indata;
   std::map<std::string, std::string> mappa;
   std::string line;
   vector<string>vstring ;
//
    indata.open(argv[0]);
   if(!indata) { // file couldn't be opened
   	std::cout <<__LINE__ <<argv[0]<< " Error: fileList can not be opened" << std::endl;
   	exit(1);
   }
   while(std::getline(indata, line)) {
	 line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
	 line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
	 line.erase(std::remove(line.begin(), line.end(), ' ' ), line.end());

 	 char *cstr = new char [line.size()+1];


 	 strcpy (cstr, line.c_str());
//	 cout <<"stringa->"<< cstr << endl;
	 vstring = split(cstr,'=');
	 mappa.insert( std::pair<string,string>(vstring[0],vstring[1]) );
    }
    std::cout<<"#########################################################################################################"<<std::endl;
    for (map<string,string>::iterator imap = mappa.begin();
    			       imap != mappa.end();
    			       ++imap)
    {
   	std::cout <<"mappa->"<< (*imap).first<<" = "<<(*imap).second << std::endl;
    }
    std::cout<<"#########################################################################################################"<<std::endl;
    indata.close();	
  return mappa ;
}
vector<string> split( char *str, char c = ' ')
{
    vector<string> result;

    while(1)
    {
         char *begin = str;

        while(*str != c && *str)
                str++;

        result.push_back(string(begin, str));

        if(0 == *str++)
                break;
    }

    return result;
}
