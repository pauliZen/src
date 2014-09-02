#include <nbodystdout.h>
#include <initial.h>

int main (int argc, char *argv[])
{
  pars_initial init(".test_draw_bh");
  init.add("rootlist","rootlist to chain","rootlist.lst");
  init.initial(argc,argv);

  nbodystdout *st=new nbodystdout("star");
  st->LoadList(init.get<std::string>("rootlist"));

  return 0;
}
