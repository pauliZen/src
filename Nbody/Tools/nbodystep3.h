#ifndef nbodystep3_h
#define nbodystep3_h

//Mylibrary=========================================//
#include <nbodytools.h>
#include <uftools.h>
#include <nbodymultidraw.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TEntryList.h>

//STL===============================================//
#include <string>
#include <fstream>

class nbodystep3 : public nbodytools{
public:
  Float_t rbar;
  Int_t gnum,ns,np,nb,m1,p1;
  Double_t hnst[4], hnpt[4], hnpst[4], endt[2];        //0: half time, 1: half time err, 2: half time/end time 3: half time/end time err
  Int_t ssp[2], psp[2], pss[2], sss[2], spp[2], ppp[2];
  Int_t sp[2], ss[2], pp[2];
  Int_t ssss[2], spsp[2], sssp[2], sspp[2], sppp[2], pppp[2]; //number of encouter

  TBranch *b_rbar, *b_gnum, *b_ns, *b_np, *b_nb, *b_m1, *b_p1, *b_hnst, *b_hnpt, *b_hnpst, *b_endt;
  TBranch *b_ssp, *b_psp, *b_pss, *b_sss, *b_spp, *b_ppp;
  TBranch *b_sp, *b_ss, *b_pp;
  TBranch *b_ssss, *b_spsp, *b_sssp, *b_sspp, *b_sppp, *b_pppp;
  
  //Function==========================================//
  nbodystep3(): nbodytools("step3","triple data close encounter count") { Link(); }
  nbodystep3(std::string filename): nbodytools("step3","step3 data") { Link(filename); }
  virtual Int_t* operator[] (Int_t type);
  virtual Int_t* GetECNum(std::string name);
  virtual void MakeTexTable(std::string filename, int tnum, std::string *tableformat, int hnum, std::string* headformat, int snum, std::string *selection, std::string tabletitle="Encounter Numbers", std::string tableintro="Encounter Numbers for different types. ns:initial star number, nb:initial star-star binaries number, np:initial planet number; rbar:initial virial radius of cluster; em/ep: model parameters for planets ejecting velocity");
  virtual void Drawhps(std::string dir, std::string figname, std::string parsfile, int option = 0);

protected:
  virtual void Init();
};

Int_t* nbodystep3::operator[] (Int_t type)
{
  if (type==1) return ss;
  else if (type==2) return sp;
  else if (type==3) return pp;
  else if (type==4) return sss;
  else if (type==5) return ssp;
  else if (type==6) return pss;
  else if (type==7) return psp;
  else if (type==8) return spp;
  else if (type==9) return ppp;
  else if (type==10) return ssss;
  else if (type==11) return sssp;
  else if (type==12) return spsp;
  else if (type==13) return sspp;
  else if (type==14) return sppp;
  else if (type==15) return pppp;
  else return 0;
}

Int_t* nbodystep3::GetECNum(std::string name)
{
  if (name=="ss") return ss;
  else if (name=="sp") return sp;
  else if (name=="pp") return pp;
  else if (name=="sss") return sss;
  else if (name=="ssp") return ssp;
  else if (name=="pss") return pss;
  else if (name=="psp") return psp;
  else if (name=="spp") return spp;
  else if (name=="ppp") return ppp;
  else if (name=="ssss") return ssss;
  else if (name=="sssp") return sssp;
  else if (name=="spsp") return spsp;
  else if (name=="sspp") return sspp;
  else if (name=="sppp") return sppp;
  else if (name=="pppp") return pppp;
  else return 0;
}

