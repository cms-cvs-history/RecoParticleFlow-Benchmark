#ifndef RecoParticleFlow_PFProducer_TauBenchmarkAnalyzer
#define RecoParticleFlow_PFProducer_TauBenchmarkAnalyzer


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetfwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetfwd.h"

#include <string>

class TauBenchmarkAnalyzer : public edm::EDAnalyzer {
 public:
  explicit TauBenchmarkAnalyzer(const edm::ParameterSet&);
  ~TauBenchmarkAnalyzer();


 private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  
  edm::Handle<reco::GenJetCollection> genCaloJets_;
  edm::Handle<reco::CaloJetCollection> recoCaloJets_;
  edm::Handle<reco::PFJetCollection> pfJets_;

  std::string outputRootFileName_;
  std::string recoCaloJetsLabel_;
  std::string pfJetsLabel_;
  std::string genCaloJetsLabel_;
};

#endif
