#include "RecoParticleFlow/Benchmark/interface/TauBenchmarkAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "TFile.h"
#include "TDirectory.h"
#include "TH1F.h"

using namespace std;
using namespace edm;

TauBenchmarkAnalyzer::TauBenchmarkAnalyzer(const ParameterSet& iConfig) {

  outputRootFileName_ = iConfig.getUntrackedParameter<string>("outputRootFileName");
  caloJetsLabel_      = iConfig.getUntrackedParameter<string>("recoCaloJetsLabel");
  pfJetsLabel_        = iConfig.getUntrackedParameter<string>("pfJetsLabel");
  genJetsLabel_       = iConfig.getUntrackedParameter<string>("genCaloJetsLabel");

  // Create an Instance of the Benchmark Helper Class
  algo_ = new PFBenchmarkAlgo();

}

TauBenchmarkAnalyzer::~TauBenchmarkAnalyzer() { }

void TauBenchmarkAnalyzer::beginJob(const EventSetup& iSetup) {

  // Create the Output File
  output_ = new TFile(outputRootFileName_.c_str(),"RECREATE");

  // Book Histograms

  // Gen-CaloJet Comparisons
  TDirectory *dirCaloJets = output_->mkdir("CaloJets");
  dirCaloJets->cd();

  h_DeltaEt_Jet_Gen = new TH1F("h_DeltaEt_Jet_Gen","Jet #Delta E_{T} (CaloJet - Gen);#Delta E_{T}",100,-50,50);
  h_DeltaEta_Jet_Gen = new TH1F("h_DeltaEta_Jet_Gen","Jet #Delta #Eta (CaloJet - Gen);#Delta #Eta",50,-3,3);
  h_DeltaPhi_Jet_Gen = new TH1F("h_DeltaPhi_Jet_Gen","Jet #Delta #Phi (CaloJet - Gen);#Delta #Phi",250,-0.2,0.2);

  TDirectory *dirCaloJetsTrue = output_mkdir("CaloJets/vs_gen");
  dirCaloJetsTrue->cd();

  h_DeltaEtOverTrueEt_Jet_Gen = new TH1F("h_DeltaEtOverTrueEt_Jet_Gen","Jet #Delta E_{T} over True Et;#Delta E_{T}/E_{T true};",100,-2,2);
  h_DeltaEtvsTrueEt_Jet_Gen = new TH2F("h_DeltaEtvsTrueEt_Jet_Gen","Jet #Delta E_{T} vs. E_{T true};E_{true};#Delta E_{T}",50,0,200,100,-50,50);
  h_DeltaEtvsTrueEta_Jet_Gen = new TH2F("h_DeltaEtvsTrueEta_Jet_Gen","Jet #Delta E_{T} vs. #Eta_{true};#Eta_{true};#Delta E_{T}",50,-3,3,100,-50,50);
  h_DeltaEtOverTrueEtvsTrueEt_Jet_Gen = new TH2F("h_DeltaEtOverTrueEtvsEt_Jet_Gen" , "#Delta E_{T}/E_{T true} vs E_{T true};E_{T true};#Delta E_{T}/E_{T true}",50,0,200,100,-2,2);
  h_DeltaEtOverTrueEtvsTrueEta_Jet_Gen = new TH2F("h_DeltaEtOverTrueEtvsEta_Jet_Gen" , "#Delta E_{T}/E_{T true} vs #Eta;#Eta;#Delta E_{T}/E_{T true}",50,0,200,50,-3,3);

  h_DeltaEtaOverTrueEta_Jet_Gen = new TH1F("h_DeltaEtaOverTrueEta_Jet_Gen","Jet #Delta #Eta over True #Eta;#Delta #Eta/#Eta_{true};",100,-.5,.5);
  h_DeltaEtavsTrueEt_Jet_Gen = new TH2F("h_DeltaEtavsTrueEt_Jet_Gen","Jet #Delta #Eta vs. E_{T true};E_{true};#Delta #Eta",50,0,200,50,-3,3);
  h_DeltaEtavsTrueEta_Jet_Gen = new TH2F("h_DeltaEtavsTrueEta_Jet_Gen","Jet #Delta #Eta vs. #Eta_{true};#Eta_{true};#Delta #Eta",50,0,200,50,-3,3);
  h_DeltaEtaOverTrueEtavsTrueEt_Jet_Gen = new TH2F("h_DeltaEtaOverTrueEtavsEt_Jet_Gen" , "#Delta #Eta /#Eta_{true} vs E_{T true};E_{T true};#Delta E_{T}/E_{T true}",50,0,200,100,-2,2);
  h_DeltaEtaOverTrueEtavsTrueEta_Jet_Gen = new TH2F("h_DeltaEtOverTrueEtavsEta_Jet_Gen" , "#Delta E_{T}/E_{T true} vs #Eta;#Eta;#Delta E_{T}/E_{T true}",50,0,200,50,-3,3);

  TDirectory *dirCaloJetsReco = output_mkdir("CaloJets/vs_reco");
  dirCaloJetsReco->cd();

  h_DeltaEtOverRecoEt_Jet_Gen = new TH1F("h_DeltaEtOverRecoEt_Jet_Gen","Jet #Delta E_{T} over Reco Et;#Delta E_{T}/E_{T reco};",100,-2,2);

  h_DeltaEtvsRecoEt_Jet_Gen = new TH2F("h_DeltaEtvsRecoEt_Jet_Gen","Jet #Delta E_{T} vs. E_{T reco};E_{reco};#Delta E_{T}",50,0,200,100,-50,50);
  h_DeltaEtvsRecoEta_Jet_Gen = new TH2F("h_DeltaEtvsRecoEta_Jet_Gen","Jet #Delta E_{T} vs. #Eta_{true};#Eta_{true};#Delta E_{T}",50,-3,3,100,-50,50);
  h_DeltaEtOverRecoEtvsRecoEt_Jet_Gen = new TH2F("h_DeltaEtOverRecovsEt_Jet_Gen" , "#Delta E_{T}/E_{T reco} vs E_{T};E_{T};#Delta E_{T}/E_{T reco}",50,0,200,100,-2,2);
  h_DeltaEtOverRecoEtvsRecoEta_Jet_Gen = new TH2F("h_DeltaEtOverRecovsEta_Jet_Gen" , "#Delta E_{T}/E_{T reco} vs #Eta;#Eta;#Delta E_{T}/E_{T reco}",50,0,200,50,-3,3);

  h_DeltaEtavsRecoEta_Jet_Gen = new TH2F("h_DeltaEtavsRecoEta_Jet_Gen","Jet #Delta #Eta vs. #Eta_{reco};#Eta_{reco};#Delta #Eta",50,0,200,50,-3,3);
  h_DeltaEtavsRecoEta_Jet_Gen = new TH2F("h_DeltaEtavsRecoEta_Jet_Gen","Jet #Delta #Eta vs. #Eta_{true};#Eta_{true};#Delta #Eta",50,0,200,50,-3,3);

  // Gen-PF Comparisons
  TDirectory *dirPFlow = output_->mkdir("PFlow");
  dirPFLow->cd();

  h_DeltaEt_PF_Gen = new TH1F("h_DeltaEt_PF_Gen","Jet #Delta E_{T} (PFLow - Gen);#Delta E_{T}",100,-50,50);
  h_DeltaEta_PF_Gen = new TH1F("h_DeltaEta_PF_Gen","Jet #Delta #Eta (CaloJet - Gen);#Delta #Eta",50,-3,3);
  h_DeltaPhi_PF_Gen = new TH1F("h_DeltaPhi_PF_Gen","Jet #Delta #Phi (CaloJet - Gen);#Delta #Phi",250,-0.2,0.2);

  h_DeltaEtOverTrueEt_PF_Gen = new TH1F("h_DeltaEtOverTrueEt_PF_Gen","Jet #Delta E_{T} over True Et;#Delta E_{T}/E_{T true};",100,-2,2);
  h_DeltaEtOverRecoEt_PF_Gen = new TH1F("h_DeltaEtOverRecoEt_PF_Gen","Jet #Delta E_{T} over Reco Et;#Delta E_{T}/E_{T reco};",100,-2,2);
  
  h_DeltaEtvsTrueEt_PF_Gen = new TH2F("h_DeltaEtvsTrueEt_PF_Gen","Jet #Delta E_{T} vs. E_{T true};E_{True};#Delta E_{T}",50,0,200,100,-50,50);
  h_DeltaEtvsRecoEt_PF_Gen = new TH2F("h_DeltaEtvsRecoEt_PF_Gen","Jet #Delta E_{T} vs. E_{T reco};E_{reco};#Delta E_{T}",50,0,200,100,-50,50);

  h_DeltaEtvsEta_PF_Gen = new TH2F("h_DeltaEtvsEta_PF_Gen","Jet #Delta E_{T} vs. #Eta_{true};#Eta_{true};#Delta E_{T}",50,-3,3,100,-50,50);
  h_DeltaEtavsEt_PF_Gen = new TH2F("h_DeltaEtavsEt_PF_Gen","Jet #Delta #Eta vs. E_{T true};E_{True};#Delta #Eta",50,0,200,50,-3,3);

  h_DeltaEtavsTrueEta_PF_Gen = new TH2F("h_DeltaEtavsEta_PF_Gen","Jet #Delta #Eta vs. #Eta_{true};#Eta_{true};#Delta #Eta",50,0,200,50,-3,3);
  h_DeltaEtavsRecoEta_PF_Gen = new TH2F("h_DeltaEtavsEta_PF_Gen","Jet #Delta #Eta vs. #Eta_{reco};#Eta_{reco};#Delta #Eta",50,0,200,50,-3,3);

  h_DeltaEtOverTruevsEt_PF_Gen = new TH2F("h_DeltaEtOverTruevsEt_PF_Gen" , "#Delta E_{T}/E_{T true} vs E_{T};E_{T};#Delta E_{T}/E_{T true}",50,0,200,100,-2,2);
  h_DeltaEtOverRecovsEt_PF_Gen = new TH2F("h_DeltaEtOverRecovsEt_PF_Gen" , "#Delta E_{T}/E_{T reco} vs E_{T};E_{T};#Delta E_{T}/E_{T reco}",50,0,200,100,-2,2);
  h_DeltaEtOverTruevsEta_PF_Gen = new TH2F("h_DeltaEtOverTruevsEta_PF_Gen" , "#Delta E_{T}/E_{T true} vs #Eta;#Eta;#Delta E_{T}/E_{T true}",50,0,200,50,-3,3);
  h_DeltaEtOverRecovsEta_PF_Gen = new TH2F("h_DeltaEtOverRecovsEta_PF_Gen" , "#Delta E_{T}/E_{T reco} vs #Eta;#Eta;#Delta E_{T}/E_{T reco}",50,0,200,50,-3,3);

}

TauBenchmarkAnalyzer

TauBenchmarkAnalyzer
TauBenchmarkAnalyzer