//==================================================//
void nbodystep3::Init()
{
  if (state==1)
  {
    ftree->Branch("gnum",&gnum);
    ftree->Branch("ns",&ns);
    ftree->Branch("np",&np);
    ftree->Branch("nb",&nb);
    ftree->Branch("rbar",&rbar);
    ftree->Branch("m1",&m1);
    ftree->Branch("p1",&p1);
    ftree->Branch("hnst",hnst,"hnst[4]/D");
    ftree->Branch("hnpt",hnpt,"hnpt[4]/D");
    ftree->Branch("hnpst",hnpst,"hnpst[4]/D");
    ftree->Branch("endt",endt,"endt[2]/D");
    ftree->Branch("ss",ss,"ss[2]/I");
    ftree->Branch("sp",sp,"sp[2]/I");
    ftree->Branch("pp",pp,"pp[2]/I");
    ftree->Branch("sss",sss,"sss[2]/I");
    ftree->Branch("ssp",ssp,"ssp[2]/I");
    ftree->Branch("pss",pss,"pss[2]/I");
    ftree->Branch("psp",psp,"psp[2]/I");
    ftree->Branch("spp",spp,"spp[2]/I");
    ftree->Branch("ppp",ppp,"ppp[2]/I");
    ftree->Branch("ssss",ssss,"ssss[2]/I");
    ftree->Branch("sssp",sssp,"sssp[2]/I");
    ftree->Branch("spsp",spsp,"spsp[2]/I");
    ftree->Branch("sspp",sspp,"sspp[2]/I");
    ftree->Branch("sppp",sppp,"sppp[2]/I");
    ftree->Branch("pppp",pppp,"pppp[2]/I");

    b_gnum=(TBranch*)ftree->GetBranch("gnum");
    b_ns=(TBranch*)ftree->GetBranch("ns");
    b_np=(TBranch*)ftree->GetBranch("np");
    b_nb=(TBranch*)ftree->GetBranch("nb");
    b_rbar=(TBranch*)ftree->GetBranch("rbar");
    b_m1=(TBranch*)ftree->GetBranch("m1");
    b_p1=(TBranch*)ftree->GetBranch("p1");
    b_hnst=(TBranch*)ftree->GetBranch("hnst");
    b_hnpt=(TBranch*)ftree->GetBranch("hnpt");
    b_hnpst=(TBranch*)ftree->GetBranch("hnpst");
    b_endt=(TBranch*)ftree->GetBranch("endt");
    b_ss=(TBranch*)ftree->GetBranch("ss");
    b_sp=(TBranch*)ftree->GetBranch("sp");
    b_pp=(TBranch*)ftree->GetBranch("pp");
    b_sss=(TBranch*)ftree->GetBranch("sss");
    b_ssp=(TBranch*)ftree->GetBranch("ssp");
    b_pss=(TBranch*)ftree->GetBranch("pss");
    b_psp=(TBranch*)ftree->GetBranch("psp");
    b_spp=(TBranch*)ftree->GetBranch("spp");
    b_ppp=(TBranch*)ftree->GetBranch("ppp");
    b_ssss=(TBranch*)ftree->GetBranch("ssss");
    b_sssp=(TBranch*)ftree->GetBranch("sssp");
    b_spsp=(TBranch*)ftree->GetBranch("spsp");
    b_sspp=(TBranch*)ftree->GetBranch("sspp");
    b_sppp=(TBranch*)ftree->GetBranch("sppp");
    b_pppp=(TBranch*)ftree->GetBranch("pppp");
    std::cout<<"New step3 Tree build.\n";
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("gnum",&gnum,&b_gnum);
    fchain->SetBranchAddress("ns",&ns,&b_ns);
    fchain->SetBranchAddress("np",&np,&b_np);
    fchain->SetBranchAddress("nb",&nb,&b_nb);
    fchain->SetBranchAddress("rbar",&rbar,&b_rbar);
    fchain->SetBranchAddress("m1",&m1,&b_m1);
    fchain->SetBranchAddress("p1",&p1,&b_p1);
    fchain->SetBranchAddress("hnst",hnst,&b_hnst);
    fchain->SetBranchAddress("hnpt",hnpt,&b_hnpt);
    fchain->SetBranchAddress("hnpst",hnpst,&b_hnpst);
    fchain->SetBranchAddress("endt",endt,&b_endt);
    fchain->SetBranchAddress("ss",ss,&b_ss);
    fchain->SetBranchAddress("sp",sp,&b_sp);
    fchain->SetBranchAddress("pp",pp,&b_pp);
    fchain->SetBranchAddress("sss",sss,&b_sss);
    fchain->SetBranchAddress("ssp",ssp,&b_ssp);
    fchain->SetBranchAddress("pss",pss,&b_pss);
    fchain->SetBranchAddress("psp",psp,&b_psp);
    fchain->SetBranchAddress("spp",spp,&b_spp);
    fchain->SetBranchAddress("ppp",ppp,&b_ppp);
    fchain->SetBranchAddress("ssss",ssss,&b_ssss);
    fchain->SetBranchAddress("sssp",sssp,&b_sssp);
    fchain->SetBranchAddress("spsp",spsp,&b_spsp);
    fchain->SetBranchAddress("sspp",sspp,&b_sspp);
    fchain->SetBranchAddress("sppp",sppp,&b_sppp);
    fchain->SetBranchAddress("pppp",pppp,&b_pppp);
    std::cout<<"Chain step3 build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

void nbodystep3::MakeTexTable(std::string filename, int tnum, std::string* tableformat, int hnum, std::string* headformat, int snum, std::string *selection, std::string tabletitle, std::string tableintro)
{
  if (state==2)
  {
    std::ofstream tout(filename.c_str());
    if (tout.is_open())
    {
      tout<<"%----------------------------------------------------------------%\n"
          <<"% close encouter number table, s: star, p: planet;               %\n"
          <<"%----------------------------------------------------------------%\n"
          <<"\\begin{table}\n  \\begin{center}\n    \\caption{"<<tabletitle<<"}\n"
          <<"    \\begin{tabular}{|";
      for (int i=0;i<tnum+hnum;i++) tout<<"c|";
      tout<<"}\n\\hline\n";
      for (int i=0;i<hnum;i++)
      {
        if (headformat[i]=="ns") tout<<"$N_{s}$";
        else if (headformat[i]=="nb") tout<<"$N_{b}$";
        else if (headformat[i]=="np") tout<<"$N_{p}$";
        else if (headformat[i]=="rbar") tout<<"$R_{vir}$";
        else if (headformat[i]=="m1") tout<<"$M_{s}$";
        else if (headformat[i]=="p1") tout<<"$E_{j}$";
        if (i<hnum-1) tout<<"&";
      }
      for (int i=0;i<tnum;i++)
      {
        tout<<"&";
        if (tableformat[i]=="ss") tout<<"S-S";
        else if (tableformat[i]=="sp") tout<<"S-P";
        else if (tableformat[i]=="pp") tout<<"P-P";
        else if (tableformat[i]=="sss") tout<<"SS-S";
        else if (tableformat[i]=="ssp") tout<<"SP-S";
        else if (tableformat[i]=="pss") tout<<"SS-P";
        else if (tableformat[i]=="psp") tout<<"SP-P";
        else if (tableformat[i]=="spp") tout<<"PP-S";
        else if (tableformat[i]=="ppp") tout<<"PP-P";
        else if (tableformat[i]=="ssss") tout<<"SS-SS";
        else if (tableformat[i]=="sssp") tout<<"SS-SP";
        else if (tableformat[i]=="spsp") tout<<"SP-SP";
        else if (tableformat[i]=="sspp") tout<<"SS-PP";
        else if (tableformat[i]=="sppp") tout<<"SP-PP";
        else if (tableformat[i]=="pppp") tout<<"PP-PP";
      }
      tout<<"\\\\\n\\hline\n";
      for (int is=0;is<snum;is++)
      {
        fchain->Draw(">>slist",selection[is].c_str(),"entrylist");
        TEntryList *tl=(TEntryList*)gDirectory->Get("slist");
#ifdef DEBUG
        std::cout<<"Loop:"<<is<<"\tafter slist\n";
#endif        
        fchain->SetEntryList(tl);
        Int_t ntot=tl->GetN();
#ifdef DEBUG
        std::cout<<"Event Number:"<<ntot<<std::endl;
#endif        
        for (Int_t i=0; i<ntot; i++)
        {
          Int_t treenum=0;
          Int_t tentry=tl->GetEntryAndTree(i,treenum);
          fchain->GetEntry(tentry+fchain->GetTreeOffset()[treenum]);
          for (int j=0;j<hnum;j++)
          {
            if (headformat[j]=="ns") tout<<ns;
            else if (headformat[j]=="nb") tout<<nb;
            else if (headformat[j]=="np") tout<<np;
            else if (headformat[j]=="rbar") tout<<rbar;
            else if (headformat[j]=="m1")
            {
              if (m1==1) tout<<"1";
              else if (m1==2) tout<<"0.6";
              else tout<<"-";
            }
            else if (headformat[j]=="p1")
            {
              if (p1==1) tout<<'D';
              else if (p1==2) tout<<'P';
              else tout<<"-";
            }
            if (j!=hnum-1) tout<<"&";
          }
          for (int j=0;j<tnum;j++)
          {
            Int_t *n=GetECNum(tableformat[j]);
            if (!n)
            {
              std::cerr<<"Error: type "<<tableformat[j]<<" not found!\n";
              return;
            }
            tout<<"&$"<<n[0]<<"\\pm"<<n[1]<<"$";
          }
          tout<<"\\\\\n";
        }
        tout<<"\\hline\n";
        fchain->SetEntryList(0);
        delete tl;
      }
      tout<<"    \\end{tabular}\n    %\\tablecomments{"<<tableintro<<"}\n"
          <<"  \\end{center}\n\\end{table}\n"
          <<"%----------------------------------------------------------------%\n";
    }
    else std::cerr<<"Error: "+filename+" cannot open!\n";
  }
  else std::cerr<<"Error: state=1!\n";
}

void nbodystep3::Drawhps(std::string dir,std::string figname, std::string parsfile, int option)
{
  Float_t ple[4]={0.12,0.45,0.33,0.89};
  if (option==0) MultiDraw(this,dir,figname,parsfile,"hnst[0]:hnst[1]:hnpt[0]:hnpt[1]",ple,"t_{h,s}","t_{h,p}");
  else if (option==1) MultiDraw(this,dir,figname,parsfile,"hnst[2]:hnst[3]:hnpt[2]:hnpt[3]",ple,"t_{h,s} / t_{t,s}","t_{h,p} / t_{t,p}");
  else {
    std::cerr<<"Error: option not right (now:"<<option<<"), please choose 0 or 1\n";
  }
}

#endif
