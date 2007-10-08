#ifndef RecoParticleFlow_Benchmark_PFBenchmarkAlgo
#define RecoParticleFlow_Benchmark_PFBenchmarkAlgo


#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetfwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetfwd.h"

#include <string>

class TH1F;

class PFBenchmarkAlgo
{
 public:
  PFBenchmarkAlgo();
  ~PFBenchmarkAlgo();
  void doBenchmark();
  void createPlots();
  
  std::string* outputRootFileName_;
  edm::Handle<reco::GenJetCollection> genJets_;
  edm::Handle<reco::CaloJetCollection> recoCaloJets_;
  edm::Handle<reco::PFJetCollection> pfJets_;
  
  TH1F *h_deltaETvisible_EHT_GEN_;
  TH1F *h_deltaETvisible_PF_GEN_;
};

#endif
