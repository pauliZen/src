//Using in root command line
//KS-test for D
UInt_t ks_D(string treename="Dtree")
{
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  UInt_t num=t->GetEntries();
  Double_t *D=new Double_t[num];
  Double_t d,p,teststat;
  t->SetBranchAddress("D",&d);
  for (int i=0;i<num;i++)
  {
    t->GetEntry(i);
    D[i]=d;
  }
  ROOT::Math::GoFTest *tt=new ROOT::Math::GoFTest(num,D,ROOT::Math::GoFTest::kGaussian);
  tt->KolmogorovSmirnovTest(p,teststat);
  cout<<"p-value:"<<p<<", teststat:"<<teststat<<endl;
  return num;
}

//ks-test for Gaussian Random samples
void test(Int_t num)
{
  Double_t *d=new Double_t[num];
  Double_t p,t;
  TRandom3 r;
  for (int i=0;i<num;i++)
    d[i]=r.Gaus();
  ROOT::Math::GoFTest *tt=new ROOT::Math::GoFTest(num,d,ROOT::Math::GoFTest::kGaussian);
  tt->KolmogorovSmirnovTest(p,t);
  cout<<"p:"<<p<<",t:"<<t<<endl;
}

//calculate D
Int_t calc_D(string datatree, Double_t m, string treename="DTree", string select="Dm_err>0")
{
  TTree *t=(TTree*)gDirectory->Get(datatree.c_str());
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  Double_t d,de,yy,mm;
  t->SetBranchAddress("Dm",&d);
  t->SetBranchAddress("Dm_err",&de);
  t->SetBranchAddress("yyyy",&yy);
  t->SetBranchAddress("mm",&mm);
  Double_t mean=0;
  Double_t sigma=0;
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    mean +=d;
    //    sigma +=de*de;
  }
  mean /=num;
  //  sigma =sqrt(sigma)/num;
  TTree *t1=new TTree(treename.c_str(),("Calculated D ("+select+")").c_str());
  Double_t Dd,date,dm,dmerr;
  t1->Branch("D",&Dd);
  t1->Branch("date",&date);
  t1->Branch("Dm",&dm);
  t1->Branch("Dm_err",&dmerr);
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    Dd=(d-m)/de;
    date=yy+mm/12.0;
    dm=d;
    dmerr=de;
    sigma +=pow((d-m),2);
    t1->Fill();
  }
  sigma =sqrt(sigma)/num;
  cout<<"mean:"<<mean<<",sigma"<<sigma<<endl;
  t1->Write("",TObject::kOverwrite);
  return num;
}

//draw histogram of CDF
Int_t cdf_hist(TH1F *h1,string cdfname="CDF",string gausscdfname="GaussCDF",double sigma=1)
{
  Int_t num=h1->GetNbinsX();
  Double_t bmax=h1->GetXaxis()->GetXmax();
  Double_t bmin=h1->GetXaxis()->GetXmin();
  Double_t cm=0;
  TH1F *h2=new TH1F(cdfname.c_str(),"Cumulative distributions of |D|",num,bmin,bmax);
  for (int i=1;i<=num;i++)
  {
    cm +=h1->GetBinContent(i);
    h2->SetBinContent(i,cm);
  }
  TH1F *h3=new TH1F(gausscdfname.c_str(),"CDF of Gauss distribution",num*100,bmin,bmax);
  Double_t binw=h3->GetBinWidth(1);
  for (int i=1;i<=num*100;i++)
    h3->SetBinContent(i,(ROOT::Math::gaussian_cdf((i-0.5)*binw,sigma)-0.5)*2);
  h2->Scale(1/cm);
  h2->SetLineColor(kBlue);
  h2->SetXTitle("|D|");
  h2->SetYTitle("Fraction<|D|");
  h3->SetLineColor(kBlack);
  h2->Write("",TObject::kOverwrite);
  h3->Write("",TObject::kOverwrite);
  return num;
}

