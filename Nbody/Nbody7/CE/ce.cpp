#include <iostream>
#include <list>
#include <deque>
#include <fstream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"

#define NVOL 80
#define SUBDIV 100

//global variables==================================//
static double rbar, zmbar, tstar, rau, vstar;

//element for store each encounter event============//
struct cepair{
  Int_t name[4], type;
  bool exchange;
  int sn[4];
  Double_t x[3][3], v[3][3], m[4], ecc[3], peri[3], semi[3], t[3], energy[3];
  Double_t bip[3], vp[3], vinf[3];
  void store(int index, Double_t xx[], Double_t xdot[], Double_t eecc, Double_t pperi, Double_t ssemi, Double_t eene, Double_t tt, Double_t bb, Double_t vvinf, Double_t vvp)
  {
    for (int i=0;i<3;i++)
    {
      x[index][i]=xx[i];
      v[index][i]=xdot[i];
    }
    ecc[index]=eecc;
    peri[index]=pperi;
    semi[index]=ssemi;
    energy[index]=eene;
    t[index]=tt;
    bip[index]=bb;
    vp[index]=vvp;
    vinf[index]=vvinf;
  }
  void init(int type, int nn[], Double_t mm[], int ssn[])
  {
    for (int i=0;i<type;i++)
    {
      sn[i]=ssn[i];
      name[i]=nn[i];
      m[i]=mm[i];
    }
    exchange=0;
  }
  void out(Int_t oname[], Int_t &otype, Double_t ox[][3], Double_t ov[][3],Double_t om[], Double_t oecc[], Double_t operi[], Double_t osemi[], Double_t oene[], Double_t ot[],Bool_t oexc, Double_t ovinf[], Double_t ovp[], Double_t ob[])
  {
    for (int i=0;i<4;i++)
    {
      oname[i]=name[i];
      om[i]=m[i];
    }
    for (int i=0;i<3;i++)
    {
      for (int j=0;j<3;j++)
      {
        ox[j][i]=x[j][i]*rbar;
        ov[j][i]=v[j][i]*vstar;
      }
      oecc[i]=ecc[i];
      operi[i]=peri[i]*rau;
      osemi[i]=semi[i]*rau;
      oene[i]=energy[i]*rbar*vstar*vstar;
      ot[i]=t[i]*tstar;
      ovinf[i]=vinf[i]*vstar;
      ovp[i]=vp[i]*vstar;
      ob[i]=bip[i]*rau;
    }
    oexc=exchange;
    otype=type;
  }
};

//global variables==================================//
static std::deque<cepair> b[3][NVOL];
static int nstar;
static int bname[3][4]={};
static int bi[3][2];
static int counts[15]={};

//double percision vector dot=======================//
Double_t dot3(Double_t a[3])
{
  return a[0]*a[0]+a[1]*a[1]+a[2]*a[2];
}

//x and v is relative distance and velocity=========//
//calculate bounding energy and semi================//
// Double_t cal_semi(Double_t &m1, Double_t &m2, Double_t x[3], Double_t v[3], Double_t &dotx)
// {
//   dotx=sqrt(dot3(x));
//   Double_t ase=2/dotx-dot3(v)/(m1+m2);
//   return 1.0/ase;
// }

//calculate parameters==============================//
void cal_pars(Double_t &m1, Double_t &m2, Double_t &msys, Double_t x[3], Double_t v[3], Double_t &eng, Double_t &semi, Double_t &ecc, Double_t &peri)
{
  //calculate energy and semi-major-axis==============//
  Double_t dotx=sqrt(dot3(x));
  Double_t bE=dot3(v)/msys-2.0/dotx;
  semi=-1.0/bE;
  eng=m1*m2*bE/2.0;

  //calculate eccentricity============================//
  Double_t p1=1-dotx/semi;
  Double_t crs=x[0]*v[0]+x[1]*v[1]+x[2]*v[2];
  ecc=sqrt(p1*p1+crs*crs/semi/msys);
#ifdef DEBUG
  std::cout<<"LW_CE: p1="<<p1<<"\t"<<"ecc="<<ecc<<std::endl;
#endif  
  
  //calculate peri-center=============================//
  peri=semi*(1-ecc);
}

//calculate more pars===============================//
void cal_more(Double_t &msys, Double_t &semi, Double_t &ecc, Double_t &bip, Double_t &vinf, Double_t &vp)
{
  //calculate infinite velocity=======================//
  Double_t vp2=fabs(msys/semi);
  vinf=sqrt(vp2);
  
  //calculate peri-center velocity====================//
  vp=sqrt(vp2*(ecc+1)/(ecc-1));

  //calculate impact parameter========================//
  bip=-semi*sqrt(fabs(ecc*ecc-1));
#ifdef DEBUG
  std::cout<<"LW_CE: vp2="<<vp2<<"\tvp="<<vp<<"\tbip="<<bip<<std::endl;
#endif  
}

