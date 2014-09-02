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
  int pnum;
  int nbnum;
  double tbar[3];
  double tnbint;
  double time;
};
  
bool tbarmax_b(const data &a, const data &b){
  return a.tbar[0]>b.tbar[0];
}

bool tbarmax_a(const data &a, const data &b){
  return a.tbar[1]>b.tbar[1];
}

bool tbarmax_1(const data &a, const data &b){
  return a.tbar[2]>b.tbar[2];
}

bool tbarmin_b(const data &a, const data &b){
  return a.tbar[0]<b.tbar[0];
}

bool tbarmin_a(const data &a, const data &b){
  return a.tbar[1]<b.tbar[1];
}

bool tbarmin_1(const data &a, const data &b){
  return a.tbar[2]<b.tbar[2];
}

int colorfun(int index) {
  if (index%10==0) return index+20;
  if (index>11) return index+10;
  return index;
}

int main(int argc, char* argv[]) {
  init.add("datlst","first line show file number, data lst","fort.lst");
  init.add("wcl","reading line number",(int)100);
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
      for (int j=0;j<fln;j++) {
        scanf("%d %d %lg %lg %lg %lg %lg",
              &lst[j].pnum,&lst[j].nbnum,&lst[j].tbar[0],&lst[j].tbar[1],&lst[j].tbar[2],&lst[j].tnbint,&lst[j].time);
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

  TCanvas *c1=new TCanvas("c1","c1",800,600);
  c1->SetGrid();

  //--09/19/13 13:47-show total MPI_barrier time----------//
  double *ttotb=new double[fnum];
  double *ttota=new double[fnum];
  double *ttot1=new double[fnum];
  for (int i=0;i<fnum;i++) {
    ttotb[i]=ttota[i]=ttot1[i]=0;
    for (int j=0;j<fln;j++) {
      ttotb[i] +=lst[i][j].tbar[0];
      ttota[i] +=lst[i][j].tbar[1];
      ttot1[i] +=lst[i][j].tbar[2];
    }
    std::cout<<"rank "<<i<<" MPI_barrier time before nbint: "<<ttotb[i];
    std::cout<<" after nbint: "<<ttota[i];
    std::cout<<" after sendrecv: "<<ttot1[i]<<std::endl;
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
    TH1F **hbarb=new TH1F*[fnum];
    TH1F **hbara=new TH1F*[fnum];
    TH1F **hbar1=new TH1F*[fnum];
    TH1F **hwbarb=new TH1F*[fnum];
    TH1F **hwbara=new TH1F*[fnum];
    TH1F **hwbar1=new TH1F*[fnum];
    TH1F **hp=new TH1F*[fnum];
    TH1F **hnb=new TH1F*[fnum];

    for (int i=0;i<fnum;i++) {
      hbarb[i]=new TH1F(("tb"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"MPI_barrier time before nbint distribution").c_str(),100,-6,1);
      hbara[i]=new TH1F(("ta"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"MPI_barrier time after nbint distribution").c_str(),100,-6,1);
      hbar1[i]=new TH1F(("t1"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"MPI_barrier time after one sendrecv distribution").c_str(),100,-6,1);
hwbarb[i]=new TH1F(("twb"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"Weighted MPI_barrier time before nbint distribution").c_str(),14,-6,1);
      hwbara[i]=new TH1F(("twa"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"Weighted MPI_barrier time after nbint distribution").c_str(),14,-6,1);
      hwbar1[i]=new TH1F(("tw1"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"Weighted MPI_barrier time after one sendrecv distribution").c_str(),14,-6,1);
      TH1F* hwbar=new TH1F(("tw"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+"Weighted MPI_barrier time distribution").c_str(),14,-6,1);
      hnb[i]=new TH1F(("nb"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Neighbor Number distribution").c_str(),100,0,10000);
      hp[i]=new TH1F(("p"+to<std::string>(i)).c_str(),("rank "+to<std::string>(i)+" Irregular block partile number distribution").c_str(),100,0,1000);
      // TH1F **h1i=new TH1F*[3];
      // TH1F **h1iw=new TH1F*[3];
      // for (int j=0;j<3;j++) {
      //   h1i[j]=new TH1F(("t"+tostr(i)+"_f"+tostr(j)).c_str(),("rank "+tostr(i)+"_f"+tostr(j)).c_str(),100,-6,1);
      //   h1iw[j]=new TH1F(("tw"+tostr(i)+"_f"+tostr(j)).c_str(),("rank "+tostr(i)+"_f"+tostr(j)).c_str(),100,-6,1);
      //   h1i[j]->SetXTitle("Log(#Delta T_{bar})");
      //   h1iw[j]->SetXTitle("Log(#Delta T_{bar})");
      // }

      for (int j=0;j<fln;j++) {
        hbarb[j]->Fill(log10(lst[i][j].tbar[0]));
        hbara[j]->Fill(log10(lst[i][j].tbar[1]));
        hbar1[j]->Fill(log10(lst[i][j].tbar[2]));
        hwbarb[i]->Fill(log10(lst[i][j].tbar[0]),lst[i][j].tbar[0]);
        hwbara[i]->Fill(log10(lst[i][j].tbar[1]),lst[i][j].tbar[1]);
        hwbar1[i]->Fill(log10(lst[i][j].tbar[2]),lst[i][j].tbar[2]);
        hp[i]->Fill(lst[i][j].pnum);
        hnb[i]->Fill(lst[i][j].nbnum);
      }
      hbarb[i]->SetXTitle("Log(#Delta T_{bar})");
      hbarb[i]->SetLineColor(colorfun(i+1));
      hbarb[i]->SetLineWidth(2);
      hbarb[i]->SetLineStyle(1);
      hbara[i]->SetXTitle("Log(#Delta T_{bar})");
      hbara[i]->SetLineColor(colorfun(i+1));
      hbara[i]->SetLineWidth(2);
      hbara[i]->SetLineStyle(2);      
      hbar1[i]->SetXTitle("Log(#Delta T_{bar})");
      hbar1[i]->SetLineColor(colorfun(i+1));
      hbar1[i]->SetLineWidth(2);
      hbar1[i]->SetLineStyle(3);
      TH1F* hbar=(TH1F*)hbara[i]->Clone();
      hbar->SetXTitle("Log(#Delta T_{bar})");
      hbar->SetTitle(("rank "+to<std::string>(i)+"MPI_barrier time distribution").c_str());
      hwbarb[i]->SetXTitle("Log(#Delta T_{bar})");
      hwbarb[i]->SetLineColor(colorfun(i+1));
      hwbarb[i]->SetLineWidth(2);
      hwbarb[i]->SetLineStyle(1);
      hwbara[i]->SetXTitle("Log(#Delta T_{bar})");
      hwbara[i]->SetLineColor(colorfun(i+1));
      hwbara[i]->SetLineWidth(2);
      hwbara[i]->SetLineStyle(2);
      hwbar1[i]->SetXTitle("Log(#Delta T_{bar})");
      hwbar1[i]->SetLineColor(colorfun(i+1));
      hwbar1[i]->SetLineWidth(2);
      hwbar1[i]->SetLineStyle(3);
      TH1F* hwbar=(TH1F*)hwbara[i]->Clone();
      hwbar->SetTitle(("rank "+to<std::string>(i)+"Weighted MPI_barrier time distribution").c_str());
      hwbar->SetXTitle("Log(#Delta T_{bar})");      
      hnb[i]->SetXTitle("N_{nb}");
      hnb[i]->SetLineColor(colorfun(i+1));
      hnb[i]->SetLineWidth(2);
      hnb[i]->SetLineStyle(1);
      hp[i]->SetXTitle("N_{p}");
      hnb[i]->SetLineColor(colorfun(i+1));
      hnb[i]->SetLineWidth(2);
      hnb[i]->SetLineStyle(1);

      c1->Clear();
      TLegend h1t(0.8,0.13,0.9,0.75);
      hlt.AddEntry(hbarb[i],"Before nbint");
      hlt.AddEntry(hbara[i],"after nbint");
      hlt.AddEntry(hbar1[i],"after sendrecv");
      hbar->Draw();
      hbarb[i]->Draw("same");
      hbar1[i]->Draw("same");
      hlt.Draw();
      c1->SetLogy();
      c1->Update();
      c1->Print((init.gets("path")+fname[i]+"_tdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_tdist.png").c_str());
      c1->SetLogy(0);
      c1->Clear();

      TLegend h1tw(0.8,0.13,0.9,0.75);
      hlt.AddEntry(hwbarb[i],"Before nbint");
      hlt.AddEntry(hwbara[i],"after nbint");
      hlt.AddEntry(hwbar1[i],"after sendrecv");
      hwbar->Draw();
      hwbarb[i]->Draw("same");
      hwbar1[i]->Draw("same");
      hltw.Draw();
      c1->Print((init.gets("path")+fname[i]+"_twdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_twdist.png").c_str());
      hp[i]->Draw();
      c1->Print((init.gets("path")+fname[i]+"_pdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_pdist.png").c_str());
      hnb[i]->Draw();
      c1->Print((init.gets("path")+fname[i]+"_nbdist.eps").c_str());
      c1->Print((init.gets("path")+fname[i]+"_nbdist.png").c_str());
    }

    //    TH1F *hd=new TH1F("tall",("MPI_Barrier time distribution "+to<std::string>(fnum)+" nodes").c_str(),100,-6,-1);
    TH1F *hdb=(TH1F*)hbarb[findmax(ttot,fnum)]->Clone();
    TH1F *hda=(TH1F*)hbara[findmax(ttot,fnum)]->Clone();
    TH1F *hd1=(TH1F*)hbar1[findmax(ttot,fnum)]->Clone();
    TH1F *hdwb=(TH1F*)hwbarb[findmax(ttot,fnum)]->Clone();
    TH1F *hdwa=(TH1F*)hwbara[findmax(ttot,fnum)]->Clone();
    TH1F *hdw1=(TH1F*)hwbar1[findmax(ttot,fnum)]->Clone();
    c1->Clear();
    hdb->SetTitle(("MPI_Barrier time before nbint distribution "+to<std::string>(fnum)+" nodes").c_str());
    hda->SetTitle(("MPI_Barrier time after nbint distribution "+to<std::string>(fnum)+" nodes").c_str());
    hd1->SetTitle(("MPI_Barrier time after sendrecv distribution "+to<std::string>(fnum)+" nodes").c_str());
    hdwb->SetTitle(("Weighted MPI_Barrier time before nbint distribution "+to<std::string>(fnum)+" nodes").c_str());
    hdwa->SetTitle(("Weighted MPI_Barrier time after nbint distribution "+to<std::string>(fnum)+" nodes").c_str());
    hdw1->SetTitle(("Weighted MPI_Barrier time after sendrecv distribution "+to<std::string>(fnum)+" nodes").c_str());
    hdb->SetXTitle("Log(#Delta T_{bar})");
    hda->SetXTitle("Log(#Delta T_{bar})");
    hd1->SetXTitle("Log(#Delta T_{bar})");
    hdwb->SetXTitle("Log(#Delta T_{bar})");
    hdwa->SetXTitle("Log(#Delta T_{bar})");
    hdw1->SetXTitle("Log(#Delta T_{bar})");
    hdb->Draw();
    TLegend tdb(0.8,0.13,0.9,0.75);
    for (int i=0;i<fnum;i++) {
      hbarb[i]->Draw("same");
      tdb.AddEntry(hbarb[i],("rank "+to<std::string>(i)).c_str());
    }
    tdb.Draw();
    c1->Print((init.gets("path")+"tbdist.eps").c_str());
    c1->Print((init.gets("path")+"tbdist.png").c_str());
    c1->Clear();
    hda->Draw();
    TLegend tda(0.8,0.13,0.9,0.75);
    for (int i=0;i<fnum;i++) {
      hbara[i]->Draw("same");
      tda.AddEntry(hbara[i],("rank "+to<std::string>(i)).c_str());
    }
    tda.Draw();
    c1->Print((init.gets("path")+"tadist.eps").c_str());
    c1->Print((init.gets("path")+"tadist.png").c_str());
    c1->Clear();
    hd1->Draw();
    TLegend td1(0.8,0.13,0.9,0.75);
    for (int i=0;i<fnum;i++) {
      hbar1[i]->Draw("same");
      td1.AddEntry(hbar1[i],("rank "+to<std::string>(i)).c_str());
    }
    td1.Draw();
    c1->Print((init.gets("path")+"t1dist.eps").c_str());
    c1->Print((init.gets("path")+"t1dist.png").c_str());
    c1->Clear();
    hdwb->Draw();
    TLegend tdwb(0.1,0.13,0.2,0.75);
    for (int i=0;i<fnum;i++) {
      hwbarb[i]->Draw("same");
      tdwb.AddEntry(hwbarb[i],("rank "+to<std::string>(i)).c_str());
    }
    tdwb.Draw();
    c1->Print((init.gets("path")+"twbdist.eps").c_str());
    c1->Print((init.gets("path")+"twbdist.png").c_str());
    c1->Clear();
    hdwa->Draw();
    TLegend tdwa(0.1,0.13,0.2,0.75);
    for (int i=0;i<fnum;i++) {
      hwbara[i]->Draw("same");
      tdwb.AddEntry(hwbara[i],("rank "+to<std::string>(i)).c_str());
    }
    tdwa.Draw();
    c1->Print((init.gets("path")+"twadist.eps").c_str());
    c1->Print((init.gets("path")+"twadist.png").c_str());
    c1->Clear();
    hdw1->Draw();
    TLegend tdw1(0.1,0.13,0.2,0.75);
    for (int i=0;i<fnum;i++) {
      hwbar1[i]->Draw("same");
      tdw1.AddEntry(hwbar1[i],("rank "+to<std::string>(i)).c_str());
    }
    tdw1.Draw();
    c1->Print((init.gets("path")+"tw1dist.eps").c_str());
    c1->Print((init.gets("path")+"tw1dist.png").c_str());
    c1->Clear();
  }
  
  //--09/15/13 11:05-dispersion of nbnum------------------//
  float *nsigma=new float[fln];
  float *lnsigma=new float[fln];
  int *nmean=new int[fln];
  float *lnmean=new float[fln];
  if(init.getb("draw_nsigma")){
    float *nratio=new float[fln];
    float *lnratio=new float[fln];
    for (int j=0;j<fln;j++){
      nmean[j]=0;
      for (int i=0;i<fnum;i++) {
        nmean[j] +=lst[i][j].nbnum;
      }
      nmean[j] /=fnum;
      nsigma[j]=0;
      for (int i=0;i<fnum;i++) {
        int n2tmp=lst[i][j].nbnum-nmean[j];
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
    for (int i=0;i<fln;i++) {
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
      for (int j=0;j<fln;j++){
        h7[i]->Fill(lnsigma[j],log10(lst[i][j].tbar));
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
    
