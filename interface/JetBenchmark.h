#ifndef RecoParticleFlow_Benchmark_JetBenchmark_h
#define RecoParticleFlow_Benchmark_JetBenchmark_h

#include "RecoParticleFlow/Benchmark/interface/PFBenchmarkAlgo.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetfwd.h"

#include <string>
#include <vector>
#include <sstream>

using namespace reco;

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

class JetBenchmark {

 public:

  JetBenchmark();
  virtual ~JetBenchmark();

  void setup(std::string Filename, std::string Algoname);
  template <typename RecoJet, template <typename> class VectorR>
    void process(const VectorR<RecoJet> *, const reco::GenJetCollection *, bool PlotAgainstReco = true, double deltaRMax = 0.1, double JetEtaMin=0, double JetEtaMax=1.);
  void write();

 private:

  TFile *file_;

  TH1F *hDeltaPt;
  TH2F *hDeltaPtvsPt;
  TH2F *hDeltaPtOverPtvsPt;
  TH2F *hDeltaPtvsEta;
  TH2F *hDeltaPtOverPtvsEta;

  TH1F *hDeltaR;
  TH2F *hDeltaRvsPt;
  
  std::vector<TH2F*> hDeltaPtOverPtvsPtinEtaBin;
  std::vector<double> ietabinlimits;
  
 protected:

  PFBenchmarkAlgo *algo_;
};

template <typename RecoJet, template <typename> class VectorR>
void JetBenchmark::process(const VectorR<RecoJet> *Rec, const GenJetCollection *Gen, bool PlotAgainstReco, double deltaRMax, double JetEtaMin, double JetEtaMax) {

  // loop over reco jets
  for (unsigned int irec = 0; irec < Rec->size(); irec++) {

    // generate histograms comparing the reco and truth candidate (truth = closest in delta-R)
    const Jet *jet = &(*Rec)[irec];
    const GenJet *gen_jet = algo_->matchByDeltaR(jet,Gen);
    //const GenJet *gen_jet = &(*(Gen->begin()));
    if(!gen_jet) return;

    // get the quantities to place on the denominator and/or divide by
    double pt, eta, phi;
    if (PlotAgainstReco) { pt = jet->pt(); eta = jet->eta(); phi = jet->phi(); }
    else { pt = gen_jet->pt(); eta = gen_jet->eta(); phi = gen_jet->phi(); }

    // get the delta quantities
    double deltaPt = jet->pt()-gen_jet->pt();
    double deltaR = algo_->deltaR(jet,gen_jet);
                
    //------------------------------------
        
    // fill histograms
    if(deltaR < deltaRMax) 
      {
        if(abs(jet->eta()) > JetEtaMin && abs(jet->eta()) < JetEtaMax)
          {
            hDeltaPt->Fill(deltaPt);
            hDeltaPtvsPt->Fill(pt,deltaPt);
            hDeltaPtOverPtvsPt->Fill(pt,deltaPt/pt);
          } 
        hDeltaPtvsEta->Fill(eta,deltaPt);
        hDeltaPtOverPtvsEta->Fill(eta,deltaPt/pt);

        // for each eta bin
        for(size_t ieta=0; ieta < ietabinlimits.size()-1; ieta++)
          if(abs(jet->eta()) > ietabinlimits[ieta] && 
             abs(jet->eta()) < ietabinlimits[ieta+1])
            {
              hDeltaPtOverPtvsPtinEtaBin[ieta]->Fill(pt,deltaPt/pt);
            }   

      }

    // DR distrib.
    if(abs(jet->eta()) > JetEtaMin && abs(jet->eta()) < JetEtaMax)
      {
        hDeltaR->Fill(deltaR);
        hDeltaRvsPt->Fill(pt,deltaR);
      }
  }

}

#endif // RecoParticleFlow_Benchmark_JetBenchmark_h
