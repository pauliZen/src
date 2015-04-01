#include <string>
#include <iostream>
#include <fstream>
#include <uftools.h>
#include <initial.h>
#include <nbodymultidraw.h>
#include <nbodyvfit.h>

int main(int argc, char *argv[])
{
  pars_initial init(".drawvfit_config");
  init.add("figpath","Directory to store figures","/home/lwang/Dropbox/Datas/Planets/vfit/");
  init.add("figname","Figure name prefix","test.eps");
  init.add("rootlist","root file to chain","vfit.lst");
  init.add("parlist","pars list file name: selname, seltype, selrange, selnum, selvalue","pars.list");
  init.add("draw_b","draw pars for b fit",(int)1);
  init.add("draw_p","draw pars for p fit",(int)1);
  init.add("draw_tm","draw pars for t fit",(int)1);
  init.add("draw_t","draw pars for t fit",(int)1);
  init.add("draw_vinf","draw pars for vinf fit",(int)1);
  init.add("draw_vp","draw pars for vp fit",(int)1);
  init.add("draw_nsnp","draw pars for np/ns fit",(int)0);
  init.add("draw_count","draw pars for typicial N_ce/per star",(int)0);
  init.add("selection","selection","chi2<200");
  init.initial(argc,argv);
  
  std::string dir=init.gets("figpath");
  std::string fig=init.gets("figname");
  std::string parlist=init.gets("rootlist");
  std::string parslist=init.gets("parlist");

  if(mkpath(dir.c_str(),0777)==-1)
  {
    std::cerr<<"Eroor: "<<strerror(errno)<<std::endl;
    exit(1);
  }

  //  Float_t legend_lnf[4]={0.13,0.6,0.33,0.89};
  Float_t legend_rnf[4]={0.74,0.35,0.89,0.89};
  Float_t legend_rf[4]={0.75,0.35,0.89,0.89};
  Float_t legend_lf[4]={0.11,0.35,0.27,0.89};
  
  if (init.getb("draw_b")){
    TChain *tc=new TChain("bfit");
    TChain_LoadList(tc,parlist);
    MultiDraw(tc,dir,("bslope_offset"+fig),parslist,"vsigma:vserr:h:herr",legend_rf,"b_{0}","#alpha_{b}",init.gets("selection"),"");
    MultiDraw(tc,dir,("bslope_n_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:1000*h/(ns+nb):1000*herr/(ns+nb)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","1000#alpha_{b}/N_{sb}",init.gets("selection"),"",1,1.7,5.3,0,0,0,0,1);
    MultiDraw(tc,dir,("bslope_norm_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:h/(500000*h+1000*vsigma):herr/(500000*h+1000*vsigma)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","#alpha_{b,norm}",init.gets("selection"),"",1,1.7,5.3,0,0,0,0,1);
  }

  if (init.getb("draw_p")){
    TChain *tc=new TChain("pfit");
    TChain_LoadList(tc,parlist);
    MultiDraw(tc,dir,("pslope_offset"+fig),parslist,"log10(h/(ns+nb)):herr/(log(10)*h):log10(vsigma):vserr/(log(10)*vsigma)",legend_rf,"log(#alpha_{p}/N_{sb})","log(p_{0})",init.gets("selection")+"&&abs(vserr/(log(10)*vsigma))<0.3&&abs(herr/(log(10)*h))<0.3","",1,-6.5,-1.5);
    MultiDraw(tc,dir,("pslope_rho_log"+fig),parslist,"log10((ns+nb)/rbar**3):ns:log10(h/(ns+nb)):herr/(log(10)*h)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","log(#alpha_{p}/N_{sb})",init.gets("selection")+"&&abs(vserr/(log(10)*vsigma))<0.3&&abs(herr/(log(10)*h))<0.3","",1,1.7,5.3,0,0,0,0,1);
    MultiDraw(tc,dir,("pslope_n_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:1000*h/(ns+nb):1000*herr/(ns+nb)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","1000#alpha_{p}/N_{sb}",init.gets("selection"),"",1,1.7,5.3,0,0,0,0,1);
    MultiDraw(tc,dir,("pslope_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:h:herr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","alpha_{p}",init.gets("selection")+"&&abs(vserr/(log(10)*vsigma))<0.3&&abs(herr/(log(10)*h))<0.3","",1,1.7,5.3,0,0,0,0,1);
    MultiDraw(tc,dir,("pslope_norm_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:h/(500000*h+1000*vsigma):herr/(500000*h+1000*vsigma)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","#alpha",init.gets("selection")+"&&abs(vserr/(log(10)*vsigma))<0.3&&abs(herr/(log(10)*h))<0.3","",1,1.7,5.3,1,0,2.5E-6,0,1);
    MultiDraw(tc,dir,("pslope_lognorm_rho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:log10(h/(500000*h+1000*vsigma)):herr/(log(10)*h)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","log(#alpha)",init.gets("selection")+"&&abs(vserr/(log(10)*vsigma))<0.3&&abs(herr/(log(10)*h))<0.3","",1,1.7,5.3,1,-7.5,-5.5,0,1);
  }

  if (init.getb("draw_t")){
    TChain *tc=new TChain("tfit");
    TChain_LoadList(tc,parlist);
    MultiDraw(tc,dir,("tmu_sigma"+fig),parslist,"vmax:vmerr:vsigma:vserr",legend_rf,"log(t_{m})","sigma_t",init.gets("selection")+"&&vmax>0&&vmax<3&&vmerr<0.2&&vserr<0.2","",1,0.5,1.8,1,0.3,0.8);
    //    MultiDraw(tc,dir,("tsigma_h"+fig),parslist,"vsigma:vserr:h:herr",legend_rf,"t_{w,log}","N_{t,log}",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","");
    MultiDraw(tc,dir,("tmu_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vmax:vmerr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","log(t_{m})",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",1,1.7,5.3,0,0,0,0,1,0.8);
    MultiDraw(tc,dir,("tsigma_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vsigma:vserr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","#sigma_{t}",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",1,1.7,5.3,0,0,0,0,1,0.8);
    MultiDraw(tc,dir,("tmus_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vmax:vsigma",legend_rnf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","log(t_{m} #pm #sigma_{t})",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",1,1.7,5.3,0,0,0,0,1,0.8);
    //    MultiDraw(tc,dir,("tmu_lgrho"+fig),parslist,"log10(ns/rbar**3):ns:vmax:vmerr",legend_rf,"log(N_{s}/r_{vir}^{3} [pc^{-3}])","log(t_{m})",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",0,0,0,0,0,0,0,1,0.8);
    //    MultiDraw(tc,dir,("t10mu_rho"+fig),parslist,"(ns+nb)/rbar**3:ns:10**vmax:vmerr/vmax/log(10)",legend_rf,"N_{sb}/r_{vir}^{3} [pc^{-3}]","t_{m}",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",0,0,0,0,0,0,0,1,0.8);
    //    MultiDraw(tc,dir,("tsigma_rho"+fig),parslist,"(ns+nb)/rbar**3:ns:vsigma:vserr",legend_rf,"N_{sb}/r_{vir}^{3} [pc^{-3}]","t_{w,log}",init.gets("selection")+"&&vmax>0&&vmax<3&&vserr<0.2","",0,0,0,0,0,0,0,1,0.8);
  }

  if (init.getb("draw_tm")){
    TChain *tc=new TChain("cemave");
    TChain_LoadList(tc,parlist);
    std::string tfrac[11]={"0.1","2.1","15.9","50","84.1","97.55","99.8","10","25","75","90"};
    bool mask[11]={0,0,0,1,1,1,1,0,0,1,1};
    for (int i=0;i<11;i++)
      MultiDraw(tc,dir,("tf_"+tfrac[i]+fig),parslist,"log10((ns+nb)/rbar**3):ns:log10(ctime["+to<std::string>(i)+"]):ctime_err["+to<std::string>(i)+"]/ctime["+to<std::string>(i)+"]/log(10)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","log(t_{"+to<std::string>(tfrac[i])+"%} [Myr])",init.gets("selection")+"&&ntot>0","",1,1.7,5.3,1,(mask[i]?0:-3),(mask[i]?4:2),0,1,0.8);
    MultiDraw(tc,dir,("td_1sigma"+fig),parslist,"log10((ns+nb)/rbar**3):ns:log10(ctime[4]-ctime[2]):(ctime_err[4]+ctime_err[2])/(ctime[4]-ctime[2])/log(10)",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","t_{1#sigma}",init.gets("selection")+"&&ntot>0","",1,1.7,5.3,0,0,0,0,1,0.8);
  }

  if (init.getb("draw_count")){
    TChain *tc=new TChain("fcount");
    TChain_LoadList(tc,parlist);
    std::string tfrac[11]={"0.1","2.1","15.9","50","84.1","97.55","99.8","10","25","75","90"};
    std::string t0label[5]={"S-A","S-M","S-P","P-A","P-M"};
    int mask[11]={10,10,30,50,150,220,250,0,0,0,0};
    if(init.geti("draw_count")==1) {
      for (int i=0;i<11;i++) {
        MultiDraw(tc,dir,("fscount_"+tfrac[i]+fig),parslist,"log10((ns+nb)/rbar**3):ns:sfrac["+to<std::string>(i)+"]:ns",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","N_{SCE,"+tfrac[i]+"%}",init.gets("selection")+"&&sfrac[6]>0","",1,1.7,5.3,1,0,mask[i],0,0,0.8);
        MultiDraw(tc,dir,("fpcount_"+tfrac[i]+fig),parslist,"log10((ns+nb)/rbar**3):ns:pfrac["+to<std::string>(i)+"]:ns",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","N_{PCE,"+tfrac[i]+"%}",init.gets("selection")+"&&pfrac[6]>0","",1,1.7,5.3,1,0,mask[i],0,0,0.8);
      }
    }
    if(init.geti("draw_count")==2) {
      for (int i=0;i<5;i++) {
        MultiDraw(tc,dir,("frac0c_"+t0label[i]+fig),parslist,"log10((ns+nb)/rbar**3):ns:frac0["+to<std::string>(i)+"][0]:frac0["+to<std::string>(i)+"][1]",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","FFPs without encounter",init.gets("selection")+"&&type==1","",1,1.7,5.3,1,0,1000,0,1,0.8,true,false);
      }
    }
  }

  
  if (init.getb("draw_vinf")){
    TChain *tc=new TChain("vinffit");
    TChain_LoadList(tc,parlist);
    //    MultiDraw(tc,dir,("vinfmax_h"+fig),parslist,"vmax:vmerr:h:herr",legend_rf,"v_{m}","N_{v#infty,max}",init.gets("selection"),"");
    MultiDraw(tc,dir,("vinfmax_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vmax:vmerr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","v_{m}",init.gets("selection")+"&&vmerr<0.5","",1,1.7,5.3,0,0,0,0,1);
  }

  if (init.getb("draw_vp")){
    TChain *tc=new TChain("vpfit");
    TChain_LoadList(tc,parlist);
    //    MultiDraw(tc,dir,("vpmax_h"+fig),parslist,"vmax:vmerr:h:herr",legend_rf,"v_{m}","N_{vp,max}",init.gets("selection"),"");
    MultiDraw(tc,dir,("vpmax_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vmax:vmerr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","v_{m}",init.gets("selection")+"&&vmerr<0.5","",1,1.7,5.3,0,0,0,0,1);
    MultiDraw(tc,dir,("vpmax_cut"+fig),parslist,"vmax:vmerr:vcut:vcerr",legend_rf,"v_{m}","v_{0}",init.gets("selection")+"&&vmerr<0.5&&vcerr<0.5","",1,1.5,6.0);
    MultiDraw(tc,dir,("vcut_lgrho"+fig),parslist,"log10((ns+nb)/rbar**3):ns:vcut:vcerr",legend_rf,"log(N_{sb}/r_{vir}^{3} [pc^{-3}])","v_{0}",init.gets("selection")+"&&vcerr<0.5&&vcut<5","",1,1.7,5.3,0,0,0,0,1);
  }

  if (init.getb("draw_nsnp")){
    TChain *tc=new TChain("nsnpfit");
    TChain_LoadList(tc,parlist);
    MultiDraw(tc,dir,("nsslope_offset"+fig),parslist,"vmax:vmerr:vcut:vcerr",legend_lf,"#alpha_{f}R_{f}(0)","R_{f}(0)",init.gets("selection"),"",1,-0.0019,-0.0005);
    MultiDraw(tc,dir,("scalensslope_offset"+fig),parslist,"vmax/vcut:vmax/vcut*sqrt((vmerr/vmax)**2+(vcerr/vcut)**2):vcut:vcerr",legend_lf,"#alpha_{f}","R_{f}(0)",init.gets("selection"),"",1,-0.0019,-0.0005);
  }
  
  std::cout<<"All Finish\n";
  return 0;
}