//For fortran call==================================//
extern "C"
{
  void getnstar_(int *);
  void storece_(int *,int *, int *, int *,double *,double *,double *,double *);
  void endstore_();
  void getunit_(double *, double *, double *, double *, double*);
}

//get unit for transform============================//
void getunit_(double *rrbar, double *rrau, double *ttstar, double *zzmbar, double *vvstar)
{
  rbar=*rrbar;
  rau=*rrau;
  tstar=*ttstar;
  zmbar=*zzmbar;
  vstar=*vvstar;
}

//get number of stars===============================//
void getnstar_(int *n)
{
  nstar=*n;
#ifdef DEBUG
  std::cout<<"LW-CE: get nstar: "<<nstar<<std::endl;
#endif
}

//exchange n1 and n2================================//
void SWAP(int &n1, int &n2)
{
  int tmp=n2;
  n2=n1;
  n1=tmp;
}

//sort n============================================//
bool sort2(int n[])
{
  if (n[0]>n[1])
  {
    SWAP(n[0],n[1]);
    return 1;
  }
  return 0;
}

bool sort3(int n[])
{
  bool exc=0;
  if (n[0]>n[1])  
  {
    SWAP(n[0],n[1]);
    exc=1;
  }
  if (n[0]>n[2])
  {
    SWAP(n[0],n[2]);
    exc=1;
  }
  if (n[1]>n[2]) SWAP(n[1],n[2]);
  return exc;
}

bool sort4(int n[])
{
  bool exc=0;
  if (n[0]>n[1]) SWAP(n[0],n[1]);
  if (n[1]>n[2])
  {
    int tmp=n[2];
    n[2]=n[1];
    if (n[0]>tmp)
    {
      n[1]=n[0];
      n[0]=tmp;
    }
    else n[1]=tmp;
    exc=1;
  }
  if (n[2]>n[3])
  {
    int tmp=n[3];
    n[3]=n[2];
    if (n[1]>tmp)
    {
      n[2]=n[1];
      exc=1;
      if (n[0]>tmp)
      {
        n[1]=n[0];
        n[0]=tmp;
      }
      else n[1]=tmp;
    }
    else n[2]=tmp;
  }
  return exc;
}

//check type of n===================================//
int subtype(int n[], int type)
{
  if (type==2)
  {
    //1: ss; 2: sp; 3: pp==============================//
    if (n[0]>n[1]) SWAP(n[0],n[1]);
    if (n[1]<=nstar) return 1;
    else if (n[0]>nstar) return 3;
    else if (n[0]<=nstar&&n[1]>nstar) return 2;
  }
  else if (type==3)
  {
    //4: sss; 5: ssp; 6: pss; 7: psp; 8: spp; 9: ppp======//
    if (n[1]>n[2]) SWAP(n[1],n[2]);
    if (n[0]<=nstar&&n[2]<=nstar) return 4;
    else if (n[0]<=nstar&&n[1]<=nstar&&n[2]>nstar) return 5;
    else if (n[0]>nstar&&n[2]<=nstar) return 6;
    else if (n[0]>nstar&&n[1]<=nstar&&n[2]>nstar) return 7;
    else if (n[0]<=nstar&&n[1]>nstar) return 8;
    else return 9;
  }
  else 
  {
    //10: ssss; 11: sssp; 12: spsp; 13: sspp; 14: sppp; 15: pppp
    if (n[0]>n[1]) SWAP(n[0],n[1]);
    if (n[2]>n[3]) SWAP(n[2],n[3]);
    if (n[1]<=nstar&&n[3]<=nstar) return 10;
    else if (n[1]<=nstar&&n[2]<=nstar&&n[3]>nstar) return 11;
    else if (n[0]<=nstar&&n[1]>nstar&&n[2]<=nstar&&n[3]>nstar) return 12;
    else if (n[1]<=nstar&&n[2]>nstar) return 13;
    else if (n[0]<=nstar&&n[1]>nstar&&n[2]>nstar) return 14;
    else return 15;
  }
  return 0;
}

//check whether n1 is equal to n2===================//
bool matchname(int n1[], int n2[], int type)
{
  for (int i=0;i<type;i++)
    if (n1[i]!=n2[i]) return 0;
  return 1;
}

