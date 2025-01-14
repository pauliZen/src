//Version 3//
//Calculate the delat E and delta L for stars=======//
//store the result in new tree in -result-dET.root==//
//   Using indexbuilding instead of entrylist       //
//   Time cost mostly in search change (if...)      //
//   ready for splited index                        //
//   For twice match, use last change point data    //
//Command: [pro.] [rootname] [nrootname] [treename] [newtreename]     //
//         [newtreetitle] [logname] [bhindex1] [bhindex2] [twicelog]  //
//         [faillog]                                                  //
//Input: rootname: result root file name===================//
//       nrootname: the name of new root to store new tree=//
//       newrootname: new tree store root file name========//
//       treename: tree name to store eject stars data=====//
//       newtreename: new tree name store new analysis data//
//       newtreetitle: title for new tree==================//
//       logfile: logfile with star list index=============//
//                (should remove black hole index)=========//
//       bhindex1/2: bh index==============================//
//       twicelog: twice match log file name===============//
//       faillog: fail match log file name=================//
//Notes!: rootname do not need suffix===============//
//        nrootname should be fullname==============//
//Tree:   ==========================================//
//     t: time_cur(in),time_cur(out), dt
//     En: e_in, de
//     En_err: e_err_in,e_err_out
//     mass: mass
//     Ls[io]: Ls_x,Ls_y,Ls_z,Ls_r,Ls_alpha,Ls_delta (in/out)
//     Lbh[io]: Lbh_x,Lbh_y,Lbh_z,Lbh_r,Lbh_alpha,Lbh_delta (in/out)
//     r[id]: r,x,y,z(in/d)
//     rb[id]: rb,xb,yb,zb(in/d)
//     v[id]: v,vx,vy,vz(in/d)
//     vb[id]: vb,vbx,vby,vbz(in/d)
//     pot[id]: pot,pots(in/d)
//     a[id]: ax,ay,az,asx,asy,asz(in/d)

#define TStepCheck 10
#define TCheckNum 3

#include <iomanip>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "uftools.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TEntryList.h"
#include "TCut.h"

using namespace std;

