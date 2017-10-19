// -*- C++ -*-
//
// Package:    QuantumEntanglementInPP/QuantumEntanglementInPP
// Class:      QuantumEntanglementInPP
// 
/**\class QuantumEntanglementInPP QuantumEntanglementInPP.cc QuantumEntanglementInPP/QuantumEntanglementInPP/plugins/QuantumEntanglementInPP.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Zhoudunming Tu
//         Created:  Thu, 19 Oct 2017 18:55:58 GMT
//
//

#include "QuantumEntanglementInPP/QuantumEntanglementInPP/interface/QuantumEntanglementInPPBase.h"


//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
QuantumEntanglementInPP::QuantumEntanglementInPP(const edm::ParameterSet& iConfig)

{
  trackName_  =  iConfig.getParameter<edm::InputTag>("trackName");
  vertexName_ =  iConfig.getParameter<edm::InputTag>("vertexName");
  towerName_ =  iConfig.getParameter<edm::InputTag>("towerName");

  trackSrc_ = consumes<reco::TrackCollection>(trackName_);
  vertexSrc_ = consumes<reco::VertexCollection>(vertexName_);
  towerSrc_ = consumes<CaloTowerCollection>(towerName_);

  Nmin_ = iConfig.getUntrackedParameter<int>("Nmin");
  Nmax_ = iConfig.getUntrackedParameter<int>("Nmax");

  doEffCorrection_ = iConfig.getUntrackedParameter<bool>("doEffCorrection");
  useEtaGap_ = iConfig.getUntrackedParameter<bool>("useEtaGap");
  doGenParticle_ = iConfig.getUntrackedParameter<bool>("doGenParticle");


  eff_ = iConfig.getUntrackedParameter<int>("eff");

  vzLow_ = iConfig.getUntrackedParameter<double>("vzLow");
  vzHigh_ = iConfig.getUntrackedParameter<double>("vzHigh");
  
  ptLow_ = iConfig.getUntrackedParameter<double>("ptLow");
  ptHigh_ = iConfig.getUntrackedParameter<double>("ptHigh");

  offlineptErr_ = iConfig.getUntrackedParameter<double>("offlineptErr", 0.0);
  offlineDCA_ = iConfig.getUntrackedParameter<double>("offlineDCA", 0.0);
  offlineChi2_ = iConfig.getUntrackedParameter<double>("offlineChi2", 0.0);
  offlinenhits_ = iConfig.getUntrackedParameter<double>("offlinenhits", 0.0);

  etaBins_ = iConfig.getUntrackedParameter<std::vector<double>>("etaBins");
  ptBins_ = iConfig.getUntrackedParameter<std::vector<double>>("ptBins");

}


QuantumEntanglementInPP::~QuantumEntanglementInPP()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
QuantumEntanglementInPP::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   if( doGenParticle_ ){
    edm::Handle<reco::GenParticleCollection> genParticleCollection;
    iEvent.getByToken(genSrc_, genParticleCollection);
    
    for(unsigned it=0; it<genParticleCollection->size(); ++it) {

      const reco::GenParticle & genCand = (*genParticleCollection)[it];
      int status = genCand.status();
      //double geneta = genCand.eta();
      int gencharge = genCand.charge();
      //double genrapidity = genCand.rapidity();
      double mass = genCand.mass();

      if( status != 1 || gencharge == 0 ) continue;

       cout << "mass " << mass << endl;
    }
  }

}


// ------------ method called once each job just before starting event loop  ------------
void 
QuantumEntanglementInPP::beginJob()
{
  edm::Service<TFileService> fs;
    
  TH1D::SetDefaultSumw2();

  const int NetaBins = etaBins_.size() - 1 ;

  double ptBinsArray[100];
  const int Nptbins = ptBins_.size() - 1;
  for(unsigned i = 0; i < ptBins_.size(); i++){
    ptBinsArray[i] = ptBins_[i];
  }

  // edm::FileInPath fip1("QuantumEntanglementInPP/QuantumEntanglementInPP/data/Hydjet_eff_mult_v1.root");
  // TFile f1(fip1.fullPath().c_str(),"READ");
  // for(int i = 0; i < 5; i++){
  //    effTable[i] = (TH2D*)f1.Get(Form("rTotalEff3D_%d",i));
  // }

  Ntrk = fs->make<TH1D>("Ntrk",";Ntrk",5000,0,5000);
  vtxZ = fs->make<TH1D>("vtxZ",";vz", 400,-20,20);
  cbinHist = fs->make<TH1D>("cbinHist",";cbin",200,0,200);
  trkPhi = fs->make<TH1D>("trkPhi", ";#phi", 700, -3.5, 3.5);
  hfPhi = fs->make<TH1D>("hfPhi", ";#phi", 700, -3.5, 3.5);
  trkPt = fs->make<TH1D>("trkPt", ";p_{T}(GeV)", Nptbins,ptBinsArray);
  trk_eta = fs->make<TH1D>("trk_eta", ";#eta", 50,-2.5,2.5);

}
TComplex 
QuantumEntanglementInPP::q_vector(double n, double p, double w, double phi) 
{
  double term1 = pow(w,p);
  TComplex e(1, n*phi, 1);
  return term1*e;
}
// ------------ method called once each job just after ending the event loop  ------------
void 
QuantumEntanglementInPP::endJob() 
{
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
QuantumEntanglementInPP::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(QuantumEntanglementInPP);