//draw multi-histogram
void drawcdf(TCanvas *c2,string cdf1name="CDF2001",string cdf12name="CDF2001_2",string cdf2name="CDF2005",string gcdfname="GaussCDF")
{
  c2->cd();
  TH1F *cdf1=(TH1F*)gDirectory->Get(cdf1name.c_str());
  TH1F *cdf12=(TH1F*)gDirectory->Get(cdf12name.c_str());
  TH1F *cdf2=(TH1F*)gDirectory->Get(cdf2name.c_str());
  TH1F *gcdf=(TH1F*)gDirectory->Get(gcdfname.c_str());
  cdf1->Draw();
  cdf2->SetLineColor(kGreen);
  cdf12->SetLineColor(kRed);
  cdf2->Draw("same");
  cdf12->Draw("same");
  gcdf->Draw("same");
  TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
  tl->SetFillStyle(0);
  tl->AddEntry(cdf1,"Observations (>=2001)(Freedman et al. 2001)");
  tl->AddEntry(cdf12,"Observations (2001-2005)(Freedman et al. 2001)");
  tl->AddEntry(cdf2,"Observations (>=2005)(McConnachie et al. 2005)");
  tl->AddEntry(gcdf,"Gauss CDF");
  tl->Draw();
}

//select m31dist
Int_t selm31 (string treename, Double_t yy[], Double_t mm[], Double_t dm[], Double_t dmerr[],Double_t date[],string select="")
{
  Double_t d,dr,y,m;
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->SetBranchAddress("Dm",&d);
  t->SetBranchAddress("Dm_err",&dr);
  t->SetBranchAddress("yyyy",&y);
  t->SetBranchAddress("mm",&m);
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    yy[i]=y;
    mm[i]=m;
    dm[i]=d;
    date[i]=y+m/12.0;
    dmerr[i]=dr;
  }
  return num;
}

//select Ddata
Int_t selmD (string treename, Double_t date[], Double_t D[], Double_t dm[], Double_t dmerr[],string select="")
{
  Double_t d,de,Dd,dat;
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->SetBranchAddress("Dm",&d);
  t->SetBranchAddress("Dm_err",&de);
  t->SetBranchAddress("date",&dat);
  t->SetBranchAddress("D",&Dd);
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    date[i]=dat;
    dm[i]=d;
    dmerr[i]=de;
    D[i]=Dd;
  }
  return num;
}

//Derivation test
Int_t dcalc(Double_t mean,string treename="m31dist",string select="")
{
  Double_t d,dr,y,m;
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->SetBranchAddress("Dm",&d);
  t->SetBranchAddress("Dm_err",&dr);
  t->SetBranchAddress("yyyy",&y);
  t->SetBranchAddress("mm",&m);
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  Double_t mm=0;
  Double_t sigma=0;
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    mm +=d;
    sigma +=pow((d-mean)/dr,2);
  }
  mm /=num;
  sigma =sqrt(sigma)/num;
  cout<<"Mean:"<<mm<<",sigma:"<<sigma<<endl;
  return num;
}

//Mean calculation
Int_t meanc (string treename="m31distreg",string ntree="mdata")
{
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  Double_t m[16]={0};
  Double_t err[16]={0};
  Double_t sigma[16]={0};
  Int_t cm[16]={0};
  Double_t d,dr;
  Int_t s;
  t->SetBranchAddress("Dm",&d);
  t->SetBranchAddress("Dm_err",&dr);
  t->SetBranchAddress("style",&s);
  t->Draw(">>indexlist","Dm_err>0","entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    m[s-2] +=d;
    err[s-2] +=dr*dr;
    cm[s-2]++;
  }
  for (int i=0;i<16;i++)
    if (cm[i]==0) {cout<<i<<" no data"<<endl;}
    else
    {
      m[i] /=cm[i];
      err[i] =sqrt(err[i])/cm[i];
    }
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    sigma[s-2] +=pow((d-m[s-2])/dr,2);
  }
  for (int i=0;i<16;i++)
    if (cm[i]==0) {cout<<i<<" no data"<<endl;}
    else
    {
      sigma[i]=sqrt(sigma[i])/cm[i];
    }
  TTree *nt=new TTree(ntree.c_str(),"Mean data of different methods");
  Double_t mm,ms,merr,sl;
  nt->Branch("m",&mm);
  nt->Branch("err",&merr);
  nt->Branch("sigma",&ms);
  nt->Branch("style",&sl);
  for (int i=0;i<16;i++)
  {
    mm=m[i];
    merr=err[i];
    ms=sigma[i];
    sl=i+2;
    if (m[i]!=0)
      nt->Fill();
  }
  nt->Write("",TObject::kOverwrite);
  return num;
}

