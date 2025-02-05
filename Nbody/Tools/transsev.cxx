#include <stdio.h>
#include <initial.h>
#include <uftools.h>
#include <string>

#define width 65

int main(int argc, char *argv[])
{
  pars_initial init(".trans83_config");
  init.add("file","file to scan","fort.83");
  init.add("begin","begin of the time",(float)0);
  init.add("steps","time step of output",(float)1.0);
  init.add("end","end of the time",(float)1000);
  init.add("prefix","new file prefix","fort.83_");
  init.initial(argc,argv);

  FILE *stream;
  std::string name=init.gets("file");
  if ( (stream = fopen(name.c_str(), "r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s. \n",name.c_str() );
    return 0;
  }
  float tcount=init.get<float>("begin");
  float tend=init.get<float>("end");
  bool flag=true;
  std::string oformat="%"+to<std::string>(width)+"s";
  std::string iformat="%"+to<std::string>(width-3)+"c";
  while (!feof(stream)) {
    int lnum;
    float time;
    char a1[10],a2[10],atmp[1];
    fscanf(stream,"%d %f",a1,a2,&lnum,&time);
    fscanf(stream,"%c",atmp);
    if (feof(stream)){
      printf("Reach End\n");
      break;
    }
    if (strcmp(a1,"##")||strcmp(a2,"BEGIN")) {
      fprintf(stderr,"Error: begin not match (%s %s)!\n",a1,a2);
      flag=false;
    }
    if (!flag) {
      while (true){
        char aa2[80];
        while (true) {
          char aa1[80];
          fscanf(stream,"%s",aa1);
          if (!strcmp(aa1,"##")) break;
          if (feof(stream)) {
            fprintf(stderr,"Reach the end, stop!\n");
            return 0;
          }
        }
        fscanf(stream,"%s",aa2);
        if (!strcmp(aa2,"BEGIN")) break;
      }
      fscanf(stream,"%d %f",&lnum,&time);
      fscanf(stream,"%c",atmp);
      flag=true;
    }
    if (time>tend) {
      fprintf(stdout,"Finished\n");
      break;
    }
    if (time>=tcount) {
      fprintf(stdout,"Now time: %f , N: %d\n",time,lnum);
      FILE *fnew;
      if ( (fnew = fopen((init.gets("prefix")+to<std::string>(time)).c_str(), "w")) == NULL) {
        fprintf(stdout,"Error: Cannot create new file %f.\n",time);
        return 0;
      }
      fprintf(fnew,"%f\n",time);
      //      int totc=width*lnum;
      //      std::string iformat="%"+to<std::string>(totc)+"c";
      //      std::string oformat="%"+to<std::string>(totc)+"s";
      //      char *str=new char[width*lnum+10];
      //      std::string iformat="%"+to<std::string>(width-3)+"c";
      while(true){
        //for (int i=0;i<lnum;i++) {
        char str[100];
        fscanf(stream,"%3c",str);
        if (str[2]=='#') break;
        fscanf(stream,iformat.c_str(),str);
        fprintf(fnew,oformat.c_str(),str);
        //        fprintf(stdout,oformat.c_str(),str);
      //      delete str;
      }
      fscanf(stream,"%s %d",a2,&lnum);
      fscanf(stream,"%c",atmp);
      tcount +=init.get<float>("steps");
      fclose(fnew);
    }
    else {
      fprintf(stdout,"Pass time: %f , N: %d\n",time,lnum);
      //      int totc=width*lnum;
      //      std::string format="%*"+to<std::string>(totc)+"c";
      while (true){
        char tmp[100];
        fscanf(stream,"%3c",tmp);
        if (tmp[2]=='#') break;
        fscanf(stream,iformat.c_str(),tmp);
      }
      fscanf(stream,"%s %d",a2,&lnum);
      fscanf(stream,"%c",atmp);
    }
  }

  fclose(stream);
  
  return 0;
}
