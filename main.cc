#include <TChain.h>
#include <TTree.h>
#include <string>
#include <vector>

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual float GetMvaValue( std::vector<float>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#include "./MLP.C"

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

  TChain* kette = new TChain("TestTree");
  kette->Add("TMVA.root");

  kette->SetBranchStatus("*",0);
  for (unsigned u = 0u ; u < vars.size() ; ++u) {
    kette->SetBranchAddress(vars[u].c_str(), &(fvars[u]));
    kette->SetBranchStatus(vars[u].c_str(),1);
  }

  IClassifierReader* classifier = new ReadMLP(vars);

  for (unsigned u = 0u ; u < kette->GetEntriesFast() ; ++u) {
    kette->GetEntry(u);
    classifier->GetMvaValue( fvars );
  }
  return 0;
}
