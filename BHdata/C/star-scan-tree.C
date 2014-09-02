// scan one tree in one root filename, and store ===//
// in vselect-index.log=============================//
// Problem: need to enter CR if scanned number is ==//
// larger than 25===================================//

{
  string filename;
  cout<<"Input star root filename:";
  cin>>filename;
  TFile f(filename.c_str(),"update");
  cout<<"Input Tree name to select v:";
  string treename;
  cin>>treename;
  TTree *ptree=(TTree*)(f.Get(treename.c_str()));
  string cuti;
  cout<<"Input cut:";
  cin>>cuti;
  TCut cut1=cuti.c_str();
  cout<<"Input scan format:";
  string scanfm;
  cin>>scanfm;
  ptree->Scan(scanfm.c_str(),cut1); >vselect-index.log;
}

