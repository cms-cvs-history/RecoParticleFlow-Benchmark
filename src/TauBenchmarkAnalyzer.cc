// system include files
#include <memory>

// user include files

#include "RecoParticleFlow/Benchmark/interface/TauBenchmarkAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"


#include "RecoParticleFlow/Benchmark/interface/PFBenchmarkAlgo.h"

using namespace std;

//define this as a plug-in
DEFINE_FWK_MODULE(TauBenchmarkAnalyzer);

TauBenchmarkAnalyzer::TauBenchmarkAnalyzer(const edm::ParameterSet& iConfig)
{
  outputRootFileName_ = iConfig.getUntrackedParameter< string >("outputRootFileName","tauBenchmark.root");
  recoCaloJetsLabel_= iConfig.getUntrackedParameter< string >("recoCaloJetsLabel","iterativeCone5CaloJets");
  pfJetsLabel_= iConfig.getUntrackedParameter< string >("pfJetsLabel","iterativeCone5PFJets");
  genCaloJetsLabel_= iConfig.getUntrackedParameter< string >("genCaloJetsLabel","iterativeCone5GenJets");
}

TauBenchmarkAnalyzer::~TauBenchmarkAnalyzer()
{

}


void TauBenchmarkAnalyzer::beginJob(const edm::EventSetup&)
{

}


void TauBenchmarkAnalyzer::endJob()
{

}

void TauBenchmarkAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  genCaloJets_.clear();
  recoCaloJets_.clear();
  pfJets_.clear();
 
  iEvent.getByLabel(recoCaloJetsLabel_, recoCaloJets_);
  iEvent.getByLabel(pfJetsLabel_, pfJets_);
  iEvent.getByLabel(genCaloJetsLabel_, genCaloJets_);

  cout<<recoCaloJets_->size()<<endl;
  cout<<pfJets_->size()<<endl;
  cout<<genCaloJets_->size()<<endl;
  
  PFBenchmarkAlgo *benchmark=new PFBenchmarkAlgo();
  benchmark->outputRootFileName_=&outputRootFileName_;
  benchmark->recoCaloJets_=recoCaloJets_;
  benchmark->pfJets_=pfJets_;
  benchmark->genJets_=genCaloJets_;
  benchmark->doBenchmark();
  
}