// draw dm vs date graph
void dgraph(string select="yyyy>1990")
{
  Double_t yy[163],mm[163],dm[163],t[163],date[163];
  selm31("m31dist",yy,mm,dm,t,date,("Dm_err>0&&"+select).c_str());
  TGraphErrors *g1=new TGraphErrors(105,date,dm,0,t);
  g1->GetYaxis()->SetTitle("Dm(mag)");
  g1->GetXaxis()->SetTitle("Date");
  g1->SetTitle("Distance modulus vs. date");
  g1->Draw("A*");
  Double_t mu1[2]={24.38,24.38};
  Double_t mu2[2]={24.47,24.47};
  Double_t tt[2]={1990,2012};
  TGraph *g2=new TGraph(2,tt,mu1);
  TGraph *g3=new TGraph(2,tt,mu2);
  g2->SetLineColor(kBlue);
  g3->SetLineColor(kGreen);
  g2->Draw("L");
  g3->Draw("L");
  TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
  tl->SetFillStyle(0);
  tl->AddEntry(g1,"Observation value");
  tl->AddEntry(g2,"Freedman et al. 2001 (24.38mag)");
  tl->AddEntry(g3,"McConnachie et al. 2005 (24.47mag)");
  tl->Draw();
}

//draw mean dm
Int_t dmg(TCanvas *c1,string treename="mdata",string select="")
{
  Double_t m[16],s[16],err[16],ds[16];
  Double_t mm,merr,mds,ms;
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->SetBranchAddress("m",&mm);
  t->SetBranchAddress("err",&merr);
  t->SetBranchAddress("sigma",&mds);
  t->SetBranchAddress("style",&ms);
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    m[i]=mm;
    s[i]=ms;
    err[i]=merr;
    ds[i]=mds;
  }
  c1->cd();
  TGraphErrors *g1=new TGraphErrors(num,s,m,err,ds);
  g1->GetYaxis()->SetTitle("Mean Dm(mag)");
  g1->GetXaxis()->SetTitle("Methods");
  g1->SetTitle("Mean distance modulus of different methods");
  g1->Draw("A*");
  return num;
}

//calculate mean of different methods
Int_t cmm(string treename="mdata",string select="m>23")
{
  Double_t m[16],s[16],err[16],ds[16];
  Double_t mm,merr,mds,ms;
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->SetBranchAddress("m",&mm);
  t->SetBranchAddress("err",&merr);
  t->SetBranchAddress("sigma",&mds);
  t->SetBranchAddress("style",&ms);
  t->Draw(">>indexlist",select.c_str(),"entrylist");
  TEntryList *indexl=(TEntryList*)gDirectory->Get("indexlist");
  Int_t num=indexl->GetN();
  Double_t mmm=0;
  Double_t msigma=0;
  Double_t md=0;
  for (int i=0;i<num;i++)
  {
    Int_t entryi=indexl->GetEntry(i);
    t->GetEntry(entryi);
    m[i]=mm;
    mmm +=mm;
    s[i]=ms;
    err[i]=merr;
    ds[i]=mds;
  }
  mmm /=num;
  for (int i=0;i<num;i++)
  {
    msigma +=pow((m[i]-mmm),2);
  }
  msigma = sqrt(msigma)/num;
  cout<<"mean:"<<mmm<<", sigma:"<<msigma<<endl;
  return num;
}
