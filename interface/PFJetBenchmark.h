#ifndef RecoParticleFlow_Benchmark_PFJetBenchmark_h
#define RecoParticleFlow_Benchmark_PFJetBenchmark_h

#include "RecoParticleFlow/Benchmark/interface/PFBenchmarkAlgo.h"

//#include "DataFormats/JetReco/interface/PFJetCollection.h"//exported from V2
#include "DataFormats/JetReco/interface/PFJetfwd.h"
#include "DataFormats/JetReco/interface/PFJet.h"
//#include "DataFormats/JetReco/interface/GenJetCollection.h"//exported from V2
#include "DataFormats/JetReco/interface/GenJetfwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleCandidate.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

//#include "DQMServices/Core/interface/DQMStore.h"
//#include "DQMServices/Core/interface/MonitorElement.h"
//#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
//#include "DQMServices/Daemon/interface/MonitorDaemon.h"

#include <TFile.h>
#include <string.h>



//class PFJetBenchmark;

class TH1F;
class TH2F;

//class DQMStore; // CMSSW_2_X_X not needed here?
class DaqMonitorBEInterface;

class PFJetBenchmark {
	
 public:
	
  PFJetBenchmark();
  virtual ~PFJetBenchmark();
	
  void setup(
	     std::string Filename,
	     DaqMonitorBEInterface* db,
	     bool debug, 
	     bool PlotAgainstReco=0, 
	     double deltaRMax=0.1,
             std::string benchmarkLabel_ = "BenchmarkAna", 
	     double recPt = 20, 
	     double maxEta = -1
	     );
  //Version 2.x
  //  void process(const reco::PFJetCollection& , const reco::GenJetCollection& );
  //Version 1x
 void process(const edm::View<reco::Candidate> *RecoCollection, const edm::View<reco::Candidate> *GenCollection);
 // void process(const reco::PFJetCollection& pfJets, const reco::GenJetCollection& genJets);
  void gettrue (const reco::Candidate* truth, double& true_ChargedHadEnergy, 
		double& true_NeutralHadEnergy, double& true_NeutralEmEnergy);
  void getreco (const reco::Candidate* truth, double& true_ChargedHadEnergy, 
		double& true_NeutralHadEnergy, double& true_NeutralEmEnergy);
  void printPFJet (const reco::PFJet*);
  void printGenJet (const reco::GenJet*);
  double resPtMax() const {return resPtMax_;};
  double resChargedHadEnergyMax() const {return resChargedHadEnergyMax_;};
  double resNeutralHadEnergyMax() const {return resNeutralHadEnergyMax_;};
  double resNeutralEmEnergyMax() const {return resNeutralEmEnergyMax_;};
  void save();	

 private:
	
  TFile *file_;
	
  // histograms
  // Jets inclusive  distributions  (Pt > 20 GeV)
  TH1F *hNjets;
  TH1F *hjetsPt;
  TH1F *hjetsEta;
	
  // delta Pt or E quantities for Barrel
  TH1F *hBRPt;
  TH1F *hBRCHE;
  TH1F *hBRNHE;
  TH1F *hBRNEE;
  TH1F *hBRneut;
  TH2F *hBRPtvsPt ;
  TH2F *hBRCHEvsPt ;
  TH2F *hBRNHEvsPt;
  TH2F *hBRNEEvsPt;
  TH2F *hBRneutvsPt;
	
  // delta Pt or E quantities for Endcap
  TH1F *hERPt ;
  TH1F *hERCHE;
  TH1F *hERNHE;
  TH1F *hERNEE;
  TH1F *hERneut;
  TH2F *hERPtvsPt ;
  TH2F *hERCHEvsPt;
  TH2F *hERNHEvsPt ;
  TH2F *hERNEEvsPt;
  TH2F *hERneutvsPt;
	
  std::string outputFile_;	
 protected:
		
  PFBenchmarkAlgo *algo_;
  bool debug_;
  bool PlotAgainstReco_;
  double deltaRMax_;
  double resPtMax_;
  double resChargedHadEnergyMax_;
  double resNeutralHadEnergyMax_;
  double resNeutralEmEnergyMax_; 
  double recPt_cut;
  double maxEta_cut;
  //DQMStore *dbe_; //V 2_...
  DaqMonitorBEInterface *dbe_;
};

#endif // RecoParticleFlow_Benchmark_PFJetBenchmark_h
