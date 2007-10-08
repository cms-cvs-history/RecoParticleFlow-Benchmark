#include <iostream>
#include <TH1.h>
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetfwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetfwd.h"

#include "RecoParticleFlow/Benchmark/interface/PFBenchmarkAlgo.h"
#include <vector>


using namespace std;


PFBenchmarkAlgo::PFBenchmarkAlgo()
{
 
}

PFBenchmarkAlgo::~PFBenchmarkAlgo()
{

}

void PFBenchmarkAlgo::doBenchmark()
{
  cout<<"TauBenchmarkAnalyzer"
    <<"opening output root file "<<outputRootFileName_<<endl;
  
  /* file_ = TFile::Open(outputRootFileName_.c_str(), "RECREATE");
  
  if(file_->IsZombie() ) {
    string err = "output file ";
    err += outputRootFileName_;
    err += " can't be opened";
    throw cms::Exception("OutputFileOpen",err);
  }
  */
  h_deltaETvisible_EHT_GEN_
    = new TH1F("h_deltaETvisible_EHT_GEN_","Jet Et difference CaloTowers-MC"
	       ,500,-50,50);
  
  h_deltaETvisible_PF_GEN_
    = new TH1F("h_deltaETvisible_PF_GEN_" ,
	       "Jet Et difference ParticleFlow-MC"
	       ,500,-50,50);

  // ==================================================================
  // GEN JETS ==========================================================
  // ==================================================================
 
  double JetGEN_ETmax=0.0;
  double jetGEN_et=0.0;
  for ( unsigned int i = 0; i < genJets_->size(); i++)
    {
      //Taking the most energetic jet
      jetGEN_et=(*genJets_)[i].et();
      if(JetGEN_ETmax<jetgen_et)
	JetGEN_ETmax = jetgen_et;
    }
   cout<<"biggest et of gen jets: "<<JetGEN_ETmax<<endl;
  
  // ==================================================================
  // CALO TOWER JETS (ECAL+HCAL Towers)=================================
  // ==================================================================
  
  double JetEHTETmax=0.0;
  double jetcalo_et=0.0;
  for ( unsigned int i = 0; i < recoCaloJets_->size(); ++i)
    {
      jetcalo_et=(*recoCaloJets_)[i].et();
      if (jetcalo_et >= JetEHTETmax) 
	JetEHTETmax = jetcalo_et;
    }//loop calo towers
  cout<<"biggest et of calo jets: "<<JetEHTETmax<<endl;
  
  
  // ==================================================================
  // PF Jets ===========================================================
  // ==================================================================
  
  double pfjet_et=0.0;
  double JetPFETmax=0.0;/*
  for ( unsigned int i = 0; i < (*pfJets_).size(); ++i)
    {
      pfjet_et=(*pfJets_)[i].et();
      if (pfjet_et >= JetPFETmax) 
	JetPFETmax = pfjet_et;
    }//loop pfjets*/
  cout<<"biggest et of pf jets: "<<JetPFETmax<<endl;
  // ==================================================================
  // Status output ====================================================
  // ==================================================================
  
  
  cout<<"delta et calo-gen: "<<JetEHTETmax-JetGEN_ETmax<<endl;
  cout<<"delta et pflow-gen : "<<JetPFETmax-JetGEN_ETmax<<endl; 
  cout<<endl<<endl<<endl;
  // ==================================================================
  // Filling Histogramms ===============================================
  // ==================================================================
  
  h_deltaETvisible_PF_GEN_->Fill(JetPFETmax-JetGEN_ETmax);
  h_deltaETvisible_EHT_GEN_->Fill(JetEHTETmax-JetGEN_ETmax); 
}


void PFBenchmarkAlgo::createPlots()
{
  h_deltaETvisible_PF_GEN_->Print("pf_gen.jpg");
  h_deltaETvisible_EHT_GEN_->Print("eht_gen.jpg");

}
