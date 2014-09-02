#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <omp.h>

#include <uftools.h>
#include <initial.h>

#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLegend.h"

static pars_initial init(".bardraw_config");

struct data{
  int nbnum;
  double tbar;
  double time;
};
  
bool tbarmax(const data &a, const data &b){
  return a.tbar>b.tbar;
}

bool tbarmin(const data &a, const data &b){
  return a.tbar<b.tbar;
}

int colorfun(int index) {
  if (index%10==0) return index+20;
  if (index>11) return index+10;
  return index;
}

int main(int argc, char* argv[]) {
  init.add("datlst","first line show file number, data lst","fort.lst");
  init.add("repeat","nbint loop repert times",(int)32);
  init.add("wcl","file line number - 1",(int)100);
  init.add("flag","read data from binary",(bool)true);
  init.add("path","figure path","./");
  init.add("draw_ntdist","draw nbnum and time distribution",(bool)true);
  init.add("draw_nsigma","draw nsigma distribution",(bool)true);
  init.initial(argc,argv);
  
  if(mkpath(init.gets("path").c_str(),0777)==-1)
  {
    std::cerr<<"Eroor: "<<strerror(errno)<<std::endl;
    exit(1);
  }
  
  ifstream f(init.gets("datlst").c_str());

  if(!f.is_open()) {
    std::cerr<<"Error: No file list found!\n";
    return 0;
  }

  int fnum,fln;
  int ncount;

  f>>fnum;
  fln=init.geti("wcl");

  std::string *fname=new std::string[fnum];
  data **lst=new data*[fnum];

  for (int i=0;i<fnum;i++) {
    f>>fname[i];
    lst[i]=new data[fln];

    if (!init.get<bool>("flag")){
      if ( freopen(fname[i].c_str(),"r",stdin) == NULL) {
        std::cerr<<"Error, file "<<fname[i]<<" not found!\n";
        return 0;
      }
      int nbtmp;
      double tbtmp;
      double ttmp;
      scanf("%d %lg %lg",&nbtmp,&tbtmp,&ttmp);
      for (int j=0;j<fln;j++) {
        scanf("%d %lg %lg",&lst[i][j].nbnum,&lst[i][j].tbar,&lst[i][j].time);
      }
      FILE *stream;
      if ( (stream = fopen((fname[i]+"b").c_str(), "w")) == NULL) {
        std::cerr<<"Error, Cannot open output file "<<fname[i]<<"b!\n";
        return 0;
      }
      fwrite(lst[i],sizeof(data),fln, stream);
      fclose(stream);
    }
    else {
      FILE *stream;
      if ( (stream = fopen((fname[i]+"b").c_str(), "r")) == NULL) {
        std::cerr<<"Error, Cannot open file "<<fname[i]<<"b!\n";
        return 0;
      }
      fread(lst[i],sizeof(data),fln, stream);
      fclose(stream);
    }
  }

  int frp=init.geti("repeat");
  int fntot=fln/frp;
  if(fln%frp) std::cerr<<"Warning: file lines number not match file number ("<<fln%frp<<")!\n";

  TCanvas *c1=new TCanvas("c1","c1",800,600);
  c1->SetGrid();

  //--09/19/13 13:47-show total MPI_barrier time----------//
  double *ttot=new double[fnum];
  for (int i=0;i<fnum;i++) {
    ttot[i]=0;
    for (int j=0;j<fln;j++) {
      ttot[i] +=lst[i][j].tbar;
    }
    std::cout<<"rank "<<i<<" MPI_barrier time: "<<ttot[i]<<std::endl;
  }

  //--09/18/13 12:22-count--------------------------------//
  // if (init.getb("draw_intgrt_time")){
  //   double *tmax=new double[fnum];
  //   double *tmin=new double[fnum];
  //   for (int i=0;i<fnum;i++) {
  //     tmax[i]=findpeak(lst[i],fln,tbarmax);
  //     tmin[i]=findpeak(lst[i],fln,tbarmin);
  //   }
  //   int ttmax=log10(findmax(tmax,fnum))+1;
  //   int ttmin=log10(findmin(tmax,fnum))-1;
  //   int tintv=ttmax-ttmin;
  //   double **tcum=new double*[fnum];
  //   for (int i=0;i<fnum;i++) {
  //     tcum[i]=new double[tintv];
  //     for (int j=0;j<tintv;j++) {
  //       tcum[i][j]=0;
  //     }
  //     for (int j=0;j<fln;j++) {
  //       tcum[i][log10[lst[i][j].tbar]+ttmin] +=lst[i][j].tbar;
  //     }
  // }
  
  //--09/15/13 11:05-individual plots---------------------//
  if (init.getb("draw_ntdist")){
    TH1F **h1=new TH1F*[fnum];
    TH1F **h2=new TH1F*[fnum];
    TH1F **h1w=new TH1F*[fnum];

#pragma omp parallel for private(ncount)
    for (int i=0;i<fnum;i++) {
      h1[i]=new TH1F(("t"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"MPI_barrier time distribution").c_str(),100,-6,1);
      h1w[i]=new TH1F(("tw"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"Weighted MPI_barrier time distribution").c_str(),14,-6,1);
      h2[i]=new TH1F(("n"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Neighbor Number distribution").c_str(),100,0,10000);
      TH1F **h1i=new TH1F*[frp];
      TH1F **h1iw=new TH1F*[frp];
      for (int j=0;j<frp;j++) {
        h1i[j]=new TH1F(("t"+tostr(i)+"_f"+tostr(j)).c_str(),("rank "+tostr(i)+"_f"+tostr(j)).c_str(),100,-6,1);
        h1iw[j]=new TH1F(("tw"+tostr(i)+"_f"+tostr(j)).c_str(),("rank "+tostr(i)+"_f"+tostr(j)).c_str(),100,-6,1);
        h1i[j]->SetXTitle("Log(#Delta T_{bar})");
        h1iw[j]->SetXTitle("Log(#Delta T_{bar})");
      }

      ncount=0;
      for (int j=0;j<fln;j++) {
        ncount++;
        h1[i]->Fill(log10(lst[i][j].tbar));
        h1w[i]->Fill(log10(lst[i][j].tbar),lst[i][j].tbar);
        h1i[j%frp]->Fill(log10(lst[i][j].tbar));
        h1iw[j%frp]->Fill(log10(lst[i][j].tbar),lst[i][j].tbar);
        if (ncount==31) {
          h2[i]->Fill(lst[i][j].nbnum);
          ncount=0;
        }
      }
      h1[i]->SetXTitle("Log(#Delta T_{bar})");
      h1w[i]->SetXTitle("Log(#Delta T_{bar})");
      h2[i]->SetXTitle("N_{nb}");

      c1->Clear();
      h1[i]->SetLineStyle(2);
      h1[i]->SetLineWidth(3);
      h1[i]->SetLineColor(1);
      h1[i]->Draw();
      TLegend h1t(0.8,0.13,0.9,0.75);
      h1t.AddEntry(h1[i],"Total");
      for (int j=0;j<frp;j++) {
        h1i[j]->SetLineColor(colorfun(j+1));
        h1i[j]->SetLineWidth(2);
        if (j==0) h1i[j]->SetLineStyle(3);
        if (j==frp-1) h1i[j]->SetLineStyle(4);
        if (j<frp-1) h1t.AddEntry(h1i[j],("Loop "+tostr(j+1)).c_str());
        else h1t.AddEntry(h1i[j],("BFNB "+tostr(j)).c_str());
        h1i[j]->Draw("same");
      }
      h1t.Draw();
      c1->SetLogy();
      c1->Update();
      c1->Print((init.gets("path")+fname[i]+"_tdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_tdist.png").c_str());
      c1->SetLogy(0);
      c1->Clear();
      h1w[i]->SetLineWidth(3);
      h1w[i]->SetLineStyle(2);
      h1w[i]->SetLineColor(1);
      h1w[i]->Draw();
      TLegend h1tw(0.8,0.13,0.9,0.75);
      h1tw.AddEntry(h1w[i],"Total");
      for (int j=0;j<frp;j++) {
        h1iw[j]->SetLineColor(colorfun(j+1));
        //        h1iw[j]->SetLineStyle(2);
        h1iw[j]->SetLineWidth(2);
        if (j==0) h1iw[j]->SetLineStyle(3);
        if (j==frp-1) h1iw[j]->SetLineStyle(4);
        if (j<frp-1) h1tw.AddEntry(h1iw[j],("Loop "+tostr(j+1)).c_str());
        else h1tw.AddEntry(h1iw[j],("BFNB "+tostr(j)).c_str());
        h1iw[j]->Draw("same");
      }
      h1tw.Draw();
      c1->Print((init.gets("path")+fname[i]+"_twdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_twdist.png").c_str());
      h2[i]->Draw();
      c1->Print((init.gets("path")+fname[i]+"_ndist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_ndist.png").c_str());
    }

    //    TH1F *hd=new TH1F("tall",("MPI_Barrier time distribution "+to<std::string>(fnum)+" nodes").c_str(),100,-6,-1);
    TH1F *hd=(TH1F*)h1[findmax(ttot,fnum)]->Clone();
    TH1F *hdw=(TH1F*)h1w[findmax(ttot,fnum)]->Clone();
    c1->Clear();
    hd->SetTitle(("MPI_Barrier time distribution "+to<std::string>(fnum)+" nodes").c_str());
    hdw->SetTitle(("Weighted MPI_Barrier time distribution "+to<std::string>(fnum)+" nodes").c_str());
    hd->SetXTitle("Log(#Delta T_{bar})");
    hdw->SetXTitle("Log(#Delta T_{bar})");
    hd->Draw();
    TLegend td(0.8,0.13,0.9,0.75);
    for (int i=0;i<fnum;i++) {
      h1[i]->SetLineColor(colorfun(i));
      h1[i]->Draw("same");
      td.AddEntry(h1[i],("rank "+to<std::string>(i)).c_str());
    }
    td.Draw();
    c1->Print((init.gets("path")+"tdist.eps").c_str());
    c1->Print((init.gets("path")+"tdist.png").c_str());
    c1->Clear();
    hdw->Draw();
    TLegend tdw(0.1,0.13,0.2,0.75);
    for (int i=0;i<fnum;i++) {
      h1w[i]->SetLineColor(colorfun(i));
      h1w[i]->Draw("same");
      tdw.AddEntry(h1w[i],("rank "+to<std::string>(i)).c_str());
    }
    tdw.Draw();
    c1->Print((init.gets("path")+"twdist.eps").c_str());
    c1->Print((init.gets("path")+"twdist.png").c_str());
  }
  
  //--09/15/13 11:05-dispersion of nbnum------------------//
  float *nsigma=new float[fntot];
  float *lnsigma=new float[fntot];
  int *nmean=new int[fntot];
  float *lnmean=new float[fntot];
  if(init.getb("draw_nsigma")){
    float *nratio=new float[fntot];
    float *lnratio=new float[fntot];
    for (int j=0;j<fntot;j++){
      nmean[j]=0;
      for (int i=0;i<fnum;i++) {
        nmean[j] +=lst[i][frp*j].nbnum;
      }
      nmean[j] /=fnum;
      nsigma[j]=0;
      for (int i=0;i<fnum;i++) {
        int n2tmp=lst[i][frp*j].nbnum-nmean[j];
        nsigma[j] +=n2tmp*n2tmp;
      }
      nsigma[j] =sqrt(nsigma[j])/fnum;
      lnsigma[j]=log10(nsigma[j]);
      nratio[j]=nsigma[j]/(float)nmean[j];
      lnratio[j]=log10(nratio[j]);
      lnmean[j] = log10(nmean[j]);
    }

    TH1F *h3=new TH1F("ns","Neighbor number standard deviation",100,0,nsigma[findmax(nsigma,fntot)]);
    TH1F *h4=new TH1F("nsn","Neighbor number standard deviation / mean",100,0,nratio[findmax(nratio,fntot)]);
    TH1F *h5=new TH1F("lns","Neighbor number standard deviation",100,0,lnsigma[findmax(lnsigma,fntot)]);
    TH1F *h6=new TH1F("lnsn","Neighbor number standard deviation / mean",100,0,lnratio[findmax(lnratio,fntot)]);
    TH2D *h7=new TH2D("nns","Neighbor number vs. standard deviation",100,0,nmean[findmax(nmean,fntot)],100,0,nsigma[findmax(nsigma,fntot)]);
    TH2D *h8=new TH2D("lnns","Neighbor number vs. standard deviation",400,0,lnmean[findmax(lnmean,fntot)],400,0,lnsigma[findmax(lnsigma,fntot)]);    
    for (int i=0;i<fntot;i++) {
      h3->Fill(nsigma[i]);
      h4->Fill(nratio[i]);
      h5->Fill(lnsigma[i]);
      h6->Fill(lnratio[i]);
      h7->Fill(nmean[i],nsigma[i]);
      h8->Fill(lnmean[i],lnsigma[i]);
    }
    h3->SetXTitle("#sigma_{nb}");
    h4->SetXTitle("#sigma_{nb}/N_{nb}");
    h5->SetXTitle("Log(#sigma_{nb})");
    h6->SetXTitle("Log(#sigma_{nb}/N_{nb})");
    h7->SetXTitle("N_{nb}");
    h7->SetYTitle("#sigma_{nb}");
    h8->SetXTitle("Log(N_{nb})");
    h8->SetYTitle("Log(#sigma_{nb})");
    h7->SetStats(0);
    h8->SetStats(0);
    
    c1->Clear();
    h3->Draw();
    c1->Print((init.gets("path")+"nsigma_dist.eps").c_str());
    c1->Print((init.gets("path")+"nsigma_dist.png").c_str()); 
    h4->Draw();
    c1->Print((init.gets("path")+"nsigma_nordist.eps").c_str());
    c1->Print((init.gets("path")+"nsigma_nordist.png").c_str()); 
    h5->Draw();
    c1->Print((init.gets("path")+"lnsigma_dist.eps").c_str());
    c1->Print((init.gets("path")+"lnsigma_dist.png").c_str());
    h6->Draw();
    c1->Print((init.gets("path")+"lnsigma_nordist.eps").c_str());
    c1->Print((init.gets("path")+"lnsigma_nordist.png").c_str());
    h7->Draw();
    c1->Print((init.gets("path")+"ns_nsigma.eps").c_str());
    c1->Print((init.gets("path")+"ns_nsigma.png").c_str());
    h8->Draw();
    c1->Print((init.gets("path")+"lns_lnsigma.eps").c_str());
    c1->Print((init.gets("path")+"lns_lnsigma.png").c_str());
  }

  //--09/15/13 14:16-phase nsigma tdist-------------------//
  if (init.getb("draw_ntdist")&&init.getb("draw_nsigma")){
    TH2F **h7=new TH2F*[fnum];
    TH2F **h8=new TH2F*[fnum];
    TH2D **h9=new TH2D*[fnum];
    for (int i=0;i<fnum;i++) {
      h7[i]=new TH2F(("ns_tbar1"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Neighbor number standard deviation vs. MPI_barrier time(1st loop)").c_str(),100,0,lnsigma[findmax(lnsigma,fntot)],100,-6,1);
      h8[i]=new TH2F(("ns_tbar0"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Neighbor number standard deviation vs. MPI_barrier time(Before nbint)").c_str(),100,0,lnsigma[findmax(lnsigma,fntot)],100,-6,1);
      h9[i]=new TH2D(("nb_tbar1"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Neighbor number vs. MPI_barrier time(1st loop)").c_str(),400,0.0,lnmean[findmax(lnmean,fntot)],400,-6.,1.);
      for (int j=0;j<fntot;j++){
        h7[i]->Fill(lnsigma[j],log10(lst[i][frp*j].tbar));
        h8[i]->Fill(lnsigma[j],log10(lst[i][frp*(j+1)-1].tbar));
        h9[i]->Fill(lnmean[j],log10(lst[i][frp*j].tbar));
      }
      h7[i]->SetXTitle("Log(#sigma_{nb})");
      h7[i]->SetYTitle("Log(#Delta T_{bar})");
      h8[i]->SetXTitle("Log(#sigma_{nb})");
      h8[i]->SetYTitle("Log(#Delta T_{bar})");
      h9[i]->SetXTitle("Log(N_{b})");
      h9[i]->SetYTitle("Log(#Delta T_{bar})");
      c1->Clear();
      h7[i]->Draw();
      h7[i]->SetStats(0);
      c1->Print((init.gets("path")+fname[i]+"_nsigma_tbar1.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_nsigma_tbar1.png").c_str());
      c1->Clear();
      h8[i]->Draw();
      h8[i]->SetStats(0);
      c1->Print((init.gets("path")+fname[i]+"_nsigma_tbar0.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_nsigma_tbar0.png").c_str());
      h9[i]->Draw();
      h9[i]->SetStats(0);
      c1->Print((init.gets("path")+fname[i]+"_nb_tbar1.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_nb_tbar1.png").c_str());
    }
  }
  
  return 0;
}
    
