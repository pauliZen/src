//Draw chi c1 c2====================================//
void drawchi(TCanvas *c1,string select="r==1",string xname="c1",string yname="chi")
{
  TTree *t=(TTree*)gDirectory->Get("chi2");
  Int_t tnum=t->Draw((yname+":"+xname).c_str(),select.c_str());
  Double_t *chi=t->GetV1();
  Double_t *xc=t->GetV2();
  TGraph *g1=new TGraph(tnum,xc,chi);
  c1->cd();
  g1->SetTitle(("Chi square vs. "+xname).c_str());
  g1->GetXaxis()->SetTitle(xname.c_str());
  g1->GetYaxis()->SetTitle("Chi^2");
  g1->Draw("A*L");
}

//Draw V P relation=================================//
void drawVP(Int_t drawnum=1)
{
  TCanvas *c2=new TCanvas;
  TTree *tn=(TTree*)gDirectory->Get("data");
  Int_t tnum=tn->Draw("V:log10(P)","P>0");
  Double_t *v=tn->GetV1();
  Double_t *p=tn->GetV2();
  TGraph* g1=new TGraph(tnum,p,v);
  c2->cd();
  g1->SetTitle("V magnitude vs. Log(P)");
  g1->GetXaxis()->SetTitle("Log(P)");
  g1->GetYaxis()->SetTitle("V");
  g1->Draw("A*");
  TF1 *f1=new TF1("polf1","x*[1]+[0]",p[0],p[tnum-1]);
  TF1 *f2=new TF1("polf2","x*x*[2]+x*[1]+[0]",p[0],p[tnum-1]);
  TFitResultPtr p1=g1->Fit("polf1","S");
  TFitResultPtr p2=g1->Fit("polf2","S+");
  p1->Write("VPpol1",6);
  p2->Write("VPpol2",6);
  Double_t *par2=p1->GetParams();
  Double_t *par3=p2->GetParams();
  Double_t *dv1=new Double_t[tnum];
  Double_t *dv2=new Double_t[tnum];
  Double_t *ddv=new Double_t[tnum];
  for (int i=0;i<tnum;i++)
  {
    dv1[i]=v[i]-f1->Eval(p[i]);
    dv2[i]=v[i]-f2->Eval(p[i]);
    ddv[i]=dv2[i]-dv1[i];
  }
  TGraph *g2=new TGraph(tnum,p,dv1);
  TGraph *g3=new TGraph(tnum,p,dv2);
  TGraph *gd=new TGraph(tnum,p,ddv);
  TMultiGraph* gm=new TMultiGraph();
  g2->GetXaxis()->SetTitle("Log(P)");
  g2->GetYaxis()->SetTitle("Residuals");
  g3->GetXaxis()->SetTitle("Log(P)");
  g3->GetYaxis()->SetTitle("Residuals");
  g2->SetTitle("Residuals of v to Pol 1 fitting vs. Log(P)");
  g3->SetTitle("Residuals of v to Pol 2 fitting vs. Log(P)");
  gd->GetXaxis()->SetTitle("Log(P)");
  gd->GetYaxis()->SetTitle("Fitting difference");
  gd->SetTitle("Evaluated V of Pol 2 minus Pol 1 vs. Log(P)");
  g2->SetFillColor(kRed-5);
  g3->SetFillColor(kBlue-5);
  g2->SetMarkerColor(kRed);
  g2->SetMarkerStyle(2);
  g2->SetMarkerSize(0.5);
  g3->SetMarkerColor(kBlue);
  g3->SetMarkerStyle(2);
  g3->SetMarkerSize(0.5);
  gm->Add(g2);
  gm->Add(g3);
  gm->SetTitle("Residuals of v to fitting vs. Log(P)");
  TLegend *tle=new TLegend(0.57,0.75,0.9,0.9);
  tle->AddEntry(g2,"Pol 1 fitting");
  tle->AddEntry(g3,"Pol 2 fitting");
  tle->SetFillStyle(0);
  if (drawnum==2)
  {
    c2->Clear();
    c2->Divide(1,2);
    c2->cd(1);
    g2->Draw("AB");
    g2->Draw("P");
    c2->cd(2);
    g3->Draw("AB");
    g3->Draw("P");
  }
  if (drawnum==3)
  {
    c2->Clear();
    gm->Draw("AB");
    gm->Draw("P");
    tle->Draw();
  }
  if (drawnum==4)
  {
    c2->Clear();
    gd->Draw("AP");
  }
}
