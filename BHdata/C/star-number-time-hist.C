// draw histogram of number vs. time for v>2 of stars==//
// save NThist(TH1D) in *-result.root==================//

{
  //Define pars=======================================//
  string filename;
  string histname;
  string histtitle;
  string vcut;
  string outname;
  int totnum;

  //input=============================================//
  cout<<"Input root file to make v distribution:(run-020-020-1mil)";
  cin>>filename;
  //  cout<<"Input histogram name:";
  //  cin>>histname;
  //  cout<<"Input histogram title:";
  //  cin>>histtitle;
  cout<<"Input scan dat range end:";
  cin>>totnum;
  //  cout<<"Input scan condition:";
  //  cin>>vcut;
  //  cout<<"Input new root file for result:";
  //  cin>>outname;
  outname=filename+"-result.root";
  filename=filename+"-star.root";
  histname="NThist";
  histtitle="Number vs. Time for v>2";

  //analysis==========================================//
  TFile f(filename.c_str(),"update");
  TH1D *h1=new TH1D(histname.c_str(),histtitle.c_str(),totnum,0,totnum);
  TCut cut1=vcut.c_str();
  for (int i=0;i<=totnum;i++)
  {
    string treename="P";
    string order;
    stringstream sstr;
    Int_t numv=0;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    sstr>>order;
    if (i<10)
      treename="P000";
    if (i>=10&&i<100)
      treename="P00";
    if (i>=100&&i<1000)
      treename="P0";
    if (i>=1000&&i<10000)
      treename="P";
    treename=treename+order;
    cout<<"now "<<treename<<endl;
    TTree *tree1=(TTree*)(f.Get(treename.c_str()));
    //    tree1.SetScanfield(0);
    numv=tree1.GetEntries();
    Double_t vi;
    tree1->SetBranchAddress("v",&vi);
    for (int j=0;j<numv;j++)
    {
      tree1->GetEntry(j);
      if (vi>2)
        h1.Fill(i);
    }
  }
  TFile* out=new TFile(outname.c_str(),"update");
  h1->SetYTitle("Number");
  h1->SetXTitle("Time_cur");
  h1->Write("",TObject::kOverwrite);
  out->Close();
}
