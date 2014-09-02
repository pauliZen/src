#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "initial.h"

using namespace std;

int main(int argc, char *argv[])
{
  pars_initial inipars(".ini.config");
  inipars.add("test3","Test intro 3 double",0.000003);
  inipars.add("test2","Test intro 2 integer",20);
  inipars.add("test1","Test intro 1 integer",100);
  inipars.add("test4","Test intro 4 double",100.03);
  inipars.add("test5","Test intro 5 string","initial_5");
  inipars.add("test6","Test intro 6 string","initial_6");

  inipars.initial(argc,argv);

  pars_initial int2(".ini2.config",inipars.getnextargc());
  int2.add("kke","ddkskd dd","dfd");
  int2.initial(argc,argv);

  string tt;
  int ll;
  double dd;
  tt=inipars.gets("tst3");
  dd=inipars.getd("test3");
  ll=inipars.geti("test3");

  cout<<setprecision(10)<<tt<<"\t"<<dd<<"\t"<<ll<<endl;
  cout<<"finished"<<endl;
  return 0;
}