//check whether sorted name n related event ========//
bool check(std::deque<cepair> &hdeque, int &index, int n[], int type)
{
  index=hdeque.size();
#ifdef DEBUG
  std::cout<<"LW_CE: check: deque size ="<<index<<std::endl;
#endif  
  if (!index)
  {
    cepair tmp;
    hdeque.push_back(tmp);
    return 0;
  }
  else
  {
    while (index>0)
    {
      index--;
      if (matchname(hdeque[index].sn,n,type))
        return 1;
    }
    cepair tmp;
    hdeque.push_back(tmp);
    index=hdeque.size()-1;
    return 0;
  }
}

//continue: still need to change input pars to array//
//          need to sort the name===================//
void storece_(int *n1, int *n2, int *n3, int *n4, double mass[], double *x, double *xdot, double *t)
{
#ifdef DEBUG
  if (*n1==0||*n2==0)
  {
    std::cout<<"LW_CE: Fine name=0";
    return;
  }
#endif  
  //Determine which type to store=====================//
  int type=4;
  if (*n3==0) type=2;
  else if (*n4==0) type=3;
#ifdef DEBUG
  std::cout<<"LW_CE: type: "<<type<<"\n";
#endif  
  
  //Define index for static first array===============//
  int ti=type-2;

  //Declare new pars==================================//
  Double_t semi, eng, ecc, peri, m1, m2, msys, bip, vinf, vp;
  int *name=new int[type];    //Unsort name
  int *sn=new int[type];      //sort name
  bool exc=0;
  name[0]=sn[0]=*n1;
  name[1]=sn[1]=*n2;
  if (type==3) {
    name[2]=sn[2]=*n3;
    m1=mass[0];
    m2=mass[1]+mass[2];
    exc=sort3(sn);
  }
  if (type==4) {
    name[2]=sn[2]=*n3;
    name[3]=sn[3]=*n4;
    m1=mass[0]+mass[1];
    m2=mass[2]+mass[3];
    exc=sort4(sn);
  }
  if (type==2) {
    m1=mass[0];
    m2=mass[1];
    exc=sort2(sn);
  }
  msys=m1+m2;
#ifdef DEBUG
  std::cout<<"LW_CE: name: ";
  for (int i=0;i<type;i++) std::cout<<name[i]<<"\t("<<sn[i]<<")\t";
  std::cout<<std::endl;
#endif
  
  if (matchname(sn,bname[ti],type))
  {
#ifdef DEBUG
    std::cout<<"LW_CE: match: match last one\n";
#endif
    cal_pars(m1,m2,msys,x,xdot,eng,semi,ecc,peri);
    cal_more(msys,semi,ecc,bip,vinf,vp);
#ifdef DEBUG
    std::cout<<"LW_CE: calculate: semi="<<semi<<"\teng="<<eng<<"\tecc="<<ecc<<"\tperi"<<peri<<"\tt="<<*t<<"\n";
#endif      
    if (ecc<b[ti][bi[ti][0]][bi[ti][1]].ecc[1])
    {
      b[ti][bi[ti][0]][bi[ti][1]].store(1,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
      b[ti][bi[ti][0]][bi[ti][1]].store(2,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
    }
    else b[ti][bi[ti][0]][bi[ti][1]].store(2,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
  }
  else
  {
    bi[ti][0]=sn[0]/SUBDIV;
    for (int i=0;i<type;i++)
      bname[ti][i]=sn[i];
    if (check(b[ti][bi[ti][0]],bi[ti][1],sn,type))
    {
#ifdef DEBUG
      std::cout<<"LW_CE: check succesful: last store: "<<bi[ti][0]<<" "<<bi[ti][1]<<"\n";
#endif
      cal_pars(m1,m2,msys,x,xdot,eng,semi,ecc,peri);
      cal_more(msys,semi,ecc,bip,vinf,vp);
#ifdef DEBUG
      std::cout<<"LW_CE: calculate: semi="<<semi<<"\teng="<<eng<<"\tecc="<<ecc<<"\tperi"<<peri<<"\tt="<<*t<<"\n";
#endif      
      if (ecc<b[ti][bi[ti][0]][bi[ti][1]].ecc[1])
      {
#ifdef DEBUG
        std::cout<<"LW_CE: calculate: status new, store smaller one\n";
#endif        
        b[ti][bi[ti][0]][bi[ti][1]].store(1,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
        b[ti][bi[ti][0]][bi[ti][1]].store(2,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
      }
      else b[ti][bi[ti][0]][bi[ti][1]].store(2,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
      if (!b[ti][bi[ti][0]][bi[ti][1]].exchange&&exc) b[ti][bi[ti][0]][bi[ti][1]].exchange=1;
#ifdef DEBUG
      std::cout<<"LW_CE: calculate: exchange="<<b[ti][bi[ti][0]][bi[ti][1]].exchange<<std::endl;
#endif      
    }
    else
    {
      std::cout<<"LW_CE: new encouter find: name = ";
      for (int j=0;j<type;j++) std::cout<<"\t"<<name[j];
      std::cout<<std::endl;
#ifdef DEBUG
      std::cout<<"LW_CE: check no match, new store: "<<bi[ti][0]<<" "<<bi[ti][1]<<"\n";
#endif      
      b[ti][bi[ti][0]][bi[ti][1]].init(type,name,mass,sn);
      b[ti][bi[ti][0]][bi[ti][1]].type=subtype(name,type);
      counts[b[ti][bi[ti][0]][bi[ti][1]].type-1]++;
      b[ti][bi[ti][0]][bi[ti][1]].exchange=0;
      cal_pars(m1,m2,msys,x,xdot,eng,semi,ecc,peri);
      cal_more(msys,semi,ecc,bip,vinf,vp);
#ifdef DEBUG
      std::cout<<"LW_CE: calculate: semi="<<semi<<"\teng="<<eng<<"\tecc="<<ecc<<"\tperi"<<peri<<"\tt="<<*t<<"\n";
#endif      
      b[ti][bi[ti][0]][bi[ti][1]].store(0,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
      b[ti][bi[ti][0]][bi[ti][1]].store(1,x,xdot,ecc,peri,semi,eng,*t,bip,vinf,vp);
    }
  }
#ifdef DEBUG
  std::cout<<"LW_CE: size of b["<<ti<<"]["<<bi[ti][0]<<"] = "<<b[ti][bi[ti][0]].size()<<std::endl;
#endif  
}

void endstore_()
{
#ifdef DEBUG
  std::cout<<"LW_CE: end store\n";
  std::cout<<"LW_CE: show unit: rbar="<<rbar<<"\tzmbar="<<zmbar<<"\tstar="<<tstar<<"\trau"<<rau<<"\tvstar"<<vstar<<std::endl;
#endif  
  //std::string typen[15]={"ss","sp","pp","sss","ssp","pss","psp","spp","ppp","ssss","sssp","spsp","sspp","sppp","pppp"};
  TFile *f=new TFile("ce.root","create");
  f->cd();
  TTree *ntree=new TTree("ce","close encounter events");
  TTree *unit=new TTree("unit","unit transformation pars");
  Double_t x[3][3], v[3][3], m[4], ecc[3], peri[3], semi[3], t[3], E[3];
  Double_t vinf[3], vp[3], bip[3];
  Double_t rrau, rrbar, ttstar, zzmbar, vvstar;
  Bool_t exchange;
  Int_t name[4], type;
  ntree->Branch("name",name,"name[4]/I");
  ntree->Branch("type",&type,"type/I");
  ntree->Branch("t",t,"t[3]/D");
  ntree->Branch("x",x,"x[3][3]/D");
  ntree->Branch("v",v,"v[3][3]/D");
  ntree->Branch("m",m,"m[4]/D");
  ntree->Branch("ecc",ecc,"ecc[3]/D");
  ntree->Branch("peri",peri,"peri[3]/D");
  ntree->Branch("semi",semi,"semi[3]/D");
  ntree->Branch("exchange",&exchange);
  ntree->Branch("E",E,"E[3]/D");
  ntree->Branch("bip",bip,"bip[3]/D");
  ntree->Branch("vinf",vinf,"vinf[3]/D");
  ntree->Branch("vp",vp,"vp[3]/D");
  unit->Branch("rau",&rrau);
  unit->Branch("rbar",&rrbar);
  unit->Branch("tstar",&ttstar);
  unit->Branch("zmbar",&zzmbar);
  unit->Branch("vstar",&vvstar);
  rrau=rau;
  rrbar=rbar;
  ttstar=tstar;
  zzmbar=zmbar;
  vvstar=vstar;
  unit->Fill();
  for (int i=0;i<3;i++)
    for (int j=0;j<NVOL;j++)
      for (unsigned int k=0;k<b[i][j].size();k++)
      {
        b[i][j][k].out(name,type,x,v,m,ecc,peri,semi,E,t,exchange,vinf,vp,bip);
        ntree->Fill();
      }
  ntree->Write("",TObject::kOverwrite);
  unit->Write("",TObject::kOverwrite);
}
