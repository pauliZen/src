//Drawgraph function================================//

Int_t drawgraph(string treename, TCanvas *c1, string xname="x", string yname="y",TCut listcondition="",string drawoption="*AC",string vartype="DD",bool printgraph=0,string graphname="graph")//bool closeTCanvas)
{
  Double_t varxD;
  Double_t varyD;
  Int_t varxI;
  Int_t varyI;
  Float_t varxF;
  Float_t varyF;
  TTree *treenow=(TTree*)(gDirectory->Get(treename.c_str()));
  if (vartype[0]=="I")
    treenow->SetBranchAddress(xname.c_str(),&varxI);
  else if (vartype[0]=="F")
    treenow->SetBranchAddress(xname.c_str(),&varxF);
  else
    treenow->SetBranchAddress(xname.c_str(),&varxD);
  if (vartype[1]=="I")
    treenow->SetBranchAddress(yname.c_str(),&varyI);
  else if (vartype[1]=="F")
    treenow->SetBranchAddress(yname.c_str(),&varyF);
  else
    treenow->SetBranchAddress(yname.c_str(),&varyD);
  treenow->Draw(">>graphlist",listcondition,"entrylist");
  Int_t entrynum=graphlist->GetN();
  Double_t *xlist= new Double_t[entrynum];
  Double_t *ylist= new Double_t[entrynum];
  for (Int_t i=0;i<entrynum;i++)
  {
    Int_t entryi=graphlist->GetEntry(i);
    treenow->GetEntry(entryi);
    if (vartype[0]=="I")
    {
      xlist[i]=varxI;
      ylist[i]=varyI;
    }
    else if (vartype[0]=="F")
    {
      xlist[i]=varxF;
      ylist[i]=varyF;
    }
    else
    {
      xlist[i]=varxD;
      ylist[i]=varyD;
    }
  }
  //  c1->SetCanvasSize(600,400);
  c1->cd();
  TGraph *g1= new TGraph(entrynum,xlist,ylist);
  g1->GetXaxis()->SetTitle(xname.c_str());
  g1->GetYaxis()->SetTitle(yname.c_str());
  g1->SetLineColor(4);
  g1->SetTitle((yname+" vs. "+xname+" ("+listcondition+")").c_str());
  g1->Draw(drawoption.c_str());
  c1->Update();
  if (printgraph)
    c1->Print((graphname+".eps").c_str());
  graphlist->Delete();
  //  treenow->Delete();
  return entrynum;
}
