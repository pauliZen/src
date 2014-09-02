void create_histograms()
{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Feb  3 10:46:00 2010 by ROOT version5.24/00)
//   from TTree PSTree/root
//   found on file: nbg489.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   gROOT->SetStyle("Plain");

   TChain* PSTree = new TChain("PSTree");

//---------------------------------------------
// Siegfried-II in liquid Nitrogen
//---------------------------------------------

   PSTree->AddFile("../../data/SII_ntuple/nbg484.root");
   PSTree->AddFile("../../data/SII_ntuple/nbg485.root");
   PSTree->AddFile("../../data/SII_ntuple/nbg486.root");
   PSTree->AddFile("../../data/SII_ntuple/nbg487.root");
   PSTree->AddFile("../../data/SII_ntuple/nbg488.root");
   PSTree->AddFile("../../data/SII_ntuple/nbg489.root");
   Char_t* output_histogram_filename="../../data/histograms/h.sii.ln2o.root";

//---------------------------------------------
// Siegfried-I in K-1, August  2006
//---------------------------------------------
/*
   PSTree->AddFile("/.hb/raidg01/Siegfried_I/Run_01/neutron/bkg/shrinked/neutron_bg_210806_1.root");
   PSTree->AddFile("/.hb/raidg01/Siegfried_I/Run_01/neutron/bkg/shrinked/neutron_bg_210806_2.root");
   PSTree->AddFile("/.hb/raidg01/Siegfried_I/Run_01/neutron/bkg/shrinked/neutron_bg_210806_3.root");
   Char_t* output_histogram_filename="histograms/h.si.k1.root";
*/
//-------------------------------
// S-III in G-III 2010
//-------------------------------
//   PSTree->AddFile("/.hb/raidg01/SiegfriedIII/Run_09/BiPo/shrinked/shrinked.root");
//   Char_t* output_histogram_filename="histograms/h.siii.g2.root";
//---------------------------------------------
// Supersiegfried in K-1 3-segment events
//---------------------------------------------

//---------------------------------------------
// SiPM data for checking DAQ dead time
//---------------------------------------------
/*
   PSTree->AddFile("/home/pclg-08/xliu/work/Gerda-Munich/pixie-convert/wrk/test.root");
   Char_t* output_histogram_filename="histograms/h.sipm.root";
*/    
//-------------------------------
// Bi214 energy lines
//-------------------------------
   const Int_t nbi=7;
   Float_t ebi[nbi]={609.312, 1120.287, 1377.669, 1729.595, 1764.494, 1847.420, 2204.21};
//-------------------------------
//Declaration of leaves types
//-------------------------------
   Int_t           Evt_Number;
   Int_t           nsegs;
   Float_t         eseg[20];
   Int_t           iseg[20];
   Float_t         tote;
   Float_t         tote_threshold;
   Float_t         ecore;
   Int_t           triggertime;
   Int_t           evt_timehigh;
   Int_t           evt_timelow;

