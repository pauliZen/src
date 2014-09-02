//draw star Energy, L vs. time in one canvas

Int_t draw(string index,TTree *t)
{
  TCanvas *c1 = new TCanvas("c1","different scales hists",600,400);
  gStyle->SetOptStat(kFALSE);
  Double_t etot,time_cur,Lalpha,Ldelta,Lr;
  t->SetBranchAddress("etot",&etot);
  t->SetBranchAddress("time_cur",&time_cur);
  t->SetBranchAddress("Lalpha",&Lalpha);
  t->SetBranchAddress("Ldelta",&Ldelta);
  t->SetBranchAddress("Lr",&Lr);
  t->Draw(">>tlist",("index=="+index).c_str(),"entrylist");
  TEntryList *tl=(TEntryList*)gDirectory->Get("tlist");
  Int_t entrynum=tl->GetN();
  Double_t *en=new Double_t[entrynum];
  Double_t *tn=new Double_t[entrynum];
  Double_t *Lrn=new Double_t[entrynum];
  Double_t *Lan=new Double_t[entrynum];
  Double_t *Ldn=new Double_t[entrynum];
  for (Int_t i=0;i<entrynum;i++)
  {
     Int_t entryi=tl->GetEntry(i);
     t->GetEntry(entryi);
     en[i]=etot*1E6;
     tn[i]=time_cur;
     Lrn[i]=Lr*3E6;
     Lan[i]=Lalpha;
     Ldn[i]=Ldelta;
  }
  //create E-t
  TGraph *h1=new TGraph(entrynum,tn,en);
  h1->SetTitle("Energy vs. time");
  h1->GetYaxis()->SetTitle("Energy");
  h1->GetXaxis()->SetTitle("time");
  //create Lalpha-t
  TGraph *h2=new TGraph(entrynum,tn,Lan);
  h2->SetTitle("L_alpha vs. time");
  h2->GetYaxis()->SetTitle("L_alpha");
  h2->GetXaxis()->SetTitle("time");
  //create Ldelta-t
  TGraph *h3=new TGraph(entrynum,tn,Ldn);
  h3->SetTitle("L_delta vs. time");
  h3->GetYaxis()->SetTitle("L_delta");
  h3->GetXaxis()->SetTitle("time");
  //create Lr-t
  TGraph *h4=new TGraph(entrynum,tn,Lrn);
  h4->SetTitle("L_r vs. time");
  h4->GetYaxis()->SetTitle("L_r");
  h4->GetXaxis()->SetTitle("time");
  
  //scale h2-4 to the pad coordinates
  // Float_t rightmax2 = 1.1*h2->GetMaximum();
  // Float_t scale2 = gPad->GetUymax()/rightmax2;
  // h2->Scale(scale2);

  h2->SetLineColor(kRed);
  h3->SetLineColor(kBlue);
  h4->SetLineColor(kGreen);

  TMultiGraph *ht=new TMultiGraph();
  ht->Add(h1);
  ht->Add(h2);
  ht->Add(h3);
  ht->Add(h4);
  ht->SetTitle(("Compare pars of star (index:"+index+") vs. time;time;Pars").c_str());
  ht->Draw("al");

  TLegend *tle=new TLegend(0.4,0.1,0.85,0.25);
  //  tle->SetFillStyle(0);
  tle->AddEntry(h1,"total energy (in 10^-6 unit)");
  tle->AddEntry(h2,"L_alpha (0-2 pi)");
  tle->AddEntry(h3,"L_delta (0-pi)");
  tle->AddEntry(h4,"L_r (in 1/3*10^-6 unit)");
  tle->Draw();
  
  // h2->Draw("Lsame");
  // h3->Draw("Lsame");
  // h4->Draw("Lsame");
  
  //draw an axis on the right side
  // TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(),
  //   		      gPad->GetUymax(),0,rightmax2,510,"+L");
  // axis2->SetLineColor(kRed);
  // axis2->SetLabelColor(kRed);

  // Float_t rightmax3 = 1.1*h3->GetMaximum();
  // Float_t scale3 = gPad->GetUymax()/rightmax3;
  return entrynum;
}
