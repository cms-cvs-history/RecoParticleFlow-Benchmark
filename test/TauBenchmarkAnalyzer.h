#ifndef RecoParticleFlow_Benchmark_TauBenchmarkAnalyzer_h
#define RecoParticleFlow_Benchmark_TauBenchmarkAnalyzer_h

#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include <string>
#include <map>

class PFBenchmarkAlgo;

class TauBenchmarkAnalyzer: public edm::EDAnalyzer {
public:

  explicit TauBenchmarkAnalyzer(const edm::ParameterSet&);
  ~TauBenchmarkAnalyzer();

  void beginJob(const edm::EventSetup&);
  void analyze(const edm::Event&, const edm::EventSetup&);
  void endJob();

private:

  // DAQ Tools
  DaqMonitorBEInterface* dbe_;
  std::map<std::string, MonitorElement*> me;

  // Benchmark Tools
  PFBenchmarkAlgo *algo_;

  // Configuration Parameters
  std::string outputRootFileName_;
  std::string caloJetsLabel_;
  std::string pfJetsLabel_;
  std::string genJetsLabel_;

  /*
  //__CaloJet-Gen Comparison Histograms__
  TH1F *h_DeltaEt_Jet_Gen;
  TH1F *h_DeltaEta_Jet_Gen;
  TH1F *h_DeltaPhi_Jet_Gen;

  TH1F *h_DeltaEtOverTrueEt_Jet_Gen;
  TH1F *h_DeltaEtOverRecoEt_Jet_Gen;

  TH2F *h_DeltaEtvsEt_Jet_Gen;
  TH2F *h_DeltaEtavsEt_Jet_Gen;
  TH2F *h_DeltaPhivsEt_Jet_Gen;
  TH2F *h_DeltaEtvsEta_Jet_Gen;

  TH2F *h_DeltaEtOverTrueEtvsEt_Jet_Gen;
  TH2F *h_DeltaEtOverRecoEtvsEt_Jet_Gen;
  TH2F *h_DeltaEtOverTrueEtvsEta_Jet_Gen;
  TH2F *h_DeltaEtOverRecoEtvsEta_Jet_Gen;

  //__PFlow-Gen Comparison Histograms__
  TH1F *h_DeltaEt_PF_Gen;
  TH1F *h_DeltaEta_PF_Gen;
  TH1F *h_DeltaPhi_PF_Gen;

  TH1F *h_DeltaEtOverTrueEt_PF_Gen;
  TH1F *h_DeltaEtOverRecoEt_PF_Gen;

  TH2F *h_DeltaEtvsEt_PF_Gen;
  TH2F *h_DeltaPhivsEt_PF_Gen;
  TH2F *h_DeltaEtavsEt_PF_Gen;
  TH2F *h_DeltaEtvsEta_PF_Gen;

  TH2F *h_DeltaEtOverTruevsEt_PF_Gen;
  TH2F *h_DeltaEtOverRecovsEt_PF_Gen;
  TH2F *h_DeltaEtOverTruevsEta_PF_Gen;
  TH2F *h_DeltaEtOverRecovsEta_PF_Gen;
  */
};

#endif // RecoParticleFlow_Benchmark_TauBenchmarkAnalyzer_h
