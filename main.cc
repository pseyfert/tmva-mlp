#include <TChain.h>
#include <TTree.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <string>
#include <vector>

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual float GetMvaValue( std::vector<float>& inputValues ) = 0;

};

#include "./MLP.C"
#include "./oldMLP.C"

int main() {

  std::vector<std::string> vars;
  std::vector<Float_t> fvars;
  vars.push_back("tracks_OldImplementation_obsVELO");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_FitVeloChi2");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_FitVeloNDoF");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_obsTT");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_TToutlier");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_obsIT");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_obsOT");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_IToutlier");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_OTunused");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_FitTChi2");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_FitTNDoF");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_veloHits");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_ttHits");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_itHits");
  fvars.push_back(0.f);
  vars.push_back("tracks_OldImplementation_otHits");
  fvars.push_back(0.f);
  vars.push_back("tracks_PT");
  fvars.push_back(0.f);
  vars.push_back("tracks_TRACK_CHI2");
  fvars.push_back(0.f);
  vars.push_back("tracks_TRACK_NDOF");
  fvars.push_back(0.f);
  vars.push_back("tracks_TRACK_CHI2NDOF");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_NCandCommonHits");
  fvars.push_back(0.f);
  vars.push_back("tracks_TrackExtraInfo_FitMatchChi2");
  fvars.push_back(0.f);
  fvars.push_back(2.f);
  fvars.push_back(1.f);
  fvars.push_back(1.f);

  TChain* kette = new TChain("TestTree");
  kette->Add("TMVA.root");

  kette->SetBranchStatus("*",0);
  for (unsigned u = 0u ; u < vars.size() ; ++u) {
    kette->SetBranchAddress(vars[u].c_str(), &(fvars[u]));
    kette->SetBranchStatus(vars[u].c_str(),1);
  }

  IClassifierReader* classifier = new ReadMLP(vars);
  IClassifierReader* oldclassifier = new ReadoldMLP(vars);

  TH2F* h = new TH2F("h","h",200,-1,1,200,-1,1);
  for (unsigned u = 0u ; u < kette->GetEntriesFast() ; ++u) {
    for (unsigned k = 0u; k < 1 ; ++k) {
      fvars[21]=1.f;
      fvars[22]=0.f;
      fvars[23]=0.f;
      kette->GetEntry(u);
      float o = oldclassifier->GetMvaValue(fvars);
      fvars[21]=2.f;
      fvars[22]=1.f;
      fvars[23]=1.f;
      kette->GetEntry(u);
      float n = classifier->GetMvaValue(fvars);

      h->Fill(o,n);
    }
  }
  TCanvas* c = new TCanvas();
  h->Draw("colz");
  c->Print("hist.eps");
  return 0;
}
