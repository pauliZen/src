// draw delta E of eject stars (bh) vs. time_eject=======//
// should open root file first===========================//
//subroutine: drawstardE: draw ejects stars deltaE-time_eject===========//
//              command:[prog.] [treename] [savefile] [drawoption]======//
//            drawbhdE: draw bh -deltaE-time_eject======================//
//              command:[prog.] [treename] [bhmass1] [bhmass2]==========//
//                      [savefile] [drawoption]=========================//
//            drawtotdE: draw star bh and tot deltaE-time ==============//
//              command:[prog.] [star] [bh] [savefile] [drawoption]=====//
//Input:      savefile: save TH1D root name=============================//
//            star: TH1D name of star===================================//
//            bh: TH1D name of bh=======================================//

Int_t drawstarEt (TFile *savefile,string dEvsTstarhist="dEvsTstar",string newhistname="EvsTstar",string drawoption="")
{
  TH1D *starde=(TH1D*)gDirectory->Get(dEvsTstarhist.c_str());
  Int_t bins=starde->GetNbinsX();
  Double_t xmin=starde->GetXaxis()->GetXmin();
  Double_t xmax=starde->GetXaxis()->GetXmax();
  Double_t sum=0;
  TH1D *stare=new TH1D(newhistname.c_str(),"total energy of eject stars vs. time",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=1;i<=bins;i++)
  {
    sum +=starde->GetBinContent(i);
    stare->SetBinContent(i,sum);
  }
  stare->SetXTitle("time");
  stare->SetYTitle("total energy");
  stare->Draw(drawoption.c_str());
  savefile->cd();
  stare->Write("",TObject::kOverwrite);
  return sum;
}  

Int_t drawstardE (TFile *savefile,string treename="destars",string histname="dEvsTstar",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  Double_t teject[3],deltaE[2];
  TTree *ftree=(TTree*)gDirectory->Get(treename.c_str());
  ftree->SetBranchAddress("t",teject);
  ftree->SetBranchAddress("En",deltaE);
  Int_t totnum=ftree->GetEntries();
  TH1D *starde=new TH1D(histname.c_str(),"Delta E of eject stars vs. time_eject",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    starde->Fill(teject[1]-1,deltaE[1]);
  }
  starde->SetXTitle("time");
  starde->SetYTitle("energy change");
  starde->Draw(drawoption.c_str());
  savefile->cd();
  starde->Write("",TObject::kOverwrite);
  return totnum;
}

Int_t drawstardEqueue (TFile *savefile,string rootname="run-020-020-1mil-result-dEt-",Int_t filenumber=10,string treename="destars",string histname="dEvsTstar",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  Double_t teject[3],deltaE[2];
  stringstream sstr;
  TChain *ftree=new TChain(treename.c_str());
  for (int i=0;i<filenumber;i++)
  {
    string index;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    sstr>>index;
    ftree->AddFile((rootname+index+".root").c_str());
  }
  ftree->SetBranchAddress("t",teject);
  ftree->SetBranchAddress("En",deltaE);
  Int_t totnum=ftree->GetEntries();
  TH1D *starde=new TH1D(histname.c_str(),"Delta E of eject stars vs. time_eject",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    starde->Fill(teject[1]-1,deltaE[1]);
  }
  starde->SetXTitle("time");
  starde->SetYTitle("energy change");
  starde->Draw(drawoption.c_str());
  savefile->cd();
  starde->Write("",TObject::kOverwrite);
  return totnum;
}

Int_t drawbhdE (TFile *savefile,Double_t bhmass1,Double_t bhmass2,string treename="BHpars",string histname="dEvsTbh",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  Double_t time,doa;
  TTree *ftree=(TTree*)gDirectory->Get(treename.c_str());
  ftree->SetBranchAddress("t",&time);
  ftree->SetBranchAddress("dover_a",&doa);
  Int_t totnum=ftree->GetEntries();
  TH1D *bhde=new TH1D(histname.c_str(),"Delta E of bh binary vs. time",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    bhde->Fill(time,doa*bhmass1*bhmass2/2);
  }
  bhde->SetXTitle("time");
  bhde->SetYTitle("energy change");
  bhde->Draw(drawoption.c_str());
  savefile->cd();
  bhde->Write("",TObject::kOverwrite);
}

