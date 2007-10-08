// system include files
#include <memory>

// user include files

#include "RecoParticleFlow/Benchmark/interface/TauBenchmarkAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include "TH1.h"
#include "TFile.h"


#include "RecoParticleFlow/Benchmark/interface/PFBenchmarkAlgo.h"

using namespace std;

//define this as a plug-in
DEFINE_FWK_MODULE(TauBenchmarkAnalyzer);

TauBenchmarkAnalyzer::TauBenchmarkAnalyzer(const edm::ParameterSet& iConfig)
{

  benchmark=new PFBenchmarkAlgo();
  outputRootFileName_ = iConfig.getUntrackedParameter< string >("outputRootFileName","tauBenchmark.root");
  recoCaloJetsLabel_= iConfig.getUntrackedParameter< string >("recoCaloJetsLabel","iterativeCone5CaloJets");
  pfJetsLabel_= iConfig.getUntrackedParameter< string >("pfJetsLabel","iterativeCone5PFJets");
  genCaloJetsLabel_= iConfig.getUntrackedParameter< string >("genCaloJetsLabel","iterativeCone5GenJets");

   file_ = TFile::Open(outputRootFileName_.c_str(), "RECREATE");
  
  if(file_->IsZombie() ) {
    string err = "output file ";
    err += outputRootFileName_;
    err += " can't be opened";
    throw cms::Exception("OutputFileOpen",err);
  }
  
  h_deltaETvisible_EHT_GEN_
    = new TH1F("h_deltaETvisible_EHT_GEN_","Jet Et difference CaloTowers-MC"
	       ,500,-50,50);
  
  h_deltaETvisible_PF_GEN_
    = new TH1F("h_deltaETvisible_PF_GEN_" ,
	       "Jet Et difference ParticleFlow-MC"
	       ,500,-50,50);

}

TauBenchmarkAnalyzer::~TauBenchmarkAnalyzer()
{
  
}


void TauBenchmarkAnalyzer::beginJob(const edm::EventSetup&)
{
  benchmark->h_deltaETvisible_EHT_GEN_=h_deltaETvisible_EHT_GEN_;
  benchmark->h_deltaETvisible_PF_GEN_=h_deltaETvisible_PF_GEN_;
  benchmark->file_=file_;
}


void TauBenchmarkAnalyzer::endJob()
{
  benchmark->createPlots();
  file_->Write();
}

void TauBenchmarkAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  genCaloJets_.clear();
  recoCaloJets_.clear();
  pfJets_.clear();
 
  iEvent.getByLabel(recoCaloJetsLabel_, recoCaloJets_);
  iEvent.getByLabel(pfJetsLabel_, pfJets_);
  iEvent.getByLabel(genCaloJetsLabel_, genCaloJets_);

  cout<<"Size of CaloJets: "<<recoCaloJets_->size()<<endl;
  cout<<"Size of PFJets: "<<pfJets_->size()<<endl;
  cout<<"Size of genJets: "<<genCaloJets_->size()<<endl;
  
  
  
  benchmark->outputRootFileName_=outputRootFileName_;
  benchmark->recoCaloJets_=recoCaloJets_;
  benchmark->pfJets_=pfJets_;
  benchmark->genJets_=genCaloJets_;
  benchmark->doBenchmark();

  
}