//-------------------------------
// the first and the second event 
//-------------------------------
   Float_t  ecore_f;
   Int_t    nsegs_f;
   Float_t  eseg_f[20];
   Int_t    iseg_f[20];
   Int_t    triggertime_f;
   Int_t    evt_timehigh_f;
   Int_t    evt_timelow_f;
   Float_t  tote_f;

   Float_t  ecore_s;
   Int_t    nsegs_s;
   Float_t  eseg_s[20];
   Int_t    iseg_s[20];
   Int_t    triggertime_s;
   Int_t    evt_timehigh_s;
   Int_t    evt_timelow_s;
   Float_t  tote_s;

   // Set branch addresses.
   PSTree->SetBranchAddress("Evt_Number",&Evt_Number);
   PSTree->SetBranchAddress("nsegs",&nsegs);
   PSTree->SetBranchAddress("eseg",eseg);
   PSTree->SetBranchAddress("iseg",iseg);
   PSTree->SetBranchAddress("tote",&tote);
   PSTree->SetBranchAddress("tote_threshold",&tote_threshold);
   PSTree->SetBranchAddress("ecore",&ecore);
   PSTree->SetBranchAddress("triggertime",&triggertime);
   PSTree->SetBranchAddress("evt_timehigh",&evt_timehigh);
   PSTree->SetBranchAddress("evt_timelow",&evt_timelow);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// PSTree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   TH1F* hecore = new TH1F("hecore","hecore",
                                 10000,0.0,10000.0);
   TH1F* hecores = new TH1F("hecores","hecores",
                                 10000,0.0,10000.0);
   TH1F* hecore_first = new TH1F("hecore_first","hecore_first",
                                 10000,0.0,10000.0);
   TH1F* hecore_second = new TH1F("hecore_second","hecore_second",
                                 10000,0.0,10000.0);
   TH1F* hecore_seconds = new TH1F("hecore_seconds","hecore_seconds",
                                 10000,0.0,10000.0);
   TH1F* hecore_secondt = new TH1F("hecore_secondt","hecore_secondt",
                                 10000,0.0,10000.0);
   TH1F* hecore_secondts = new TH1F("hecore_secondts","hecore_secondts",
                                 10000,0.0,10000.0);
   TH1F* htriggertime_diff = new TH1F("htriggertime_diff","htriggertime_diff",
                                 10000,0.0,66000.0);
   TH1F* hevttime_diff = new TH1F("hevttime_diff","hevttime_diff",  
                                 10000,0.0,10000.0);  // all events

   Int_t nentries = PSTree->GetEntries();
   cout<<" total number of events "<<nentries<<endl;
   Bool_t first_is_bi;
   Bool_t within_time_window; // 164 microsecond = 12331 counts cut at 25000
   for (Int_t ievt=0; ievt<(nentries-1);ievt++) {
      if (ievt%100000==0) cout<<" now event "<<ievt<<endl;
      PSTree->GetEntry(ievt);
      ecore_f = ecore;
      nsegs_f = nsegs;
      tote_f  = tote;
      triggertime_f = triggertime;
      evt_timehigh_f = evt_timehigh;
      evt_timelow_f = evt_timelow;
      for (Int_t icha=0; icha<nsegs; icha++) {
         iseg_f[icha] = iseg[icha];
         eseg_f[icha] = eseg[icha];
      }

      PSTree->GetEntry(ievt+1);
      ecore_s = ecore;
      nsegs_s = nsegs;
      tote_s  = tote;
      triggertime_s = triggertime;
      evt_timehigh_s = evt_timehigh;
      evt_timelow_s = evt_timelow;
      for (Int_t icha=0; icha<nsegs; icha++) {
         iseg_s[icha] = iseg[icha];
         eseg_s[icha] = eseg[icha];
      }

      // following cut is for S-III who has no signal in segment 16
      if (TMath::Abs(ecore_f-tote_f)>10.0 || TMath::Abs(ecore_s-tote_s)>10.0) continue;

      if (triggertime_s>triggertime_f) 
        htriggertime_diff->Fill(float(triggertime_s-triggertime_f));
      else                             
        htriggertime_diff->Fill(float(triggertime_s-triggertime_f+65536));

      hecore->Fill(ecore_f);
      if (nsegs_f==1) hecores->Fill(ecore_f);
      hevttime_diff->Fill(((evt_timehigh_s-evt_timehigh_f)*65536+(evt_timelow_s-evt_timelow_f))*0.0133333);


      first_is_bi = kFALSE;
      for (Int_t ie=0; ie<nbi; ie++) {
        if (TMath::Abs(ecore_f-ebi[ie])<5.0) first_is_bi=kTRUE;
      }

      if (first_is_bi) {
         hecore_first->Fill(ecore_f); 
         hecore_second->Fill(ecore_s);

         if (nsegs_s==1) hecore_seconds->Fill(ecore_s);

         within_time_window=kFALSE;
         Int_t time_diff = (evt_timehigh_s-evt_timehigh_f)*65536+(evt_timelow_s-evt_timelow_f);
         if (time_diff>0 && time_diff<60000) within_time_window=kTRUE;
         if (within_time_window) {
           hecore_secondt->Fill(ecore_s);
           if (nsegs_s==1) hecore_secondts->Fill(ecore_s);

           if (ecore_s>3000.0) {
/*
             cout<<"-------------------------"<<endl;
             cout<<" event "<<ievt
                 <<" core "<<ecore_f<<" "<<ecore_s<<endl;
             cout<<" time "<<evt_timehigh_f<<" "<<evt_timelow_f
                 <<" "<<evt_timehigh_s<<" "<<evt_timelow_s<<endl;
             cout<<" nsegs "<<nsegs_s<<endl;
             for (Int_t icha=0; icha<nsegs_s; icha++) {
                cout<<" seg "<<iseg_s[icha]<<" e "<<eseg_s[icha]<<endl;
             }
*/
             if (nsegs_s==1) {
               cout<<ecore_f<<"\&  "<<ecore_s<<"\&  "
                   <<float(time_diff)*0.0133333<<"\&  "
                   <<iseg_s[0]<<"\&  "<<eseg_s[0]<<"\\\\hline"<<endl;
             }
           }

         }
      }
   }

//-----------------------------------------
// save histograms
//-----------------------------------------
   TFile* houtput = new TFile(output_histogram_filename,"recreate");
   houtput->cd();
   hecore->Write();
   htriggertime_diff->Write();
   hevttime_diff->Write();
   hecores->Write();
   hecore_first->Write();
   hecore_second->Write();
   hecore_seconds->Write();
   hecore_secondt->Write();
   hecore_secondts->Write();
   houtput->Close();
}