Int_t drawbhEt (TFile *savefile,Double_t bhmass1,Double_t bhmass2,string treename="BHpars",string histname="EvsTbh",string drawoption="")
{
  Double_t time,overa;
  TTree *ftree=(TTree*)gDirectory->Get(treename.c_str());
  ftree->SetBranchAddress("t",&time);
  ftree->SetBranchAddress("over_a",&overa);
  Int_t bins=(ftree->GetEntries()-1);
  ftree->GetEntry(0);
  Double_t xmin=time;
  ftree->GetEntry(bins-1);
  Double_t xmax=time;
  ftree->GetEntry(1);
  Double_t tmp=time;
  bins=(xmax-xmin)/(tmp-xmin)+1;
  TH1D *bhe=new TH1D(histname.c_str(),"total energy of BHs vs. time", bins,xmin,xmax);
  for (Int_t i=0;i<bins;i++)
  {
    ftree->GetEntry(i);
    bhe->Fill(time,overa*bhmass1*bhmass2/2);
  }
  bhe->SetXTitle("time");
  bhe->SetYTitle("total energy");
  bhe->Draw(drawoption.c_str());
  savefile->cd();
  bhe->Write("",TObject::kOverwrite);
}

Int_t drawbhstarE (TFile *savefile, string bhhistname="EvsTbh",string starhistname="EvsTstar",string drawoption="")
{
  TH1D *star=(TH1D*)gDirectory->Get(starhistname.c_str());
  TH1D *comp=star->Clone();
  TH1D *bh=(TH1D*)gDirectory->Get(bhhistname.c_str());
  comp->SetTitle("Total energy vs. time");
  comp->GetYaxis()->SetTitleOffset(1.25);
  comp->SetLineColor(kRed);
  comp->SetName("Energy");
  comp->Draw();
  bh->SetLineColor(kBlack);
  bh->Draw("same");
  TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
  tl->SetFillStyle(0);
  tl->AddEntry(comp,"star total energy change");
  tl->AddEntry(bh,"BHs energy M_bh^2/(2a)");
  tl->Draw();
}

Int_t drawbhdEqueue (TFile *savefile,Double_t bhmass1,Double_t bhmass2,string treename,string rootname="run-020-020-1mil-result-dEt-",Int_t filenumber=7, string histname="dEvsTbh",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  Double_t time,doa;
  stringstream sstr;
  TChain *ftree=new TChain(treename.c_str());
  for (int i=0;i<filenumber;i++)
  {
    string index;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    sstr>>index;
    ftree->AddFile((rootname+index+".root").c_str());
  }
  ftree->SetBranchAddress("t",&time);
  ftree->SetBranchAddress("dover_a",&doa);
  Int_t totnum=ftree->GetEntries();
  TH1D *bhde=new TH1D(histname.c_str(),"Delta E of bh binary vs. time",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    bhde->Fill(time,doa*bhmass1*bhmass2);
  }
  bhde->SetXTitle("time");
  bhde->SetYTitle("energy change");
  bhde->Draw(drawoption.c_str());
  savefile->cd();
  bhde->Write("",TObject::kOverwrite);
}

Int_t drawtotdE (TFile *savefile,string star="dEvsTstar", string bh="dEvsTbh", string drawoption="")
{
  TH1D *s1=(TH1D*)gDirectory->Get(star.c_str());
  TH1D *b1=(TH1D*)gDirectory->Get(bh.c_str());
  Int_t snum=s1->GetNbinsX();
  Int_t bnum=b1->GetNbinsX();
  if (snum==bnum)
  {
    Double_t smin=s1->GetXaxis()->GetXmin();
    Double_t bmin=b1->GetXaxis()->GetXmin();
    if (smin==bmin)
    {
      Double_t smax=s1->GetXaxis()->GetXmax();
      Double_t bmax=b1->GetXaxis()->GetXmax();
      if (smax==bmax)
      {
        TH1D *t1=new TH1D("totdE","Delta E of total energy vs. time",snum,smin,smax);
        for (Int_t i=0;i<=snum;i++)
        {
          Double_t snow=s1->GetBinContent(i);
          Double_t bnow=b1->GetBinContent(i);
          Double_t tnow=-snow+bnow;
          t1->SetBinContent(i,tnow);
        }
        savefile->cd();
        t1->Write("",TObject::kOverwrite);
        TH1D *t3=b1->Clone();
        t3->SetTitle("Delta E vs. time");
        t3->GetYaxis()->SetTitleOffset(1.25);
        t3->SetLineColor(kBlack);
        t3->SetName("dE");
        t3->Draw();
        b1->SetLineColor(kBlack);
        b1->Draw("same");
        s1->SetLineColor(kRed);
        s1->Draw("same");
        t1->SetLineColor(kBlue);
        t1->Draw("same");
        t1->Draw("same");
        TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
        tl->SetFillStyle(0);
        tl->AddEntry(t1,"d(M_bh^2/(2a))-dE_stars");
        tl->AddEntry(b1,"BH energy change d(M_bh^2/(2a))");
        tl->AddEntry(s1,"eject stars total energy change dE_stars");
        tl->Draw();
      }
      else
        cout<<"smax NE bmax"<<endl;
    }
    else
      cout<<"smin NE bmin"<<endl;
  }
  else
    cout<<"snum NE bnum"<<endl;
  return snum;
}

