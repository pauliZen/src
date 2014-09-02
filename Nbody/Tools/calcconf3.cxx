#include <stdio.h>
#include <initial.h>
#include <nb6out3.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <omp.h>
#include <uftools.h>
#include <string>
#include <algorithm>
#ifdef USE_ROOT
#include <TH2F.h>
#include <TCanvas.h>
#endif

typedef float float2[2];
typedef int int3[3];

float distance (float x[3]) {
  return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
}

float dot (float x[3]) {
  return x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
}

int countindex(int i) {
  if(i/10) return countindex(i/10) + 1;
  else return 1;
}

std::string plus0(int i) {
  if(i--) return "0"+plus0(i);
  else return "";
}

std::string fileindex(int i, const int &imax) {
  int l=countindex(i);
  if (l>imax) return to<std::string>(i);
  else return plus0(imax-l)+to<std::string>(i);
}

struct mpair{
  float m[2];
  float & operator [] (int i) {return m[i];}
};

bool ismaller(mpair a,mpair b) {
  return a[0]<b[0];
}

bool ismaller_mass(particle6pp a, particle6pp b) {
  return a.mass<b.mass;
}

bool ismaller_r(particle6pp a, particle6pp b) {
  return dot(a.x)<dot(b.x);
}

int main(int argc, char *argv[]){
  pars_initial init(".calcmloss_config");
  init.add("dataname","data name to read","conf.3");
  init.add("off","offset for first line",(int)1);
  init.add("nmax","maximum particle number",(int)1000000);
  init.add("m0","read or write initial mass (1:read; 0: write - switch on calc_mloss to write)",(int)1);
  init.add("rtide","read tidal radius (suppressed by negative value)",(double)-1.0);
  init.add("calc_mloss","mloss calculation",(int)1);
  init.add("outmloss","output mloss file","mloss");
  init.add("calc_mm0","right now mass and initial mass",(int)1);
  init.add("outmm0","output mnow vs. minit file","mm0");
  init.add("calc_lagr","lagrange radii, average mass, number count, vrot, sigma r/t",(int)1);
  init.add("outlagr","output lagr file","lagr");
  init.add("calc_density","density profile",(int)1);
  init.add("outden","output density file","den");
  init.add("outdenb","output binary density file","denb");
  init.add("draw_density","mloss calculation",(int)0);
  init.initial(argc,argv);

  const int NMAX=init.geti("nmax");

  //Input data of conf.3==============================//

  particle6pp *data=new particle6pp[NMAX];
  header *h=new header;
  pars6pp *par=new pars6pp;
  bool sort_flag=false; //Whether data is sorted by distance
  
  FILE *fin;
  if ( (fin = fopen(init.gets("dataname").c_str(),"r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("dataname").c_str());
    return 0;
  }

  int off=init.geti("off");

  if(!readp6pp(NMAX,data,h,par,fin,true,off)) {
    perror("Error: NMAX too small!\n");
    return 0;
  }

  fclose(fin);
  
  //initial mass data read or write===================//
  float *mass0=NULL;  //Initial mass array
  int n0tot=0;         //Initial ntot
  double m0tot=0.;    //Initial total mass

  FILE *m0;
  bool m0r=init.geti("m0");
  if (m0r) {
    if ( (m0 = fopen("m0list.dat","r")) == NULL) {
      fprintf(stderr,"Error: Cannot open m0list.dat\n.");
      return 0;
    }
    fread(&n0tot,sizeof(int),1,m0);
    fread(&m0tot,sizeof(double),1,m0);
    mass0=new float[n0tot+10];
    fread(mass0,sizeof(float),n0tot+10,m0);
  }
  else {
    if ( (m0 = fopen("m0list.dat","w")) == NULL) {
      fprintf(stderr,"Error: Cannot open m0list.dat\n.");
      return 0;
    }
    n0tot=h->ntot-par->npairs;
    mass0=new float[n0tot+10];
    for (int i=0;i<n0tot;i++) {
      if(data[i].name>0&&data[i].name<=n0tot) {
        float msol=data[i].mass*par->zmbar;
        mass0[data[i].name]=msol;
        m0tot +=msol;
      }
    }
    fwrite(&n0tot,sizeof(int),1,m0);
    fwrite(&m0tot,sizeof(double),1,m0);
    fwrite(mass0,sizeof(float),n0tot+10,m0);
  }
  fclose(m0);
  
  //output data of mloss==============================//
  if(init.geti("calc_mloss")) {
    int nnow=0; //Total number now 
    int nbinds=0; //Strong bound number
    int nbindw=0; //Weak bound number
    int ntid=0; //<2 r_tid number
    double Mnow=0; //Total mass now
    double Minit=0; //Total mass initial
    double Mbindsn=0;   //Total strong bound mass now    
    double Mbindwn=0;   //Total weak bound mass now      
    double Mtidn=0;   //Total mass <2 r_tid now          
    double Mbindsi=0;   //Total strong bound mass initial
    double Mbindwi=0;   //Total weak bound mass initial  
    double Mtidi=0;   //Total mass <2 r_tid initial      
    FILE *fout;
    if ( (fout = fopen(init.gets("outmloss").c_str(),"a+")) == NULL) {
      fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outmloss").c_str());
      return 0;
    }
    float ttot=par->ttot_nb*par->tscale;
    float rtid=par->rtide;
    if(init.getd("rtide")>0) rtid=init.getd("rtide");
        
    for (int j=0; j<h->ntot-par->npairs; j++) {
      if(data[j].name>0&&data[j].name<=n0tot) {
        float msol=data[j].mass*par->zmbar;
        Mnow +=msol;
        nnow++;
        Minit +=mass0[data[j].name];
        if(distance(data[j].x)<2*rtid) {
          Mtidn +=msol;
          ntid++;
          Mtidi +=mass0[data[j].name];
        }
        float ekin=0.5*distance(data[j].v);
        if(ekin<data[j].phi) {
          Mbindwn +=msol;
          nbindw++;
          Mbindwi +=mass0[data[j].name];
          if(ekin<0.5*data[j].phi) {
            Mbindsn +=msol;
            nbinds++;
            Mbindsi +=mass0[data[j].name];
          }
        }
      }
      else printf("Warning!: %d name %d <=0 or >ntot %d\n",j,data[j].name,n0tot);
    }
    if(ttot==0.) fprintf(fout,"N_{now} N_{s,bind} N_{w,bind} N_{tid} M_{now} M_{init} M_{now,s,bind} M_{now,w,bind} M_{now,tid} M_{init,s,bind} M_{init,w,bind} M_{init,tid}\n");
    fprintf(fout,
            "%g %g %g %g %d %g %g %d %g %g %d %g %g %d\n",
            ttot,
            rtid*par->rbar,
            Mnow,
            Minit,
            nnow,
            Mbindsn,
            Mbindsi,
            nbinds,
            Mbindwn,
            Mbindwi,
            nbindw,
            Mtidn,
            Mtidi,
            ntid);
    fclose(fout);
  }

  //current mass vs. initial mass=====================//  
  if(init.geti("calc_mm0")){
    mpair *mass2=NULL; //for calc_mm0
    if (!mass2) mass2=new mpair[h->ntot+10];
    FILE *f1;
    if ( (f1 = fopen(init.gets("outmm0").c_str(),"w")) == NULL) {
        fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outmm0").c_str());
        return 0;
    }
    for (int k=0;k<h->ntot-par->npairs;k++) {
      mass2[k][0]=mass0[data[k].name];
      mass2[k][1]=data[k].mass*par->zmbar;
    }
    std::sort(mass2,&mass2[(int)(h->ntot-par->npairs)],ismaller);
    for (int k=0;k<h->ntot-par->npairs;k++) fprintf(f1,"%g %g\n",mass2[k][0],mass2[k][1]);
    fclose(f1);
  }
  
  //output data of lagr
  if(init.geti("calc_lagr")) {
    FILE *flagr;
    if ( (flagr = fopen(init.gets("outlagr").c_str(),"a+")) == NULL) {
      fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outlagr").c_str());
      return 0;
    }
    int n=(int)(h->ntot-par->npairs);
    float tnow=par->ttot_nb*par->tscale;
    if(!sort_flag) {
      std::sort(data,&data[n],ismaller_r);
      std::sort(&data[n],&data[h->ntot],ismaller_r);
      sort_flag=true;
    }
    float fraction[18]={0.001,0.003,0.005,0.01,0.03,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,0.99,1.0};
    float mtot=0.;
    float mlimit[18],rlagr[18],avmass[18];    
    float mcum=0.,mshell=0.;
    int ncount[18]={},mc=0;
    for(int k=0;k<n;k++) mtot +=data[k].mass;
    printf("N_total=%d N_binary=%d\n",n,(int)par->npairs);
    printf("Mass Fraction:               ");
    for(int k=0;k<18;k++) printf("%10g",fraction[k]);
    printf("\n");
    printf("Sinlge Mass fraction[M_sun]: ");
    for(int k=0;k<18;k++) {
      mlimit[k]=fraction[k]*mtot;
      printf("%10g",mlimit[k]*par->zmbar);
    }
    printf("\n");
    for(int k=0;k<n;k++) {
      float rk=distance(data[k].x);
      mcum +=data[k].mass;
      ncount[mc]++;
      if(mcum>=mlimit[mc]) {
        rlagr[mc]=rk*par->rbar;
        avmass[mc]=(mcum-mshell)/ncount[mc]*par->zmbar;
        mshell=mcum;
        mc++;
        // if(mc>=18&&k<h->ntot-1) {
        //   perror("Error: mass overflow (>initial total mass)!\n");
        //   return 0;
        // }        
      }
      if(mc>=18) break;
    }
    if(mc<18)
      for(int k=mc;k<18;k++) {
        rlagr[k]=rlagr[mc-1];
        avmass[k]=avmass[mc-1];
        ncount[k]=0;
      }
    mc=0.;
    mcum=0.;
    mshell=0.;
    float mbtot=0.;
    float mblimit[18],rblagr[18],avbmass[18];
    int nbcount[18]={};
    for(int k=n;k<h->ntot;k++) mbtot +=data[k].mass;
    printf("Binary Mass fraction[M_sun]: ");
    for(int k=0;k<18;k++) {
      mblimit[k]=fraction[k]*mbtot;
      printf("%10g",mblimit[k]*par->zmbar);
    }
    printf("\n");
    for(int k=n;k<h->ntot;k++) {
      float rk=distance(data[k].x);
      //        printf("k=%d rk=%g\n",k,rk);
      //         float vri[3],vroti[3];
      mcum +=data[k].mass;
      //         for(int j=0;j<3;j++) v[i][0] += data[i].x[j]*data[i].v[j]/rk;
      //         for(int j=0;j<3;j++) {
      //           vri[j] = vrii*data[i].x[j]/rk;
      //           vroti[j] = data[i].v[j]-vri[j];
      //         }
      //         vr[mc] +=v[i][0];
      //         float vrot2=dot(vroti);
      //         v[i][2] = vroti[2];
      //         v[i][1] = ((vroti[1]>=0)?1:-1)*sqrt(vrot2-vroti[2]*vroti[2]);
      //         vxyrot[mc] +=v[i][1];
      //         vzrot[mc] +=v[i][2];
      nbcount[mc]++;
      if(mcum>=mblimit[mc]) {
        rblagr[mc]=rk*par->rbar;
        avbmass[mc]=(mcum-mshell)/nbcount[mc]*par->zmbar;
        mshell=mcum;
        mc++;
        // if(mc>=18&&k<par->npairs-1) {
        //   perror("Error: mass overflow (>initial total mass)!\n");
        //   return 0;
        // }
      }
      if(mc>=18) break;
    }
    if(mc<18)
      for(int k=mc;k<18;k++) {
        rblagr[k]=rblagr[mc-1];
        avbmass[k]=avbmass[mc-1];
        nbcount[k]=0;
      }
      
    if(tnow==0.) {
      fprintf(flagr,"Time[Myr] ");
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      for (int k=0;k<18;k++) fprintf(flagr,(to<std::string>(fraction[k])+" ").c_str());
      fprintf(flagr,"\n");
    }
      
    fprintf(flagr,"%g ", tnow);
    for (int k=0;k<18;k++) fprintf(flagr,"%g ",rlagr[k]);
    for (int k=0;k<18;k++) fprintf(flagr,"%d ",ncount[k]);
    for (int k=0;k<18;k++) fprintf(flagr,"%g ",avmass[k]);
    for (int k=0;k<18;k++) fprintf(flagr,"%g ",rblagr[k]);
    for (int k=0;k<18;k++) fprintf(flagr,"%d ",nbcount[k]);
    for (int k=0;k<18;k++) fprintf(flagr,"%g ",avbmass[k]);
    fprintf(flagr,"\n");

    fclose(flagr);
//       float vr[18],vzrot[18],vxyrot[18],sigmar[18],sigmat[18]

//       float3 *v=new float3[ntot];
//       memset(v,0,sizeof(float3));
//         printf("k=%d rk=%g\n",k,rk);
//         float vri[3],vroti[3];

//         for(int j=0;j<3;j++) v[i][0] += data[i].x[j]*data[i].v[j]/rk;
//         for(int j=0;j<3;j++) {
//           vri[j] = vrii*data[i].x[j]/rk;
//           vroti[j] = data[i].v[j]-vri[j];
//         }
//         vr[mc] +=v[i][0];
//         float vrot2=dot(vroti);
//         v[i][2] = vroti[2];
//         v[i][1] = ((vroti[1]>=0)?1:-1)*sqrt(vrot2-vroti[2]*vroti[2]);
//         vxyrot[mc] +=v[i][1];
//         vzrot[mc] +=v[i][2];
  }
  
  //calc density =====================================//
  if(init.geti("calc_density")) {
    int n=(int)(h->ntot-par->npairs);
    float tnow=par->ttot_nb*par->tscale;
    FILE *f1,*f2;
    if ( (f1 = fopen(init.gets("outden").c_str(),"w")) == NULL) {
      fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outden").c_str());
      return 0;
    }
    if ( (f2 = fopen(init.gets("outdenb").c_str(),"w")) == NULL) {
      fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outdenb").c_str());
      return 0;
    }
    if(!sort_flag) {
      std::sort(data,&data[n],ismaller_r);
      std::sort(&data[n],&data[h->ntot],ismaller_r);
      sort_flag=true;
    }
    //      float2 *cum_r=new float2[n];
    //      memset(cum_r,0,sizeof(float2));
    float cumm=0.;
    fprintf(f1,"n  %gMyr\n",tnow);
    for (int k=0;k<n;k++) {
      float rk=distance(data[k].x);
      cumm +=data[k].mass;
      fprintf(f1,"%g %g\n",rk,cumm);
      //        cum_r[k][0]=rk;
      //        cum_r[k][1] +=data[k].m;
    }
    fclose(f1);
    cumm=0.;
    fprintf(f2,"n  %gMyr\n",tnow);
    for (int k=n;k<h->ntot;k++) {
      float rk=distance(data[k].x);
      cumm +=data[k].mass;
      fprintf(f2,"%g %g\n",rk,cumm);
      //        cum_r[k][0]=rk;
      //        cum_r[k][1] +=data[k].m;
    }
    fclose(f2);
  }
      
#ifdef USE_ROOT
  //draw density x-y==================================//
  // Double_t couts[21];
  // for (int j=0;j<21;j++) couts[j]=(Double_t)pow(10.0,(j-5)/4);
  if(init.geti("draw_density")){
    Double_t range=10*par->rtide;
    TCanvas *c1=new TCanvas("c1","density",800,800);
    TH2F *h2=new TH2F("Density",("Density T = "+to<std::string>(par->ttot_nb*tscale)+" Myr").c_str(),100,-range,range,100,-range,range);
    for (int j=0;j<h->ntot;j++) {
      h2->Fill(data[j].x[0],data[j].x[1]);
    }
    h2->SetXTitle("x[NB]");
    h2->SetYTitle("y[NB]");
    h2->SetStats(0);
    //      h2->SetContour(21,couts);
    h2->Draw("surf3");
    h2->GetZaxis()->SetRangeUser(1,50000);
    c1->SetLogz(1);
    c1->Print((init.gets("outfile")+fileindex(par->ttot_nb,5)+".png").c_str());
    delete h2;
  }
#endif    

  fprintf(stdout,"Finished\n");
  return 0;
}
