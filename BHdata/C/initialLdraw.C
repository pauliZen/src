//Draw initial angularmomentum distribution=========//
//draw distribution=================================//
void drawLd(string parameter="Lalpha",string treename="E150to100")
{
  TTree *e=(TTree*)gDirectory->Get(treename.c_str());
  string li=parameter+"_start";
  e->Draw((li+">>h1").c_str());
  TH1F *lsd=(TH1F*)gDirectory->Get("h1");
  lsd->SetTitle((li+" distribution").c_str());
  lsd->SetXTitle(li.c_str());
  lsd->SetYTitle("N");
}

//draw all distribution
void drawAlld(string directory="run-020-020-1mil/",string treename="E150to100")
{
  TCanvas c2;
  TTree *e=(TTree*)gDirectory->Get(treename.c_str());
  string l[6]={"Lalpha_start","Ldelta_start","Lr_start","Lx_start","Ly_start","Lz_start"};
  for (int i=0;i<6;i++)
  {
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    string ii;
    sstr>>ii;
    c2.cd();
    e->Draw(l[i].c_str());
    // TH1F *lsd=(TH1F*)gDirectory->Get("h1");
    // lsd->SetTitle((l[i]+" distribution").c_str());
    // lsd->SetXTitle(l[i].c_str());
    // lsd->SetYTitle("N");
    // lsd->Draw();
    c2->Update();
    c2->Print(("~/Dropbox/Datas/BHdata/figures/"+directory+"L"+ii+"_all_distribution").c_str());
  }
}
 
//draw all CONT of end:start============================//
void drawAllp(string directory="run-020-020-1mil/",string treename="E150to100")
{
  TCanvas c2;
  TTree *e=(TTree*)gDirectory->Get(treename.c_str());
  string l[6]={"Lalpha_end:Lalpha_start","Ldelta_end:Ldelta_start","Lr_end:Lr_start","Lx_end:Lx_start","Ly_end:Ly_start","Lz_end:Lz_start"};
  for (int i=0;i<6;i++)
  {
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    string ii;
    sstr>>ii;
    c2.cd();
    e->Draw(l[i].c_str(),"","CONT1");
    // TH1F *lsd=(TH1F*)gDirectory->Get("h1");
    // lsd->SetTitle((l[i]+" distribution").c_str());
    // lsd->SetXTitle(l[i].c_str());
    // lsd->SetYTitle("N");
    // lsd->Draw();
    c2->Update();
    c2->Print(("~/Dropbox/Datas/BHdata/figures/"+directory+"L"+ii+"s_e_all_CONT").c_str());
  }
}

