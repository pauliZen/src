#include <string>
#include <iostream>
#include <fstream>
#include <uftools.h>
#include <nbodystep3.h>
#include <initial.h>

int main(int argc, char *argv[])
{
  pars_initial opt(".draw_choose");
  opt.add("opt","hnps:tex","hnps");
  opt.add("filelist","root file number to chain","step3.lst");
  opt.initial(argc,argv);

  nbodystep3 stp;
  stp.LoadList(opt.gets("filelist"));
    
  std::string option=opt.get<std::string>("opt");
  std::string configfile;
  if (option=="hnps") configfile=".draw_hnps_config";
  else if (option=="tex") configfile=".draw_tex_config";
  
  pars_initial ini(configfile,opt.getnextargc());
  if (option=="hnps")
  {
    ini.add("figpath","Directory to store figures","/home/lwang/Dropbox/Datas/Planets/");
    ini.add("figname","Figure name prefix","test.eps");
    ini.add("parlist","pars list file name: selname, seltype, selrange, selnum, selvalue","pars.list");
    ini.add("option","option for draw, 0: half time, 1: half time ratio",(int)0);
  }
  else if (option=="tex")
  {
    ini.add("texname","tex file name","cetable.tex");
    ini.add("configure","configure file, format: hnum, tnum, hlist, tlist","tex.config");
  }
  ini.initial(argc,argv);
  
  if (option=="hnps") stp.Drawhps(ini.get<std::string>("figpath"),ini.get<std::string>("figname"),ini.get<std::string>("parlist"),ini.get<int>("option"));
  else if (option=="tex")
  {
    ifstream fs(ini.gets("configure").c_str());
    if (!fs.is_open())
    {
      std::cerr<<"Error: tex configure file not found!\n";
      return 0;
    }
    int tnum,hnum,snum;
    fs>>hnum;
    fs>>tnum;
    fs>>snum;
    std::string *tablelist=new std::string[tnum];
    std::string *headlist=new std::string[hnum];
    for (int i=0;i<hnum;i++) fs>>headlist[i];
    for (int i=0;i<tnum;i++) fs>>tablelist[i];
    if (snum)
    {
      std::string *selection=new std::string[snum];
      for (int i=0;i<tnum;i++) fs>>selection[i];
      stp.MakeTexTable(ini.gets("texname"),tnum,tablelist,hnum,headlist,snum,selection);
    }
    else
    {
      std::string *selection=new std::string;
      selection[0]="";
      stp.MakeTexTable(ini.gets("texname"),tnum,tablelist,hnum,headlist,1,selection);
    }
  }
  std::cout<<"Finished\n";
  return 0;
}
