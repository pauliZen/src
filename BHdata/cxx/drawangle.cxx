//Draw delta vs. alpha contour for stars and BHs====//
//Command: [prog.] [rootfilename] [bhmass1]=========//
//             [bhmass2] [treename] [drawdir]=======//
// Str: rootfilename: root file name================//
// F:   bhmass1/2: bh mass==========================//
// Str: drawdir: figures store dir==================//
// Str: treename: langle tree=======================//

#include "initial.h"
#include "TFile.h"
#include "uftools.h"
#include <string>
#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLine.h"

int main(int argc, char* argv[])
{
  pars_initial init(".drawangle_config");
  init.add("rootfilename","root file name to open","run-020-020-1mil-result.root");
  init.add("bhmass1","bh mass 1",(float)0.02);
  init.add("bhmass2","bh mass 2",(float)0.02);
  init.add("rinf","influence radius",(float)0.22);
  init.add("drawdir","directory to store figures","./");
  init.add("treename","tree name which store langle","langle");
  init.add("draw_theta_alpha_cout","option for draw theta_alpha plots coutour", (bool)1);
  init.add("draw_theta_alpha_mean","option for draw theta_alpha mean plots coutour", (bool)1);
  init.add("draw_theta_alpha_elimit","option for draw theta_alpha plots coutour with energy limit", (bool)1);
  init.add("draw_theta_alpha_rinf","option for draw theta_alpha with rinf limit",(bool)1);
  init.add("draw_before_after_cout","option for draw before_after plots coutour", (bool)1);
  init.add("draw_before_after_mean","option for draw before_after mean plots coutour", (bool)1);
  init.add("draw_before_after_elimit","option for draw before_after plots coutour with energy limit", (bool)1);
  init.add("draw_before_after_rinf","option for draw before_after plots with rinf limit", (bool)1);
  init.initial(argc,argv);

  std::string rootf=init.get<std::string>("rootfilename");
  std::string treen=init.get<std::string>("treename");
  std::string ddir=init.get<std::string>("drawdir");
  std::string bh1m=init.get<std::string>("bhmass1");
  std::string bh2m=init.get<std::string>("bhmass2");
  std::string rinf=init.get<std::string>("rinf");

  TFile *f=new TFile(rootf.c_str(),"update");
  TTree *tr=(TTree*)gDirectory->Get(treen.c_str());
  Int_t index;
  Double_t t, theta[2], phi[2], li[6], lo[6], lbi[6], lbo[6];
  Double_t lsim[3][6], lsom[3][6], lsie[3][6], lsoe[3][6];
  tr->SetBranchAddress("index",&index);
  tr->SetBranchAddress("t",&t);
  tr->SetBranchAddress("theta",theta);
  tr->SetBranchAddress("phi",phi);
  tr->SetBranchAddress("Lsi",li);
  tr->SetBranchAddress("Lso",lo);
  tr->SetBranchAddress("Lbhi",lbi);
  tr->SetBranchAddress("Lbho",lbo);
  tr->SetBranchAddress("Lsi_mean",lsim);
  tr->SetBranchAddress("Lso_mean",lsom);
  tr->SetBranchAddress("Lsi_err",lsie);
  tr->SetBranchAddress("Lso_err",lsoe);
  TCanvas c1("c1","c1",800,800);

  if (init.get<bool>("draw_theta_alpha_cout"))
  {
    tr->Draw("cos(Lso[5]):Lso[4]","t>50","contZ");
    TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht=(TH2F*)hto->Clone();
    ht->SetName("Angle_so");
    ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht->SetXTitle("#alpha_{AE}");
    ht->SetYTitle("cos(#delta_{AE})");
    ht->GetXaxis()->SetRangeUser(0,6.283);
    ht->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbho[5]):Lbho[4]","t>50","CONTZ");
    TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb=(TH2F*)htbo->Clone();
    htb->SetName("Angle_bho");
    htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb->SetXTitle("#alpha_{AE}");
    htb->SetYTitle("cos(#delta_{AE})");
    htb->SetLineWidth(5);
    htb->GetXaxis()->SetRangeUser(0,6.283);
    htb->GetYaxis()->SetRangeUser(-1,1);

    ht->Draw("CONT1Z");
    htb->Draw("CONT2same");
    c1.Print((ddir+"Alpha_delta_o.pdf").c_str());
    c1.Print((ddir+"Alpha_delta_o.eps").c_str());
    c1.Print((ddir+"Alpha_delta_o.png").c_str());

    tr->Draw("cos(Lsi[5]):Lsi[4]","t>50","contZ");
    TH2F *hti=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht2=(TH2F*)hti->Clone();
    ht2->SetName("Angle_si");
    ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht2->SetXTitle("#alpha_{BE}");
    ht2->SetYTitle("cos(#delta_{BE})");
    ht2->GetXaxis()->SetRangeUser(0,6.283);
    ht2->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbhi[5]):Lbhi[4]","t>50","CONTZ");
    TH2F *htbi=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb2=(TH2F*)htbi->Clone();
    htb2->SetName("Angle_bhi");
    htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb2->SetXTitle("#alpha_{BE}");
    htb2->SetYTitle("cos(#delta_{BE})");
    htb2->SetLineWidth(5);
    htb2->GetXaxis()->SetRangeUser(0,6.283);
    htb2->GetYaxis()->SetRangeUser(-1,1);
      
    ht2->Draw("CONT1Z");
    htb2->Draw("CONT2same");
    c1.Print((ddir+"Alpha_delta_i.pdf").c_str());
    c1.Print((ddir+"Alpha_delta_i.eps").c_str());
    c1.Print((ddir+"Alpha_delta_i.png").c_str());
    c1.Clear();
  }

  if (init.get<bool>("draw_theta_alpha_mean"))
  {
    for (int i=0;i<3;i++)
    {
      std::string ii=to<std::string>(i);
      std::string ij=to<std::string>(i+1);
      tr->Draw(("Lso_mean["+ii+"][5]:Lso_mean["+ii+"][4]").c_str(),"t>50","contZ");
      TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht=(TH2F*)hto->Clone();
      ht->SetName("Angle_so");
      ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      ht->SetXTitle("#alpha_{AE}");
      ht->SetYTitle("cos(#delta_{AE})");
      ht->GetXaxis()->SetRangeUser(0,6.283);
      ht->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbho[5]):Lbho[4]","t>50","CONTZ");
      TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb=(TH2F*)htbo->Clone();
      htb->SetName("Angle_bho");
      htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      htb->SetXTitle("#alpha_{AE}");
      htb->SetYTitle("cos(#delta_{AE})");
      htb->SetLineWidth(5);
      htb->GetXaxis()->SetRangeUser(0,6.283);
      htb->GetYaxis()->SetRangeUser(-1,1);

      ht->Draw("CONT1Z");
      htb->Draw("CONT2same");
      c1.Print((ddir+"Alpha_delta_om"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"Alpha_delta_om"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"Alpha_delta_om"+to<std::string>(i)+".png").c_str());

      tr->Draw(("Lsi_mean["+ii+"][5]:Lsi_mean["+ii+"][4]").c_str(),"t>50","contZ");
      TH2F *hti=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht2=(TH2F*)hti->Clone();
      ht2->SetName("Angle_si");
      ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      ht2->SetXTitle("#alpha_{BE}");
      ht2->SetYTitle("cos(#delta_{BE})");
      ht2->GetXaxis()->SetRangeUser(0,6.283);
      ht2->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbhi[5]):Lbhi[4]","t>50","contZ");
      TH2F *htbi=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb2=(TH2F*)htbi->Clone();
      htb2->SetName("Angle_bhi");
      htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      htb2->SetXTitle("#alpha_{BE}");
      htb2->SetYTitle("cos(#delta_{BE})");
      htb2->SetLineWidth(5);
      htb2->GetXaxis()->SetRangeUser(0,6.283);
      htb2->GetYaxis()->SetRangeUser(-1,1);
      
      ht2->Draw("CONT1Z");
      htb2->Draw("CONT2same");
      c1.Print((ddir+"Alpha_delta_im"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"Alpha_delta_im"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"Alpha_delta_im"+to<std::string>(i)+".png").c_str());
      c1.Clear();
    }
  }

  if (init.get<bool>("draw_theta_alpha_elimit"))
  {
    for (int i=0;i<3;i++)
    {
      std::string crit=to<std::string>((float)i/3*0.02E-3);
      tr->Draw("cos(Lso[5]):Lso[4]",("t>50&&En[1]>"+crit).c_str(),"contZ");
      TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht=(TH2F*)hto->Clone();
      ht->SetName("Angle_so");
      ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      ht->SetXTitle("#alpha_{AE}");
      ht->SetYTitle("cos(#delta_{AE})");
      ht->GetXaxis()->SetRangeUser(0,6.283);
      ht->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbho[5]):Lbho[4]","t>50","CONTZ");
      TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb=(TH2F*)htbo->Clone();
      htb->SetName("Angle_bho");
      htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      htb->SetXTitle("#alpha_{AE}");
      htb->SetYTitle("cos(#delta_{AE})");
      htb->SetLineWidth(5);
      htb->GetXaxis()->SetRangeUser(0,6.283);
      htb->GetYaxis()->SetRangeUser(-1,1);

      ht->Draw("CONT1Z");
      htb->Draw("CONT2same");
      c1.Print((ddir+"Alpha_delta_o"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"Alpha_delta_o"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"Alpha_delta_o"+to<std::string>(i)+".png").c_str());

      tr->Draw("cos(Lsi[5]):Lsi[4]",("t>50&&En[1]>"+crit).c_str(),"contZ");
      TH2F *hti=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht2=(TH2F*)hti->Clone();
      ht2->SetName("Angle_si");
      ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      ht2->SetXTitle("#alpha_{BE}");
      ht2->SetYTitle("cos(#delta_{BE})");
      ht2->GetXaxis()->SetRangeUser(0,6.283);
      ht2->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbhi[5]):Lbhi[4]","t>50","CONTZ");
      TH2F *htbi=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb2=(TH2F*)htbi->Clone();
      htb2->SetName("Angle_bhi");
      htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      htb2->SetXTitle("#alpha_{BE}");
      htb2->SetYTitle("cos(#delta_{BE})");
      htb2->SetLineWidth(5);
      htb2->GetXaxis()->SetRangeUser(0,6.283);
      htb2->GetYaxis()->SetRangeUser(-1,1);
      
      ht2->Draw("CONT1Z");
      htb2->Draw("CONT2same");
      c1.Print((ddir+"Alpha_delta_i"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"Alpha_delta_i"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"Alpha_delta_i"+to<std::string>(i)+".png").c_str());
      c1.Clear();
    }
  }
  
  if (init.get<bool>("draw_theta_alpha_rinf"))
  {
    tr->Draw("cos(Lso[5]):Lso[4]",("t>50&&rbo[0]<"+rinf).c_str(),"contZ");
    TH2F *htor=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htr=(TH2F*)htor->Clone();
    htr->SetName("Angle_so");
    htr->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    htr->SetXTitle("#alpha_{AE}");
    htr->SetYTitle("cos(#delta_{AE})");
    htr->GetXaxis()->SetRangeUser(0,6.283);
    htr->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbho[5]):Lbho[4]","t>50","CONTZ");
    TH2F *htbor=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htbr=(TH2F*)htbor->Clone();
    htbr->SetName("Angle_bho");
    htbr->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    htbr->SetXTitle("#alpha_{AE}");
    htbr->SetYTitle("cos(#delta_{AE})");
    htbr->SetLineWidth(5);
    htbr->GetXaxis()->SetRangeUser(0,6.283);
    htbr->GetYaxis()->SetRangeUser(-1,1);

    htr->Draw("CONT1Z");
    htbr->Draw("CONT2same");
    c1.Print((ddir+"Alpha_delta_or.pdf").c_str());
    c1.Print((ddir+"Alpha_delta_or.eps").c_str());
    c1.Print((ddir+"Alpha_delta_or.png").c_str());

    tr->Draw("cos(Lsi[5]):Lsi[4]",("t>50&&rbi[0]<"+rinf).c_str(),"contZ");
    TH2F *htir=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht2r=(TH2F*)htir->Clone();
    ht2r->SetName("Angle_si");
    ht2r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    ht2r->SetXTitle("#alpha_{BE}");
    ht2r->SetYTitle("cos(#delta_{BE})");
    ht2r->GetXaxis()->SetRangeUser(0,6.283);
    ht2r->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbhi[5]):Lbhi[4]","t>50","CONTZ");
    TH2F *htbir=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb2r=(TH2F*)htbir->Clone();
    htb2r->SetName("Angle_bhi");
    htb2r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    htb2r->SetXTitle("#alpha_{BE}");
    htb2r->SetYTitle("cos(#delta_{BE})");
    htb2r->SetLineWidth(5);
    htb2r->GetXaxis()->SetRangeUser(0,6.283);
    htb2r->GetYaxis()->SetRangeUser(-1,1);

    ht2r->Draw("CONT1Z");
    htb2r->Draw("CONT2same");
    c1.Print((ddir+"Alpha_delta_ir.pdf").c_str());
    c1.Print((ddir+"Alpha_delta_ir.eps").c_str());
    c1.Print((ddir+"Alpha_delta_ir.png").c_str());
    c1.Clear();
  }

  if (init.get<bool>("draw_before_after_cout"))
  {
    tr->Draw("cos(Lso[5]):cos(Lsi[5])","t>50","contZ");
    TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht=(TH2F*)hto->Clone();
    ht->SetName("Angle_sio");
    ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht->SetXTitle("cos(#delta)_{BE}");
    ht->SetYTitle("cos(#delta)_{AE})");
    ht->GetXaxis()->SetRangeUser(-1,1);
    ht->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbho[5]):cos(Lbhi[5])","t>50","CONTZ");
    TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb=(TH2F*)htbo->Clone();
    htb->SetName("Angle_bhio");
    htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb->SetXTitle("cos(#delta)_{BE}");
    htb->SetYTitle("cos(#delta)_{AE})");
    htb->SetLineWidth(5);
    htb->GetXaxis()->SetRangeUser(-1,1);
    htb->GetYaxis()->SetRangeUser(-1,1);

    TLine *tl=new TLine(-1,-1,1,1);
    tl->SetLineColor(kBlack);
    tl->SetLineStyle(2);
    
    ht->Draw("CONT1Z");
    htb->Draw("CONT2same");
    tl->Draw();
    c1.Print((ddir+"delta_io.pdf").c_str());
    c1.Print((ddir+"delta_io.eps").c_str());
    c1.Print((ddir+"delta_io.png").c_str());

    tr->Draw("Lso[4]:Lsi[4]","t>50","contZ");
    TH2F *hto3=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht3=(TH2F*)hto3->Clone();
    ht3->SetName("Angle_sio");
    ht3->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht3->SetXTitle("#alpha_{BE}");
    ht3->SetYTitle("#alpha_{AE})");
    ht3->GetXaxis()->SetRangeUser(0,6.283);
    ht3->GetYaxis()->SetRangeUser(0,6.283);

    tr->Draw("Lbho[4]:Lbhi[4]","t>50","CONTZ");
    TH2F *htbo3=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb3=(TH2F*)htbo3->Clone();
    htb3->SetName("Angle_bhio");
    htb3->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb3->SetXTitle("#alpha_{BE}");
    htb3->SetYTitle("#alpha_{AE})");
    htb3->SetLineWidth(5);
    htb3->GetXaxis()->SetRangeUser(0,6.283);
    htb3->GetYaxis()->SetRangeUser(0,6.283);

    TLine *tl2=new TLine(0,0,6.283,6.283);
    tl2->SetLineColor(kBlack);
    tl2->SetLineStyle(2);

    ht3->Draw("CONT1Z");
    htb3->Draw("CONT2same");
    tl2->Draw();
    c1.Print((ddir+"alpha_io.pdf").c_str());
    c1.Print((ddir+"alpha_io.eps").c_str());
    c1.Print((ddir+"alpha_io.png").c_str());

    tr->Draw("log10(Lso[3]):log10(Lsi[3])","t>50","contZ");
    TH2F *hto2=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht2=(TH2F*)hto2->Clone();
    ht2->SetName("Angle_sio");
    ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht2->SetXTitle("Log(L_{r,BE})");
    ht2->SetYTitle("Log(L_{r,AE})");
    ht2->GetXaxis()->SetRangeUser(-9.0,-6.5);
    //    ht2->GetXaxis()->SetLimits(-9.0,-6.5);
    ht2->GetYaxis()->SetRangeUser(-9.0,-6.5);
    //    ht2->GetYaxis()->SetLimits(-9.0,-6.5);
    ht2->GetYaxis()->SetTitleOffset(1.43);

    tr->Draw("log10(Lbho[4]):log10(Lbhi[4])","t>50","CONTZ");
    TH2F *htbo2=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb2=(TH2F*)htbo2->Clone();
    htb2->SetName("Angle_bhio");
    htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb2->SetXTitle("Log(L_{r,BE})");
    htb2->SetYTitle("Log(L_{r,AE})");
    htb2->SetLineWidth(5);
    htb2->GetXaxis()->SetRangeUser(-9.0,-6.5);
    //    htb2->GetXaxis()->SetLimits(-9.0,-6.5);
    htb2->GetYaxis()->SetRangeUser(-9.0,-6.5);
    //    htb2->GetYaxis()->SetLimits(-9.0,-6.5);
    htb2->GetYaxis()->SetTitleOffset(1.43);

    TLine *tl3=new TLine(-9.0,-9.0,-6.5,-6.5);
    tl3->SetLineColor(kBlack);
    tl3->SetLineStyle(2);

    ht2->Draw("CONT1Z");
    htb2->Draw("CONT2same");
    tl3->Draw();
    c1.Print((ddir+"r_io.pdf").c_str());
    c1.Print((ddir+"r_io.eps").c_str());
    c1.Print((ddir+"r_io.png").c_str());
  }
  
  if (init.get<bool>("draw_before_after_elimit"))
  {
    for (Int_t i=0;i<3;i++)
    {
      std::string ind=to<std::string>(i);
      std::string crit=to<std::string>((float)i/3*0.02E-3);
      tr->Draw("cos(Lso[5]):cos(Lsi[5])",("t>50&&En[1]>"+crit).c_str(),"contZ");
      TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht=(TH2F*)hto->Clone();
      ht->SetName("Angle_sio");
      ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      ht->SetXTitle("cos(#delta)_{BE}");
      ht->SetYTitle("cos(#delta)_{AE})");
      ht->GetXaxis()->SetRangeUser(-1,1);
      ht->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbho[5]):cos(Lbhi[5])","t>50","CONTZ");
      TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb=(TH2F*)htbo->Clone();
      htb->SetName("Angle_bhio");
      htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
      htb->SetXTitle("cos(#delta)_{BE}");
      htb->SetYTitle("cos(#delta)_{AE})");
      htb->SetLineWidth(5);
      htb->GetXaxis()->SetRangeUser(-1,1);
      htb->GetYaxis()->SetRangeUser(-1,1);

      TLine *tl=new TLine(-1,-1,1,1);
      tl->SetLineColor(kBlack);
      tl->SetLineStyle(2);

      ht->Draw("CONT1Z");
      htb->Draw("CONT2same");
      tl->Draw();
      c1.Print((ddir+"delta_io"+ind+".pdf").c_str());
      c1.Print((ddir+"delta_io"+ind+".eps").c_str());
      c1.Print((ddir+"delta_io"+ind+".png").c_str());

      tr->Draw("Lso[4]:Lsi[4]",("t>50&&En[1]>"+crit).c_str(),"contZ");
      TH2F *hto3=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht3=(TH2F*)hto3->Clone();
      ht3->SetName("Angle_sio");
      ht3->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      ht3->SetXTitle("#alpha_{BE}");
      ht3->SetYTitle("#alpha_{AE})");
      ht3->GetXaxis()->SetRangeUser(0,6.283);
      ht3->GetYaxis()->SetRangeUser(0,6.283);

      tr->Draw("Lbho[4]:Lbhi[4]","t>50","CONTZ");
      TH2F *htbo3=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb3=(TH2F*)htbo3->Clone();
      htb3->SetName("Angle_bhio");
      htb3->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
      htb3->SetXTitle("#alpha_{BE}");
      htb3->SetYTitle("#alpha_{AE})");
      htb3->SetLineWidth(5);
      htb3->GetXaxis()->SetRangeUser(0,6.283);
      htb3->GetYaxis()->SetRangeUser(0,6.283);

      TLine *tl2=new TLine(0,0,6.283,6.283);
      tl2->SetLineColor(kBlack);
      tl2->SetLineStyle(2);

      ht3->Draw("CONT1Z");
      htb3->Draw("CONT2same");
      tl2->Draw();
      c1.Print((ddir+"alpha_io"+ind+".pdf").c_str());
      c1.Print((ddir+"alpha_io"+ind+".eps").c_str());
      c1.Print((ddir+"alpha_io"+ind+".png").c_str());

      tr->Draw("log10(Lso[3]):log10(Lsi[3])",("t>50&&En[1]>"+crit).c_str(),"contZ");
      TH2F *hto2=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht2=(TH2F*)hto2->Clone();
      ht2->SetName("Angle_sio");
      ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (#Delta E >"+crit+")").c_str());
      ht2->SetXTitle("Log(L_{r,BE})");
      ht2->SetYTitle("Log(L_{r,AE})");
      ht2->GetXaxis()->SetRangeUser(-9.0,-6.5);
      ht2->GetYaxis()->SetRangeUser(-9.0,-6.5);

      tr->Draw("log10(Lbho[4]):log10(Lbhi[4])","t>50","CONTZ");
      TH2F *htbo2=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb2=(TH2F*)htbo2->Clone();
      htb2->SetName("Angle_bhio");
      htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
      htb2->SetXTitle("Log(L_{r,BE})");
      htb2->SetYTitle("Log(L_{r,AE})");
      htb2->SetLineWidth(5);
      htb2->GetXaxis()->SetRangeUser(-9.0,-6.5);
      htb2->GetYaxis()->SetRangeUser(-9.0,-6.5);

      TLine *tl3=new TLine(-9.0,-9.0,-6.5,-6.5);
      tl3->SetLineColor(kBlack);
      tl3->SetLineStyle(2);

      ht2->Draw("CONT1Z");
      htb2->Draw("CONT2same");
      tl3->Draw();
      c1.Print((ddir+"r_io"+ind+".pdf").c_str());
      c1.Print((ddir+"r_io"+ind+".eps").c_str());
      c1.Print((ddir+"r_io"+ind+".png").c_str());
    }
  }
  
  if (init.get<bool>("draw_before_after_mean"))
  {
    for (int i=0;i<3;i++)
    {
      std::string ii=to<std::string>(i);
      std::string ij=to<std::string>(i+1);
      tr->Draw(("Lso_mean["+ii+"][5]:Lsi_mean["+ii+"][5]").c_str(),"t>50","contZ");
      TH2F *hto=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht=(TH2F*)hto->Clone();
      ht->SetName("Angle_sio");
      ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      ht->SetXTitle("cos(#delta)_{BE}");
      ht->SetYTitle("cos(#delta)_{AE})");
      ht->GetXaxis()->SetRangeUser(-1,1);
      ht->GetYaxis()->SetRangeUser(-1,1);

      tr->Draw("cos(Lbho[5]):cos(Lbhi[5])","t>50","CONTZ");
      TH2F *htbo=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb=(TH2F*)htbo->Clone();
      htb->SetName("Angle_bhio");
      htb->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      htb->SetXTitle("cos(#delta)_{BE}");
      htb->SetYTitle("cos(#delta)_{AE})");
      htb->SetLineWidth(5);
      htb->GetXaxis()->SetRangeUser(-1,1);
      htb->GetYaxis()->SetRangeUser(-1,1);

      TLine *tl=new TLine(-1,-1,1,1);
      tl->SetLineColor(kBlack);
      tl->SetLineStyle(2);

      ht->Draw("CONT1Z");
      htb->Draw("CONT2same");
      tl->Draw();
      c1.Print((ddir+"delta_iom"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"delta_iom"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"delta_iom"+to<std::string>(i)+".png").c_str());

      tr->Draw(("Lso_mean["+ii+"][4]:Lsi_mean["+ii+"][4]").c_str(),"t>50","contZ");
      TH2F *hto2=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *ht2=(TH2F*)hto2->Clone();
      ht2->SetName("Angle_sio");
      ht2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      ht2->SetXTitle("#alpha_{BE}");
      ht2->SetYTitle("#alpha_{AE})");
      ht2->GetXaxis()->SetRangeUser(0,6.283);
      ht2->GetYaxis()->SetRangeUser(0,6.283);

      tr->Draw("Lbho[4]:Lbhi[4]","t>50","CONTZ");
      TH2F *htbo2=(TH2F*)gPad->GetPrimitive("htemp");
      TH2F *htb2=(TH2F*)htbo2->Clone();
      htb2->SetName("Angle_bhio");
      htb2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (Average "+ij+"0 )").c_str());
      htb2->SetXTitle("#alpha_{BE}");
      htb2->SetYTitle("#alpha_{AE})");
      htb2->SetLineWidth(5);
      htb2->GetXaxis()->SetRangeUser(0,6.283);
      htb2->GetYaxis()->SetRangeUser(0,6.283);

      TLine *tl2=new TLine(0,0,6.283,6.283);
      tl2->SetLineColor(kBlack);
      tl2->SetLineStyle(2);

      ht2->Draw("CONT1Z");
      htb2->Draw("CONT2same");
      tl2->Draw();
      c1.Print((ddir+"alpha_iom"+to<std::string>(i)+".pdf").c_str());
      c1.Print((ddir+"alpha_iom"+to<std::string>(i)+".eps").c_str());
      c1.Print((ddir+"alpha_iom"+to<std::string>(i)+".png").c_str());
    }
  }
    
  if (init.get<bool>("draw_before_after_rinf"))
  {
    tr->Draw("cos(Lso[5]):cos(Lsi[5])",("t>50&&rbi[0]<"+rinf+"&&rbo[0]<"+rinf).c_str(),"contZ");
    TH2F *htor=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htr=(TH2F*)htor->Clone();
    htr->SetName("Angle_sio");
    htr->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    htr->SetXTitle("cos(#delta)_{BE}");
    htr->SetYTitle("cos(#delta)_{AE})");
    htr->GetXaxis()->SetRangeUser(-1,1);
    htr->GetYaxis()->SetRangeUser(-1,1);

    tr->Draw("cos(Lbho[5]):cos(Lbhi[5])","t>50","CONTZ");
    TH2F *htbor=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htbr=(TH2F*)htbor->Clone();
    htbr->SetName("Angle_bhio");
    htbr->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htbr->SetXTitle("cos(#delta)_{BE}");
    htbr->SetYTitle("cos(#delta)_{AE})");
    htbr->SetLineWidth(5);
    htbr->GetXaxis()->SetRangeUser(-1,1);
    htbr->GetYaxis()->SetRangeUser(-1,1);

    TLine *tl=new TLine(-1,-1,1,1);
    tl->SetLineColor(kBlack);
    tl->SetLineStyle(2);

    htr->Draw("CONT1Z");
    htbr->Draw("CONT2same");
    tl->Draw();
    c1.Print((ddir+"delta_ior.pdf").c_str());
    c1.Print((ddir+"delta_ior.eps").c_str());
    c1.Print((ddir+"delta_ior.png").c_str());

    tr->Draw("Lso[4]:Lsi[4]",("t>50&&rbi[0]<"+rinf+"&&rbo[0]<"+rinf).c_str(),"contZ");
    TH2F *hto3r=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht3r=(TH2F*)hto3r->Clone();
    ht3r->SetName("Angle_sio");
    ht3r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    ht3r->SetXTitle("#alpha_{BE}");
    ht3r->SetYTitle("#alpha_{AE})");
    ht3r->GetXaxis()->SetRangeUser(0,6.283);
    ht3r->GetYaxis()->SetRangeUser(0,6.283);

    tr->Draw("Lbho[4]:Lbhi[4]","t>50","CONTZ");
    TH2F *htbo3r=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb3r=(TH2F*)htbo3r->Clone();
    htb3r->SetName("Angle_bhio");
    htb3r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb3r->SetXTitle("#alpha_{BE}");
    htb3r->SetYTitle("#alpha_{AE})");
    htb3r->SetLineWidth(5);
    htb3r->GetXaxis()->SetRangeUser(0,6.283);
    htb3r->GetYaxis()->SetRangeUser(0,6.283);

    TLine *tl2=new TLine(0,0,6.283,6.283);
    tl2->SetLineColor(kBlack);
    tl2->SetLineStyle(2);

    ht3r->Draw("CONT1Z");
    htb3r->Draw("CONT2same");
    tl2->Draw();
    c1.Print((ddir+"alpha_ior.pdf").c_str());
    c1.Print((ddir+"alpha_ior.eps").c_str());
    c1.Print((ddir+"alpha_ior.png").c_str());

    tr->Draw("log10(Lso[3]):log10(Lsi[3])",("t>50&&rbi[0]<"+rinf+"&&rbo[0]<"+rinf).c_str(),"contZ");
    TH2F *hto2r=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht2r=(TH2F*)hto2r->Clone();
    ht2r->SetName("Angle_sio");
    ht2r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+" (r_{b} <"+rinf+")").c_str());
    ht2r->SetXTitle("Log(L_{r,BE})");
    ht2r->SetYTitle("Log(L_{r,AE})");
    ht2r->GetXaxis()->SetRangeUser(-9.0,-6.5);
    ht2r->GetYaxis()->SetRangeUser(-9.0,-6.5);

    tr->Draw("log10(Lbho[4]):log10(Lbhi[4])","t>50","CONTZ");
    TH2F *htbo2r=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *htb2r=(TH2F*)htbo2r->Clone();
    htb2r->SetName("Angle_bhio");
    htb2r->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    htb2r->SetXTitle("Log(L_{r,BE})");
    htb2r->SetYTitle("Log(L_{r,AE})");
    htb2r->SetLineWidth(5);
    htb2r->GetXaxis()->SetRangeUser(-9.0,-6.5);
    htb2r->GetYaxis()->SetRangeUser(-9.0,-6.5);

    TLine *tl3=new TLine(-9.0,-9.0,-6.5,-6.5);
    tl3->SetLineColor(kBlack);
    tl3->SetLineStyle(2);

    ht2r->Draw("CONT1Z");
    htb2r->Draw("CONT2same");
    tl3->Draw();
    c1.Print((ddir+"r_ior.pdf").c_str());
    c1.Print((ddir+"r_ior.eps").c_str());
    c1.Print((ddir+"r_ior.png").c_str());
  }

  f->Close();
}
