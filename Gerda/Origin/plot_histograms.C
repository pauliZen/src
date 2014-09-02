void plot_histograms()
{
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   gROOT->LoadMacro("./get_th1f.C");

   TH1F* hecore;
   TH1F* hecores;
   TH1F* hecore_first;
   TH1F* hecore_second;
   TH1F* hecore_seconds;
   TH1F* hecore_secondt;
   TH1F* hecore_secondts;

   TFile* finput = new TFile("../../data/histograms/h.sii.ln2o.root");
   //TFile* finput = new TFile("histograms/h.susie.k1.root");
   //TFile* finput = new TFile("histograms/h.si.k1.root");
   //TFile* finput = new TFile("histograms/h.siii.g2.root");
   //   TFile* finput = new TFile("histograms/h.siii.feb2010.root");
   finput->cd();
   hecore = (TH1F*) get_th1f("hecore")->Clone();
   hecores = (TH1F*) get_th1f("hecores")->Clone();
   hecore_first = (TH1F*) get_th1f("hecore_first")->Clone();
   hecore_second = (TH1F*) get_th1f("hecore_second")->Clone();
   hecore_seconds = (TH1F*) get_th1f("hecore_seconds")->Clone();
   hecore_secondt = (TH1F*) get_th1f("hecore_secondt")->Clone();
   hecore_secondts = (TH1F*) get_th1f("hecore_secondts")->Clone();
//   hecore->Rebin(10);

   hecore->Rebin(10);
   hecores->Rebin(10);

   hecore_first->Rebin(100);
   hecore_second->Rebin(100);
   hecore_seconds->Rebin(100);
   hecore_secondt->Rebin(100);
   hecore_secondts->Rebin(100);

   TCanvas* c1 = new TCanvas("c1","c1",10,10,900,600);
   c1->cd(); gPad->SetLogy();
   hecore->GetXaxis()->SetTitle("Ecore [keV]");
   hecore->GetYaxis()->SetTitle("Entries/10keV");
   hecore->Draw();
   hecores->SetLineColor(kRed);
   //hecores->SetFillColor(kRed);
   hecores->Draw("same");
   TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
   lone->SetFillStyle(0);
   lone->AddEntry(hecore,"all events", "l");
   lone->AddEntry(hecores,"single-segment events", "l");
   lone->Draw();
   c1->Update();
   c1->Print("../../data/plots/siio/ecore_ss.eps");


   TCanvas* c2 = new TCanvas("c2","c2",10,10,900,600);
   c2->cd();
   hecore_first->Draw();
   c2->Update();

   TCanvas* c3 = new TCanvas("c3","c3",10,10,900,600);
   c3->cd(); gPad->SetLogy();
   hecore_second->SetTitle("second event");
   hecore_second->GetXaxis()->SetTitle("Ecore [keV]");
   hecore_second->GetYaxis()->SetTitle("Entries/100keV");
   hecore_second->SetLineWidth(2);
   hecore_second->SetMinimum(0.1);
   hecore_second->Draw();
   //hecore_seconds->SetLineColor(kRed);
   //hecore_seconds->SetFillColor(kRed);
   //hecore_seconds->Draw("same");
   hecore_secondt->SetLineColor(kBlue);
   hecore_secondt->SetLineWidth(2);
   hecore_secondt->Draw("same");
   hecore_secondts->SetLineColor(kRed);
   hecore_secondts->SetLineWidth(2);
   hecore_secondts->Draw("same");
   TLegend* ltwo = new TLegend(0.4,0.5,0.85,0.75);
   ltwo->SetFillStyle(0);
   ltwo->AddEntry(hecore_second,"Bi214 consecutive events","l");
   ltwo->AddEntry(hecore_secondt,"5x164 #mus time window","l");
   ltwo->AddEntry(hecore_secondts,"5x164 #mus and single-segment","l");
   ltwo->Draw();
   c3->Update();
   c3->Print("../../data/plots/siio/ecore_bi214.eps");

}

