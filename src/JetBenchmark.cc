#include "RecoParticleFlow/Benchmark/interface/JetBenchmark.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

using namespace std;

JetBenchmark::JetBenchmark() {}

JetBenchmark::~JetBenchmark() {}

void JetBenchmark::setup(string Filename, string Algoname) {

  file_ = new TFile(Filename.data(), "recreate");  

  // delta pt quantities
  char* hname;
  hname=Form("DeltaPt_%s", Algoname.data());
  hDeltaPt = new TH1F(hname,hname,1000,-100,100);
  hname=Form("DeltaPtvsPt_%s", Algoname.data());
  hDeltaPtvsPt = new TH2F(hname,hname,1000,0,1000,1000,-100,100);
  hname=Form("DeltaPtOverPtvsPt_%s", Algoname.data());
  hDeltaPtOverPtvsPt = new TH2F(hname,hname,1000,0,1000,150,-1.5,1.5);//1000,0,1000,150,-1.5,1.5
  hname=Form("DeltaPtvsEta_%s", Algoname.data());
  hDeltaPtvsEta = new TH2F(hname,hname,200,-5,5,1000,-100,100);
  hname=Form("DeltaPtOverPtvsEta_%s", Algoname.data());
  hDeltaPtOverPtvsEta = new TH2F(hname,hname,200,-5,5,150,-1.5,1.5);

  hname=Form("DeltaR_%s", Algoname.data());
  hDeltaR = new TH1F(hname,hname,100,0,1);
  hname=Form("DeltaRvsPt_%s", Algoname.data());
  hDeltaRvsPt = new TH2F(hname,hname,1000,0,1000,100,0,1);

  // delta pt for eta bins
  ietabinlimits.clear();
  ietabinlimits.push_back(0);
  ietabinlimits.push_back(1.4);
  ietabinlimits.push_back(3.0);
  ietabinlimits.push_back(5.0);

  for(size_t ieta=0; ieta < ietabinlimits.size()-1; ieta++)
    {
      TH2F *h2D = new TH2F(Form("DeltaPtOverPtvsPt_eta%.0f-%.0f_%s", ietabinlimits[ieta]*10, ietabinlimits[ieta+1]*10, Algoname.data()), Form("%s resolution   %.1f < |#eta| < %.1f", Algoname.data(), ietabinlimits[ieta], ietabinlimits[ieta+1]), 1000,0,1000,150,-1.5,1.5);
      hDeltaPtOverPtvsPtinEtaBin.push_back(h2D);
    }
  
}

void JetBenchmark::write() {

  if (file_)
    file_->Write();
}