int main(int argc, char* argv[])
{
  //variables=========================================//
  string rootname;
  string nrootname;
  string treename;
  string newtreename;
  string newtreetitle;
  string logname;
  string twicelog;
  string faillog;
  string bhindex[2];
  stringstream namestr;
  string checksh;
  char inflagc='y';
  bool inflag=1;

  switch (argc)
  {
  case 1:
    cout<<"Load last input(y/n)?";
    cin>>inflagc;
    if (inflagc=='n')
      inflag=0;
    if (inflag)
    {
      ifstream configf(".star-delta-energy.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>nrootname;
        configf>>treename;
        configf>>newtreename;
        configf>>newtreetitle;
        configf>>logname;
        configf>>bhindex[0];
        configf>>bhindex[1];
        configf>>twicelog;
        configf>>faillog;
        configf.close();
      }
    }
    
    //input=============================================//
    cout<<"root name("<<rootname<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input root name(no suffix):";
      cin>>rootname;
    }
    cout<<"new root name("<<nrootname<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input root name(no suffix):";
      cin>>nrootname;
    }
    cout<<"Tree name("<<treename<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Tree name:";
      cin>>treename;
    }
    cout<<"New tree name("<<newtreename<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
    cout<<"New Tree name:";
    cin>>newtreename;
    }
    cout<<"New Tree title("<<newtreetitle<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input New Tree title(no space):";
      cin>>newtreetitle;
    }
    cout<<"Index log name("<<logname<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input index log name:";
      cin>>logname;
    }
    cout<<"black hole index("<<bhindex[0]<<", "<<bhindex[1]<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input black hole index 1:";
      cin>>bhindex[0];
      cout<<"Input black hole index 2:";
      cin>>bhindex[1];
    }
    cout<<"twice match log filename("<<twicelog<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input twicelog name:";
      cin>>twicelog;
    }
    cout<<"fail match log filename("<<faillog<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input faillog name:";
      cin>>faillog;
    }
    break;
  case 2:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>checksh;
    if (checksh=="-l")
    {
      ifstream configf(".star-delta-energy.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>nrootname;
        configf>>treename;
        configf>>newtreename;
        configf>>newtreetitle;
        configf>>logname;
        configf>>bhindex[0];
        configf>>bhindex[1];
        configf>>twicelog;
        configf>>faillog;
        configf.close();
      }
    }
    else
    {
      cout<<"input incomplete"<<endl;
      return 0;
    }
    break;
  case 11:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>rootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[2];
    namestr>>nrootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[3];
    namestr>>treename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[4];
    namestr>>newtreename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[5];
    namestr>>newtreetitle;
    namestr.str("");
    namestr.clear();
    namestr<<argv[6];
    namestr>>logname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[7];
    namestr>>bhindex[0];
    namestr.str("");
    namestr.clear();
    namestr<<argv[8];
    namestr>>bhindex[1];
    namestr.str("");
    namestr.clear();
    namestr<<argv[9];
    namestr>>twicelog;
    namestr.str("");
    namestr.clear();
    namestr<<argv[10];
    namestr>>faillog;
    break;
  default:
    cout<<"input incomplete"<<endl;
    return 0;
    break;
  }

  ofstream outconf(".star-delta-energy.conf");
  outconf<<rootname<<endl;
  outconf<<nrootname<<endl;
  outconf<<treename<<endl;
  outconf<<newtreename<<endl;
  outconf<<newtreetitle<<endl;
  outconf<<logname<<endl;
  outconf<<bhindex[0]<<endl;
  outconf<<bhindex[1]<<endl;
  outconf<<twicelog<<endl;
  outconf<<faillog<<endl;
  outconf.close();

  rootname +="-result.root";
  cout<<rootname<<":"<<treename<<"->"<<nrootname<<":"<<newtreename<<"("<<newtreetitle<<")"<<endl;
  cout<<"star index:"<<logname<<"; bh index:"<<bhindex[0]<<", "<<bhindex[1]<<endl;
  cout<<"Twice logfile:"<<twicelog<<"; fail logfile:"<<faillog<<endl;

  //analysis==========================================//
  TFile *f1=new TFile(rootname.c_str(),"update");
  TFile *f=new TFile(nrootname.c_str(),"update");
  f->cd();
  
  //new tree==========================================//
  //t: time_cur_in,time_cur_out, dt
  //En: e_in, de
  //En_err: e_err_in,e_err_out
  //mass: mass
  //Ls[io]: Ls_x,Ls_y,Ls_z,Ls_r,Ls_alpha,Ls_delta (in/out)
  //Lbh[io]: Lbh_x,Lbh_y,Lbh_z,Lbh_r,Lbh_alpha,Lbh_delta (in/out)
  //r[id]: r,x,y,z(in/d)
  //rb[id]: rb,xb,yb,zb(in/d)
  //v[id]: v,vx,vy,vz(in/d)
  //vb[id]: vb,vbx,vby,vbz(in/d)
  //pot[id]: pot,pots(in/d)
  //a[id]: ax,ay,az,asx,asy,asz(in/d)

  TTree *ntree=new TTree (newtreename.c_str(),newtreetitle.c_str());
  Double_t t[3],En[2],En_err[2],mass;
  Double_t Lsi[6],Lbhi[6],Lso[6],Lbho[6],Lsi_err[TCheckNum][6],Lso_err[TCheckNum][6];
  Double_t Lsi_mean[TCheckNum][6],Lso_mean[TCheckNum][6];
  Double_t ri[4],rbi[4],vi[4],vbi[4],poti[2],ai[6];
  Double_t rd[4],rbd[4],vd[4],vbd[4],potd[2],ad[6];
  Double_t bh12i[3],bh12o[3],lbh12[3];
  Int_t index;
  // new parameters===================================//
  ntree->Branch("t",t,"t[3]/D");
  ntree->Branch("En",En,"En[2]/D");
  ntree->Branch("En_err",En_err,"En_err[2]/D");
  // angular momentum ==============================//
  ntree->Branch("Lsi",Lsi,"Lsi[6]/D");
  ntree->Branch("Lsi_mean",Lsi_mean,("Lsi_mean["+to<std::string>(TCheckNum)+"][6]/D").c_str());
  ntree->Branch("Lsi_err",Lsi_err,("Lsi_err["+to<std::string>(TCheckNum)+"][6]/D").c_str());
  ntree->Branch("Lbhi",Lbhi,"Lbhi[6]/D");
  ntree->Branch("Lso",Lso,"Lso[6]/D");
  ntree->Branch("Lso_mean",Lso_mean,("Lso_mean["+to<std::string>(TCheckNum)+"][6]/D").c_str());
  ntree->Branch("Lso_err",Lso_err,("Lso_err["+to<std::string>(TCheckNum)+"][6]/D").c_str());
  ntree->Branch("Lbho",Lbho,"Lbho[6]/D");
  // inherit before eject=============================//
  ntree->Branch("index",&index);
  ntree->Branch("mass",&mass);  
  ntree->Branch("ri",ri,"ri[4]/D");
  ntree->Branch("rbi",rbi,"rbi[4]/D");
  ntree->Branch("vi",vi,"vi[4]/D");
  ntree->Branch("vbi",vbi,"vbi[4]/D");
  ntree->Branch("poti",poti,"poti[2]/D");
  ntree->Branch("ai",ai,"ai[6]/D");
  // variance after eject=============================//
  ntree->Branch("rd",rd,"rd[4]/D");
  ntree->Branch("rbd",rbd,"rbd[4]/D");
  ntree->Branch("vd",vd,"vd[4]/D");
  ntree->Branch("vbd",vbd,"vbd[4]/D");
  ntree->Branch("potd",potd,"potd[2]/D");
  ntree->Branch("ad",ad,"ad[6]/D");
  ntree->Branch("bh12i",bh12i,"bh12i[3]/D");
  ntree->Branch("bh12o",bh12o,"bh12o[3]/D");

  // open treename====================================//
  TTree *ftree=(TTree*)(f1->Get(treename.c_str()));
  Double_t mass1,time_cur1,x1,y1,z1,r1,xb1,yb1,zb1,rb1;
  Double_t vx1,vy1,vz1,v1,vbx1,vby1,vbz1,vb1,pot1,pots1;
  Double_t etot1,ax1,ay1,az1,asx1,asy1,asz1;
  Double_t lx,ly,lz,lr,la,ld;
  Int_t index1;
  ftree->SetBranchAddress("index",&index1);
  ftree->SetBranchAddress("mass",&mass1);
  ftree->SetBranchAddress("time_cur",&time_cur1);
  ftree->SetBranchAddress("x",&x1);
  ftree->SetBranchAddress("y",&y1);
  ftree->SetBranchAddress("z",&z1);
  ftree->SetBranchAddress("r",&r1);
  ftree->SetBranchAddress("vx",&vx1);
  ftree->SetBranchAddress("vy",&vy1);
  ftree->SetBranchAddress("vz",&vz1);
  ftree->SetBranchAddress("v",&v1);
  ftree->SetBranchAddress("xb",&xb1);
  ftree->SetBranchAddress("yb",&yb1);
  ftree->SetBranchAddress("zb",&zb1);
  ftree->SetBranchAddress("rb",&rb1);
  ftree->SetBranchAddress("vbx",&vbx1);
  ftree->SetBranchAddress("vby",&vby1);
  ftree->SetBranchAddress("vbz",&vbz1);
  ftree->SetBranchAddress("vb",&vb1);
  ftree->SetBranchAddress("pot",&pot1);
  ftree->SetBranchAddress("pots",&pots1);
  ftree->SetBranchAddress("ax",&ax1);
  ftree->SetBranchAddress("ay",&ay1);
  ftree->SetBranchAddress("az",&az1);
  ftree->SetBranchAddress("asx",&asx1);
  ftree->SetBranchAddress("asy",&asy1);
  ftree->SetBranchAddress("asz",&asz1);
  ftree->SetBranchAddress("etot",&etot1);
  ftree->SetBranchAddress("Lx",&lx);
  ftree->SetBranchAddress("Ly",&ly);
  ftree->SetBranchAddress("Lz",&lz);
  ftree->SetBranchAddress("Lr",&lr);
  ftree->SetBranchAddress("Lalpha",&la);
  ftree->SetBranchAddress("Ldelta",&ld);
  ftree->SetBranchAddress("lbh12",lbh12);

  // data calculation=================================//
  ifstream orgdata(logname.c_str());
  
  if (!orgdata.is_open())
  {
    cout<<"No log file."<<endl;
    return 0;
  }
  else
  {
    ofstream twicedata(twicelog.c_str());
    ofstream faildata(faillog.c_str());

    // rebuild index of tree============================//
    ftree->BuildIndex("index","time_cur");
    
    // Get entrynum for each index======================//
    Int_t entrynum=ftree->GetEntries(("index=="+bhindex[1]).c_str());
    // Define useful variables==========================//
    Double_t **lstore=new Double_t*[6];
    for (int j=0;j<6;j++) lstore[j]=new Double_t[entrynum];
    Double_t *estore=new Double_t[entrynum];
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    Int_t bhI;
    sstr<<bhindex[0];
    sstr>>bhI;
    Int_t sindex=-1;
    Int_t sindex_temp;

    while (!orgdata.eof())
    {
      bool match=0;
      Double_t emean=0;
      Double_t lmean[TCheckNum][6];
      Double_t lmeanas[TCheckNum];
      Int_t itriger=0;
      //lwang-debug=======================================//
      //Notes: the last event repeat twices!, try to rm===//
      sindex_temp=sindex;
      orgdata>>sindex;
      if (sindex==sindex_temp)
        continue;
      //lwang-debug-end===================================//
      ftree->GetEntryWithIndex(sindex,0);
      estore[0]=etot1;
      lstore[0][0]=lx;
      lstore[1][0]=ly;
      lstore[2][0]=lz;
      lstore[3][0]=lr;
      lstore[4][0]=la;
      lstore[5][0]=ld;
      // check each index one by one======================//
      for (Int_t i=1;i<entrynum;i++)
      {
        ftree->GetEntryWithIndex(sindex,i);
        estore[i]=etot1;
        lstore[0][i]=lx;
        lstore[1][i]=ly;
        lstore[2][i]=lz;
        lstore[3][i]=lr;
        lstore[4][i]=la;
        lstore[5][i]=ld;
        if (etot1-estore[i-1]>1*mass1)
        {
          if (match)
          {
            cout<<"warning!:"<<sindex<<" match twice!"<<endl;
            twicedata<<sindex<<endl;
            // match=0;
            // break;
          }
          match=1;
          itriger=i;
          emean=0;
          for (Int_t j=0;j<i;j++)
            emean +=estore[i];
          emean /=(Double_t)i;
          En_err[0]=0;
          for (Int_t j=0;j<i;j++)
            En_err[0] +=pow((estore[i]-emean),2);
          En_err[0] /=(Double_t)i;
          En_err[0] = sqrt(En_err[0]);
          //L err before calculation==========================//
          for (int j=0;j<TCheckNum;j++)
          {
            lmeanas[j]=0;
            for (int jj=0;jj<6;jj++)
            {
              lmean[j][jj]=0;
              Lsi_err[j][jj]=0;
            }
          }
          bool overange=0;
          for (int j=1;j<=TCheckNum;j++)
          {
            Int_t ji=j-1;
            Int_t jb=ji-1;
            if (j*TStepCheck>i)
            {
              if (overange)
                for (int jj=0;jj<6;jj++)
                {
                  Lsi_mean[ji][jj]=Lsi_mean[jb][jj];
                  Lsi_err[ji][jj] =Lsi_err[jb][jj];
                }
              else
              {
                overange=1;
                if (j>1)
                {
                  for (Int_t jj=0;jj<4;jj++) lmean[ji][jj] +=lmean[jb][jj];
                  lmeanas[ji] +=lmeanas[jb];
                }
                Int_t jjs=i-ji*TStepCheck;
                for (Int_t jj=0;jj<4;jj++)
                {
                  for (Int_t jjj=0;jjj<jjs;jjj++) lmean[ji][jj] +=lstore[jj][jjj];
                  Lsi_mean[ji][jj]=lmean[ji][jj];
                  Lsi_mean[ji][jj] /=(Double_t)i;
                  for (Int_t jjj=0;jjj<i;jjj++) Lsi_err[ji][jj] +=pow((lstore[jj][jjj]-Lsi_mean[ji][jj]),2);
                  Lsi_err[ji][jj] /=(Double_t)i;
                  Lsi_err[ji][jj] =sqrt(Lsi_err[ji][jj]);
                }
                Double_t lxy=Lsi_mean[ji][0]*Lsi_mean[ji][0]+Lsi_mean[ji][1]*Lsi_mean[ji][1];
                Double_t lr=lxy+Lsi_mean[ji][2]*Lsi_mean[ji][2];
                Double_t dlxy2=fabs(Lsi_mean[ji][0])*Lsi_err[ji][0]+fabs(Lsi_mean[ji][1])*Lsi_err[ji][1];
                Double_t dlr2=dlxy2+fabs(Lsi_mean[ji][2])*Lsi_err[ji][2];
                dlxy2=0.25*dlxy2*dlxy2/(lxy*lxy);
                dlr2=0.25*dlr2*dlr2/(lr*lr);
                lxy=sqrt(lxy);
                lr=sqrt(lr);
                if (Lsi_mean[ji][1]>0) Lsi_mean[ji][4]=acos(Lsi_mean[ji][0]/lxy);
                else Lsi_mean[ji][4]=2*3.1415926-acos(Lsi_mean[ji][0]/lxy);
                Lsi_mean[ji][5]=Lsi_mean[ji][2]/lr;
                Lsi_err[ji][4]=Lsi_mean[ji][4]*sqrt(pow(Lsi_err[ji][0]/(Lsi_mean[ji][0]),2)+dlxy2);
                Lsi_err[ji][5]=Lsi_mean[ji][5]*sqrt(pow(Lsi_err[ji][2]/(Lsi_mean[ji][2]),2)+dlr2);
              }
            }
            else
            {
              if (j>1)
              {
                for (Int_t jj=0;jj<6;jj++)  lmean[ji][jj] +=lmean[jb][jj];
                lmeanas[ji] +=lmeanas[jb];
              }
              Int_t jjs=i-ji*TStepCheck;
              Int_t jjb=i-j*TStepCheck;
              Double_t jinter=j*TStepCheck;
              for (Int_t jj=0;jj<4;jj++)
              {
                for (Int_t jjj=jjb;jjj<jjs;jjj++) lmean[ji][jj] +=lstore[jj][jjj];
                Lsi_mean[ji][jj]=lmean[ji][jj];
                Lsi_mean[ji][jj] /=jinter;
                for (Int_t jjj=jjb;jjj<i;jjj++) Lsi_err[ji][jj] +=pow((lstore[jj][jjj]-Lsi_mean[ji][jj]),2);
                Lsi_err[ji][jj] /=jinter;
                Lsi_err[ji][jj] =sqrt(Lsi_err[ji][jj]);
              }
              Double_t lxy=Lsi_mean[ji][0]*Lsi_mean[ji][0]+Lsi_mean[ji][1]*Lsi_mean[ji][1];
              Double_t lr=lxy+Lsi_mean[ji][2]*Lsi_mean[ji][2];
              Double_t dlxy2=fabs(Lsi_mean[ji][0])*Lsi_err[ji][0]+fabs(Lsi_mean[ji][1])*Lsi_err[ji][1];
              Double_t dlr2=dlxy2+fabs(Lsi_mean[ji][2])*Lsi_err[ji][2];
              dlxy2=0.25*dlxy2*dlxy2/(lxy*lxy);
              dlr2=0.25*dlr2*dlr2/(lr*lr);
              lxy=sqrt(lxy);
              lr=sqrt(lr);
              if (Lsi_mean[ji][1]>0) Lsi_mean[ji][4]=acos(Lsi_mean[ji][0]/lxy);
              else Lsi_mean[ji][4]=2*3.1415926-acos(Lsi_mean[ji][0]/lxy);
              Lsi_mean[ji][5]=Lsi_mean[ji][2]/lr;
              Lsi_err[ji][4]=Lsi_mean[ji][4]*sqrt(pow(Lsi_err[ji][0]/(Lsi_mean[ji][0]),2)+dlxy2);
              Lsi_err[ji][5]=Lsi_mean[ji][5]*sqrt(pow(Lsi_err[ji][2]/(Lsi_mean[ji][2]),2)+dlr2);
            }
          }
          
          //Copy pars before eject============================//
          ftree->GetEntryWithIndex(sindex,i-1);
          index=index1;
          t[0]=time_cur1;
          mass=mass1;
          ri[1]=x1;
          ri[2]=y1;
          ri[3]=z1;
          ri[0]=r1;
          rbi[1]=xb1;
          rbi[2]=yb1;
          rbi[3]=zb1;
          rbi[0]=rb1;
          vi[1]=vx1;
          vi[2]=vy1;
          vi[3]=vz1;
          vi[0]=v1;
          vbi[1]=vbx1;
          vbi[2]=vby1;
          vbi[3]=vbz1;
          vbi[0]=vb1;
          poti[0]=pot1;
          poti[1]=pots1;
          En[0]=etot1;
          ai[0]=ax1;
          ai[1]=ay1;
          ai[2]=az1;
          ai[3]=asx1;
          ai[4]=asy1;
          ai[5]=asz1;
          bh12i[0]=lbh12[0];
          bh12i[1]=lbh12[1];
          bh12i[2]=lbh12[2];
          //Angular momentum calculation======================//
          Lsi[0]=lx;
          Lsi[1]=ly;
          Lsi[2]=lz;
          Lsi[3]=lr;
          Lsi[4]=la;
          Lsi[5]=ld;
            
          //Calculate change of all pars======================//
          ftree->GetEntryWithIndex(sindex,i);
          t[2]=time_cur1-t[0];
          t[1]=time_cur1;
          rd[1]=x1-ri[1];
          rd[2]=y1-ri[2];
          rd[3]=z1-ri[3];
          rd[0]=sqrt(rd[1]*rd[1]+rd[2]*rd[2]+rd[3]*rd[3]);
          rbd[1]=xb1-rbi[1];
          rbd[2]=yb1-rbi[2];
          rbd[3]=zb1-rbi[3];
          rbd[0]=sqrt(rbd[1]*rbd[1]+rbd[2]*rbd[2]+rbd[3]*rbd[3]);
          vd[1]=vx1-vi[1];
          vd[2]=vy1-vi[2];
          vd[3]=vz1-vi[3];
          vd[0]=sqrt(vd[1]*vd[1]+vd[2]*vd[2]+vd[3]*vd[3]);
          vbd[1]=vbx1-vbi[1];
          vbd[2]=vby1-vbi[2];
          vbd[3]=vbz1-vbi[3];
          vbd[0]=sqrt(vbd[1]*vbd[1]+vbd[2]*vbd[2]+vbd[3]*vbd[3]);
          potd[0]=pot1-poti[0];
          potd[1]=pots1-poti[1];
          En[1]=etot1-En[0];
          ad[0]=ax1-ai[0];
          ad[1]=ay1-ai[1];
          ad[2]=az1-ai[2];
          ad[3]=asx1-ai[3];
          ad[4]=asy1-ai[4];
          ad[5]=asz1-ai[5];
          bh12o[0]=lbh12[0];
          bh12o[1]=lbh12[1];
          bh12o[2]=lbh12[2];
          //Angular momentum calculation======================//
          Lso[0]=lx;
          Lso[1]=ly;
          Lso[2]=lz;
          Lso[3]=lr;
          Lso[4]=la;
          Lso[5]=ld;
        }
      }
      if (match)
      {
        cout<<"index "<<sindex<<" match successful"<<endl;
        emean=0;
        for (Int_t j=itriger;j<entrynum;j++)
            emean +=estore[j];
        emean /=(Double_t)entrynum-itriger+1;
        En_err[1]=0;
        for (Int_t j=itriger;j<entrynum;j++)
          En_err[1] +=pow((estore[j]-emean),2);
        En_err[1] /=(Double_t)entrynum-itriger+1;
        En_err[1] =sqrt(En_err[1]);

        //calculte L-err after eject========================//
        for (int j=0;j<TCheckNum;j++)
        {
          lmeanas[j]=0;
          for (int jj=0;jj<6;jj++)
          {
            lmean[j][jj]=0;
            Lso_err[j][jj]=0;
          }
        }
        bool overange=0;
        for (int j=1;j<=TCheckNum;j++)
        {
          Int_t ji=j-1;
          Int_t jb=ji-1;
          if (j*TStepCheck+itriger>entrynum)
          {
            if (overange)
              for (int jj=0;jj<6;jj++)
              {
                Lso_mean[ji][jj]=Lso_mean[jb][jj];
                Lso_err[ji][jj] =Lso_err[jb][jj];
              }
            else
            {
              overange=1;
              if (j>1)
              {
                for (Int_t jj=0;jj<6;jj++) lmean[ji][jj] +=lmean[jb][jj];
                lmeanas[ji] +=lmeanas[jb];
              }
              Int_t jjb=itriger+ji*TStepCheck;
              Double_t jinter=entrynum-itriger;
              for (Int_t jj=0;jj<4;jj++)
              {
                for (Int_t jjj=jjb;jjj<entrynum;jjj++) lmean[ji][jj] +=lstore[jj][jjj];
                Lso_mean[ji][jj]=lmean[ji][jj];
                Lso_mean[ji][jj] /=jinter;
                for (Int_t jjj=itriger;jjj<entrynum;jjj++) Lso_err[ji][jj] +=pow((lstore[jj][jjj]-Lso_mean[ji][jj]),2);
                Lso_err[ji][jj] /=jinter;
                Lso_err[ji][jj] =sqrt(Lso_err[ji][jj]);
              }
              Double_t lxy=Lso_mean[ji][0]*Lso_mean[ji][0]+Lso_mean[ji][1]*Lso_mean[ji][1];
              Double_t lr=lxy+Lso_mean[ji][2]*Lso_mean[ji][2];
              Double_t dlxy2=fabs(Lso_mean[ji][0])*Lso_err[ji][0]+fabs(Lso_mean[ji][1])*Lso_err[ji][1];
              Double_t dlr2=dlxy2+fabs(Lso_mean[ji][2])*Lso_err[ji][2];
              dlxy2=0.25*dlxy2*dlxy2/(lxy*lxy);
              dlr2=0.25*dlr2*dlr2/(lr*lr);
              lxy=sqrt(lxy);
              lr=sqrt(lr);
              if (Lso_mean[ji][1]>0) Lso_mean[ji][4]=acos(Lso_mean[ji][0]/lxy);
              else Lso_mean[ji][4]=2*3.1415926-acos(Lso_mean[ji][0]/lxy);
              Lso_mean[ji][5]=Lso_mean[ji][2]/lr;
              Lso_err[ji][4]=Lso_mean[ji][4]*sqrt(pow(Lso_err[ji][0]/(Lso_mean[ji][0]),2)+dlxy2);
              Lso_err[ji][5]=Lso_mean[ji][5]*sqrt(pow(Lso_err[ji][2]/(Lso_mean[ji][2]),2)+dlr2);
            }
          }
          else
          {
            if (j>1)
            {
              for (Int_t jj=0;jj<6;jj++)  lmean[ji][jj] +=lmean[jb][jj];
              lmeanas[ji] +=lmeanas[jb];
            }
            Int_t jjs=itriger+j*TStepCheck;
            Int_t jjb=itriger+ji*TStepCheck;
            Double_t jinter=j*TStepCheck;
            for (Int_t jj=0;jj<4;jj++)
            {
              for (Int_t jjj=jjb;jjj<jjs;jjj++) lmean[ji][jj] +=lstore[jj][jjj];
              Lso_mean[ji][jj]=lmean[ji][jj];
              Lso_mean[ji][jj] /=jinter;
              for (Int_t jjj=itriger;jjj<jjs;jjj++) Lso_err[ji][jj] +=pow((lstore[jj][jjj]-Lso_mean[ji][jj]),2);
              Lso_err[ji][jj] /=jinter;
              Lso_err[ji][jj] =sqrt(Lso_err[ji][jj]);
            }
            Double_t lxy=Lso_mean[ji][0]*Lso_mean[ji][0]+Lso_mean[ji][1]*Lso_mean[ji][1];
            Double_t lr=lxy+Lso_mean[ji][2]*Lso_mean[ji][2];
            Double_t dlxy2=fabs(Lso_mean[ji][0])*Lso_err[ji][0]+fabs(Lso_mean[ji][1])*Lso_err[ji][1];
            Double_t dlr2=dlxy2+fabs(Lso_mean[ji][2])*Lso_err[ji][2];
            dlxy2=0.25*dlxy2*dlxy2/(lxy*lxy);
            dlr2=0.25*dlr2*dlr2/(lr*lr);
            lxy=sqrt(lxy);
            lr=sqrt(lr);
            if (Lso_mean[ji][1]>0) Lso_mean[ji][4]=acos(Lso_mean[ji][0]/lxy);
            else Lso_mean[ji][4]=2*3.1415926-acos(Lso_mean[ji][0]/lxy);
            Lso_mean[ji][5]=Lso_mean[ji][2]/lr;
            Lso_err[ji][4]=Lso_mean[ji][4]*sqrt(pow(Lso_err[ji][0]/(Lso_mean[ji][0]),2)+dlxy2);
            Lso_err[ji][5]=Lso_mean[ji][5]*sqrt(pow(Lso_err[ji][2]/(Lso_mean[ji][2]),2)+dlr2);
          }
        }

        //black hole angular momentum calculation===========//
        ftree->GetEntryWithIndex(bhI,t[0]);
        Lbhi[0]=lx;
        Lbhi[1]=ly;
        Lbhi[2]=lz;
        Lbhi[3]=lr;
        Lbhi[4]=la;
        Lbhi[5]=ld;
        ftree->GetEntryWithIndex(bhI,t[0]);
        Lbho[0]=lx;
        Lbho[1]=ly;
        Lbho[2]=lz;
        Lbho[3]=lr;
        Lbho[4]=la;
        Lbho[5]=ld;
        //Fill tree when match successfully=================//
        ntree->Fill();
      }
      else
      {
        cout<<"index "<<sindex<<" match fail"<<endl;
        faildata<<sindex<<endl;
      }
    }
    ntree->Write("",TObject::kOverwrite);
    cout<<"Finished"<<endl;
  }
  return 0;
}
