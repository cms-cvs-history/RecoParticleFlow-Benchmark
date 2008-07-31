
#include "RecoParticleFlow/Benchmark/interface/PFJetBenchmark.h"

#include "FWCore/ServiceRegistry/interface/Service.h" 
//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DQMServices/CoreROOT/interface/CollateMERoot.h"
#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"


#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include <string>

// preprocessor macro for booking 1d histos with DaqMonitorBEInterface -or- bare Root
#define BOOK1D(name,title,nbinsx,lowx,highx) \
  if (dbe_) { \
    MonitorElement *me = dbe_->book1D(#name,title,nbinsx,lowx,highx); \
    MonitorElementT<TNamed> *ob = dynamic_cast<MonitorElementT<TNamed>* >(me); \
    if (ob) h##name = dynamic_cast<TH1F *>(ob->operator->()); \
  } else h##name = new TH1F(#name,title,nbinsx,lowx,highx)

// preprocessor macro for booking 2d histos with DaqMonitorBEInterface -or- bare Root
#define BOOK2D(name,title,nbinsx,lowx,highx,nbinsy,lowy,highy) \
  if (dbe_) { \
    MonitorElement *me = dbe_->book2D(#name,title,nbinsx,lowx,highx,nbinsy,lowy,highy); \
    MonitorElementT<TNamed> *ob = dynamic_cast<MonitorElementT<TNamed>* >(me); \
    if (ob) h##name = dynamic_cast<TH2F *>(ob->operator->()); \
  } else h##name = new TH2F(#name,title,nbinsx,lowx,highx,nbinsy,lowy,highy)

//Version 2_1_
/*
// preprocessor macro for booking 1d histos with DQMStore -or- bare Root
#define BOOK1D(name,title,nbinsx,lowx,highx) \
  h##name = dbe_ ? dbe_->book1D(#name,title,nbinsx,lowx,highx)->getTH1F() \
    : new TH1F(#name,title,nbinsx,lowx,highx)

// preprocessor macro for booking 2d histos with DQMStore -or- bare Root
#define BOOK2D(name,title,nbinsx,lowx,highx,nbinsy,lowy,highy) \
  h##name = dbe_ ? dbe_->book2D(#name,title,nbinsx,lowx,highx,nbinsy,lowy,highy)->getTH2F() \
    : new TH2F(#name,title,nbinsx,lowx,highx,nbinsy,lowy,highy)
*/
//macros for building barrel and endcap histos with one call
#define DBOOK1D(name,title,nbinsx,lowx,highx) \
  BOOK1D(B##name,"Barrel "#title,nbinsx,lowx,highx); BOOK1D(E##name,"Endcap "#title,nbinsx,lowx,highx);
#define DBOOK2D(name,title,nbinsx,lowx,highx,nbinsy,lowy,highy) \
  BOOK2D(B##name,"Barrel "#title,nbinsx,lowx,highx,nbinsy,lowy,highy); BOOK2D(E##name,"Endcap "#title,nbinsx,lowx,highx,nbinsy,lowy,highy);

// all versions OK
// preprocesor macro for setting axis titles
#define SETAXES(name,xtitle,ytitle) \
  h##name->GetXaxis()->SetTitle(xtitle); h##name->GetYaxis()->SetTitle(ytitle)

//macro for setting the titles for barrel and endcap together
#define DSETAXES(name,xtitle,ytitle) \
  SETAXES(B##name,xtitle,ytitle);SETAXES(E##name,xtitle,ytitle)
/*#define SET2AXES(name,xtitle,ytitle) \
  hE##name->GetXaxis()->SetTitle(xtitle); hE##name->GetYaxis()->SetTitle(ytitle);  hB##name->GetXaxis()->SetTitle(xtitle); hB##name->GetYaxis()->SetTitle(ytitle)
*/

#define PT (PlotAgainstReco_)?"reconstructed P_{T}" :"generated P_{T}"

using namespace reco;
using namespace std;

//class MonitorElement;


PFJetBenchmark::PFJetBenchmark() {}

PFJetBenchmark::~PFJetBenchmark() {}

void PFJetBenchmark::save() {
   // Store the DAQ Histograms 
  if (outputFile_.size() != 0) {
    if (dbe_)
          dbe_->save(outputFile_.c_str());
    // use bare Root if no DQM (FWLite applications)
    else if (file_)
      file_->Write(outputFile_.c_str());
  }
  else 
    cout << "No output file specified ("<<outputFile_<<"). Results will not be saved!" << endl;

} 

void PFJetBenchmark::setup(string Filename,
			   DaqMonitorBEInterface* db,
			   bool debug, 
			   bool PlotAgainstReco, 
			   double deltaRMax, 
			   string benchmarkLabel_, 
			   double recPt, 
			   double maxEta) {
  debug_ = debug; 
  PlotAgainstReco_ = PlotAgainstReco; 
  deltaRMax_ = deltaRMax;
  outputFile_=Filename;
  recPt_cut = recPt;
  maxEta_cut= maxEta;
  file_ = NULL;
  dbe_ = NULL;
  // print parameters
  cout<< "PFJetBenchmark Setup parameters =============================================="<<endl;
  cout << "Filename ot write histograms " << Filename<<endl;
  cout << "PFJetBenchmark debug " << debug_<< endl;
  cout << "PlotAgainstReco " << PlotAgainstReco_ << endl;
  cout << "deltaRMax " << deltaRMax << endl;
  // Book histogram

  // Establish DQM Store
  dbe_ = db;
  string path = "PFTask/Benchmarks/"+ benchmarkLabel_ + "/";
  if (PlotAgainstReco) path += "Reco"; else path += "Gen";
  if (dbe_) {
    dbe_->setCurrentFolder(path.c_str());
  }
  else {
    file_ = new TFile();
    cout << "Warning: DQM is not available to support data storage service. Errors in saving might occur. "<<endl;
  }
  // Jets inclusive  distributions  (Pt > 20 or specified recPt GeV)
  char cutString[35];
  sprintf(cutString,"Jet multiplicity P_{T}>%4.1f GeV", recPt_cut);
  BOOK1D(Njets,cutString,50, 0, 50);

  BOOK1D(jetsPt,"Jets P_{T} Distribution",100, 0, 500);

  sprintf(cutString,"Jets #eta Distribution |#eta|<%4.1f", maxEta_cut);
  BOOK1D(jetsEta,cutString,100, -5, 5);
	
  // delta Pt or E quantities for Barrel
  DBOOK1D(RPt,#DeltaP_{T}/P_{T},80,-2,2);
  DBOOK1D(RCHE,#DeltaE/E (charged had),80,-2,2);
  DBOOK1D(RNHE,#DeltaE/E (neutral had),80,-2,2);
  DBOOK1D(RNEE,#DeltaE/E (neutral em),80,-2,2);
  DBOOK1D(Rneut,#DeltaE/E (neutral),80,-2,2);
  DBOOK2D(RPtvsPt,#DeltaP_{T}/P_{T} vs P_{T},40, 0, 500, 80,-2,2);       //used to be 50 bin for each in x-direction
  DBOOK2D(RCHEvsPt,#DeltaE/E (charged had) vs P_{T},40, 0, 500, 80,-2,2);
  DBOOK2D(RNHEvsPt,#DeltaE/E (neutral had) vs P_{T},40, 0, 500, 80,-2,2);
  DBOOK2D(RNEEvsPt,#DeltaE/E (neutral em) vs P_{T},40, 0, 500, 80,-2,2);
  DBOOK2D(RneutvsPt,#DeltaE/E (neutral) vs P_{T},40, 0, 500, 80,-2,2);
	
 // Set Axis Titles
 
 // Jets inclusive  distributions  (Pt > 20 GeV)
  SETAXES(Njets,"","Multiplicity");
  SETAXES(jetsPt, PT, "Number of Events");
  SETAXES(jetsEta, "#eta", "Number of Events");
  // delta Pt or E quantities for Barrel and Endcap
  DSETAXES(RPt, "#DeltaP_{T}/P_{T}", "Events");
  DSETAXES(RCHE, "#DeltaE/E(charged had)", "Events");
  DSETAXES(RNHE, "#DeltaE/E(neutral had)", "Events");
  DSETAXES(RNEE, "#DeltaE/E(neutral em)", "Events");
  DSETAXES(Rneut, "#DeltaE/E(neutral)", "Events");
  DSETAXES(RPtvsPt, PT, "#DeltaP_{T}/P_{T}");
  DSETAXES(RCHEvsPt, PT, "#DeltaE/E(charged had)");
  DSETAXES(RNHEvsPt, PT, "#DeltaE/E(neutral had)");
  DSETAXES(RNEEvsPt, PT, "#DeltaE/E(neutral em)");
  DSETAXES(RneutvsPt, PT, "#DeltaE/E(neutral)");

}


void PFJetBenchmark::process(const edm::View<reco::Candidate> *pfJets, const edm::View<reco::Candidate> *genJets) {
  // loop over reco  pf  jets
  resPtMax_ = 0.;
  resChargedHadEnergyMax_ = 0.;
  resNeutralHadEnergyMax_ = 0.;
  resNeutralEmEnergyMax_ = 0.; 
  int NPFJets = 0;
	
  for(unsigned i=0; i<pfJets->size(); i++) {   
		
    const reco::Candidate *pfj = &(*pfJets)[i];
    //const reco::PFJet& pfj = pfJets[i];
    double rec_pt = pfj->pt();
    double rec_eta = pfj->eta();
    double rec_phi = pfj->phi();
    // skip PFjets with pt < recPt_cut GeV
    if (rec_pt<recPt_cut and recPt_cut != -1.) continue;
    // skip PFjets with eta > maxEta_cut
    if (fabs(rec_eta)>maxEta_cut and maxEta_cut != -1.) continue;

    NPFJets++;
		
    // fill inclusive PFjet distribution pt > 20 GeV
    hNjets->Fill(NPFJets);
    hjetsPt->Fill(rec_pt);
    hjetsEta->Fill(rec_eta);

    // separate Barrel PFJets from Endcap PFJets
    bool Barrel = false;
    bool Endcap = false;
    if (abs(rec_eta) < 1.4 ) Barrel = true;
    if (abs (rec_eta) > 1.6 && abs (rec_eta) < 3. ) Endcap = true;

    // do only barrel for now
    //  if(!Barrel) continue;

    // look for the closets gen Jet : truth
    const reco::Candidate *truth = algo_->matchByDeltaR(pfj,genJets);
    //const GenJet *truth = algo_->matchByDeltaR(&pfj,genJets);
    if(!truth) continue;   
    double deltaR = algo_->deltaR(pfj, truth);
    // check deltaR is small enough
    if(deltaR < deltaRMax_) {//start case deltaR < deltaRMax
      // generate histograms comparing the reco and truth candidate (truth = closest in delta-R) 
      // get the quantities to place on the denominator and/or divide by
      double pt_denom;
      double true_pt = truth->pt();
      if (PlotAgainstReco_) {pt_denom = rec_pt;}
      else {pt_denom = true_pt;}
      // get true specific quantities
      double true_ChargedHadEnergy;
      double true_NeutralHadEnergy;
      double true_NeutralEmEnergy;
      gettrue (truth, true_ChargedHadEnergy, true_NeutralHadEnergy, true_NeutralEmEnergy);
      double true_NeutralEnergy = true_NeutralHadEnergy + true_NeutralEmEnergy;
//      double rec_ChargedHadEnergy = pfj->chargedHadronEnergy();
//      double rec_NeutralHadEnergy = pfj.neutralHadronEnergy();
//      double rec_NeutralEmEnergy = pfj.neutralEmEnergy();
      double rec_ChargedHadEnergy=0.;
      double rec_NeutralHadEnergy = 0.;
      double rec_NeutralEmEnergy = 0.;
      getreco (pfj, rec_ChargedHadEnergy, rec_NeutralHadEnergy, rec_NeutralEmEnergy);
      double rec_NeutralEnergy = rec_NeutralHadEnergy + rec_NeutralEmEnergy;
      bool plot1 = false;
      bool plot2 = false;
      bool plot3 = false;
      bool plot4 = false;
      bool plot5 = false;
      double cut1 = 0.0001;
      double cut2 = 0.0001;
      double cut3 = 0.0001;
      double cut4 = 0.0001;
      double cut5 = 0.0001;
      double resPt =0.;
      double resChargedHadEnergy= 0.;
      double resNeutralHadEnergy= 0.;
      double resNeutralEmEnergy= 0.;
      double resNeutralEnergy= 0.;
      // get relative delta quantities (protect against division by zero!)
      if (true_pt > 0.0001){
	resPt = (rec_pt -true_pt)/true_pt ; 
	plot1 = true;}
      if (true_ChargedHadEnergy > cut1){
	resChargedHadEnergy = (rec_ChargedHadEnergy- true_ChargedHadEnergy)/true_ChargedHadEnergy;
	plot2 = true;}
  
    if (true_NeutralHadEnergy > cut2){
	resNeutralHadEnergy = (rec_NeutralHadEnergy- true_NeutralHadEnergy)/true_NeutralHadEnergy;
	plot3 = true;}
    else if (rec_NeutralHadEnergy > cut3){
	  resNeutralHadEnergy = (rec_NeutralHadEnergy- true_NeutralHadEnergy)/rec_NeutralHadEnergy;
	  plot3 = true;}

      if (true_NeutralEmEnergy > cut4){
	resNeutralEmEnergy = (rec_NeutralEmEnergy- true_NeutralEmEnergy)/true_NeutralEmEnergy;
	plot4 = true;}
      if (true_NeutralEnergy > cut5){
	resNeutralEnergy = (rec_NeutralEnergy- true_NeutralEnergy)/true_NeutralEnergy;
	plot5 = true;}
			
	 		
      //double deltaEta = algo_->deltaEta(&pfj, truth);
      //double deltaPhi = algo_->deltaPhi(&pfj, truth);
      if(abs(resPt) > resPtMax_) resPtMax_ = abs(resPt);
      if(abs(resChargedHadEnergy) > resChargedHadEnergyMax_) resChargedHadEnergyMax_ = abs(resChargedHadEnergy);
      if(abs(resNeutralHadEnergy) > resNeutralHadEnergyMax_) resNeutralHadEnergyMax_ = abs(resNeutralHadEnergy);
      if(abs(resNeutralEmEnergy) > resNeutralEmEnergyMax_) resNeutralEmEnergyMax_ = abs(resNeutralEmEnergy);
      if (debug_) {
	cout << i <<"  =========PFJet Pt "<< rec_pt
	     << " eta " << rec_eta
	     << " phi " << rec_phi
	     << " Charged Had Energy " << rec_ChargedHadEnergy
	     << " Neutral Had Energy " << rec_NeutralHadEnergy
	     << " Neutral elm Energy " << rec_NeutralEmEnergy << endl;
	cout << " matching Gen Jet Pt " << true_pt
	     << " eta " << truth->eta()
	     << " phi " << truth->phi()
	     << " Charged Had Energy " << true_ChargedHadEnergy
	     << " Neutral Had Energy " << true_NeutralHadEnergy
	     << " Neutral elm Energy " << true_NeutralEmEnergy << endl;
//	printPFJet(&pfj);
	//      cout<<pfj.print()<<endl;
//	printGenJet(truth);
	//cout <<truth->print()<<endl;
				
	cout << "==============deltaR " << deltaR << "  resPt " << resPt
	     << " resChargedHadEnergy " << resChargedHadEnergy
	     << " resNeutralHadEnergy " << resNeutralHadEnergy
	     << " resNeutralEmEnergy " << resNeutralEmEnergy
	     << endl;
      }
			
      // fill histograms for relative delta quantitites of matched jets
      // delta Pt or E quantities for Barrel
      if (Barrel){
	if(plot1)hBRPt->Fill (resPt);
	if(plot2)hBRCHE->Fill(resChargedHadEnergy);
	if(plot3)hBRNHE->Fill(resNeutralHadEnergy);
	if(plot4)hBRNEE->Fill(resNeutralEmEnergy);
	if(plot5)hBRneut->Fill(resNeutralEnergy);
	if(plot1)hBRPtvsPt->Fill(pt_denom, resPt);
	if(plot2)hBRCHEvsPt->Fill(pt_denom, resChargedHadEnergy);
	if(plot3)hBRNHEvsPt->Fill(pt_denom, resNeutralHadEnergy);
	if(plot4)hBRNEEvsPt->Fill(pt_denom, resNeutralEmEnergy);
	if(plot5)hBRneutvsPt->Fill(pt_denom, resNeutralEnergy);
      }
      // delta Pt or E quantities for Endcap
      if (Endcap){
	if(plot1)hERPt->Fill (resPt);
	if(plot2)hERCHE->Fill(resChargedHadEnergy);
	if(plot3)hERNHE->Fill(resNeutralHadEnergy);
	if(plot4)hERNEE->Fill(resNeutralEmEnergy);
	if(plot5)hERneut->Fill(resNeutralEnergy);
	if(plot1)hERPtvsPt->Fill(pt_denom, resPt);
	if(plot2)hERCHEvsPt->Fill(pt_denom, resChargedHadEnergy);
	if(plot3)hERNHEvsPt->Fill(pt_denom, resNeutralHadEnergy);
	if(plot4)hERNEEvsPt->Fill(pt_denom, resNeutralEmEnergy);
	if(plot5)hERneutvsPt->Fill(pt_denom, resNeutralEnergy);
      }						
    } // end case deltaR < deltaRMax
		
  } // i loop on pf Jets	
}

void PFJetBenchmark::gettrue (const reco::Candidate* truth, double& true_ChargedHadEnergy, 
			      double& true_NeutralHadEnergy, double& true_NeutralEmEnergy){

  //    std::vector <const GenParticle*> mcparts = truth->getGenConstituents();
  //std::vector <const GenParticleCandidate*> mcparts = truth->getConstituents();
  std::vector <const reco::Candidate*> mcparts;
  for(unsigned i=0;i<(truth->numberOfDaughters());i++)
   	mcparts.push_back( truth->daughter(i) );


  true_NeutralEmEnergy = 0.;
  true_ChargedHadEnergy = 0.;
  true_NeutralHadEnergy = 0.;
  // for each MC particle in turn  
  for (unsigned i = 0; i < mcparts.size (); i++) {
    const Candidate* mcpart = mcparts[i];
    int PDG = abs( mcpart->pdgId());
    double e = mcpart->energy(); 
    switch(PDG){  // start PDG switch
    case 22: // photon
      true_NeutralEmEnergy += e;
      break;
    case 211: // pi
    case 321: // K
    case 2212: // p
    case 11: //electrons (until recognised)
      true_ChargedHadEnergy += e;
      break;
    case 310: // K_S0
    case 130: // K_L0
    case 3122: // Lambda0
    case 2112: // n0
      true_NeutralHadEnergy += e;
    default:
      break;
    }  // end PDG switch		
  }  // end loop on constituents.
}

void PFJetBenchmark::getreco (const reco::Candidate* truth, double& true_ChargedHadEnergy, 
			      double& true_NeutralHadEnergy, double& true_NeutralEmEnergy){

  //    std::vector <const GenParticle*> mcparts = truth->getGenConstituents();
  //std::vector <const GenParticleCandidate*> mcparts = truth->getConstituents();
  std::vector <const reco::Candidate*> mcparts;
  for(unsigned i=0;i<(truth->numberOfDaughters());i++)
   	mcparts.push_back( truth->daughter(i) );


  true_NeutralEmEnergy = 0.;
  true_ChargedHadEnergy = 0.;
  true_NeutralHadEnergy = 0.;
  // for each MC particle in turn  
  for (unsigned i = 0; i < mcparts.size (); i++) {
    const Candidate* mcpart = mcparts[i];
    
    int PDG = abs( mcpart->pdgId());
    double e = mcpart->energy(); 
    switch(PDG){  // start PDG switch
    case 22: // photon
      true_NeutralEmEnergy += e;
      break;
    case 211: // pi
    case 321: // K
    case 2212: // p
    case 11: //electrons (until recognised)
      true_ChargedHadEnergy += e;
      break;
    case 310: // K_S0
    case 130: // K_L0
    case 3122: // Lambda0
    case 2112: // n0
      true_NeutralHadEnergy += e;
    default:
      break;
    }  // end PDG switch		
  }  // end loop on constituents.
  
  const reco::PFJet* pjot = dynamic_cast<const PFJet*>(truth);
  if (pjot!=NULL) 
  {  
  true_ChargedHadEnergy = pjot->chargedHadronEnergy(); 
  true_NeutralHadEnergy = pjot->neutralHadronEnergy(); 
  true_NeutralEmEnergy = pjot->neutralEmEnergy();
	cout << "unnull!";
  }
  else {
  cout << "dyncast unmoeglich!!!";
  cerr << "DYNCAST war nicht moeglich. Fehler in den Energie-Histogrammen zu erwarten!";
  }
  
}
void PFJetBenchmark::printPFJet(const reco::PFJet* pfj){
  cout<<setiosflags(ios::right);
  cout<<setiosflags(ios::fixed);
  cout<<setprecision(3);
  std::vector <const PFCandidate*> pfCandidates = pfj->getConstituents ();
  cout << "PFJet  p/px/py/pz/pt: " << pfj->p() << '/' << pfj->px () 
       << '/' << pfj->py() << '/' << pfj->pz() << '/' << pfj->pt() << endl
       << "    eta/phi: " << pfj->eta () << '/' << pfj->phi () << endl   		
       << "    PFJet specific:" << std::endl
       << "      charged/neutral hadrons energy: " << pfj->chargedHadronEnergy () << '/' << pfj->neutralHadronEnergy () << endl
       << "      charged/neutral em energy: " << pfj->chargedEmEnergy () << '/' << pfj->neutralEmEnergy () << endl
       << "      charged muon energy: " << pfj->chargedMuEnergy () << '/' << endl
       << "      charged/neutral multiplicity: " << pfj->chargedMultiplicity () << '/' << pfj->neutralMultiplicity () << endl
       << "    # of pfCandidates: " << pfCandidates.size() << endl;
  vector <PFBlockRef> PFBRef;
  // print PFCandidates constituents of the jet
  for(unsigned i=0; i<pfCandidates.size(); i++) {
    const PFCandidate* pfCand = pfCandidates[i];
    cout<<i <<" " << *pfCand << endl;
  } // end loop on i (PFCandidates)
  // print blocks associated to the jet (to be done with new format PFCandiates)
	
  cout<<resetiosflags(ios::right|ios::fixed);
}


void PFJetBenchmark::printGenJet (const reco::GenJet* truth){
  std::vector <const GenParticleCandidate*> mcparts = truth->getConstituents ();
  cout << "GenJet p/px/py/pz/pt: " << truth->p() << '/' << truth->px () 
       << '/' << truth->py() << '/' << truth->pz() << '/' << truth->pt() << endl
       << "    eta/phi: " << truth->eta () << '/' << truth->phi () << endl
       << "    # of constituents: " << mcparts.size() << endl;
  cout << "    constituents:" << endl;
  for (unsigned i = 0; i < mcparts.size (); i++) {
    const GenParticleCandidate* mcpart = mcparts[i];
    cout << "      #" << i << "  PDG code:" << mcpart->pdgId() 
	 << ", p/pt/eta/phi: " << mcpart->p() << '/' << mcpart->pt() 
	 << '/' << mcpart->eta() << '/' << mcpart->phi() << endl;	
  }    
}

