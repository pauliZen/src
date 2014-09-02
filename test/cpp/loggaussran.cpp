#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const double pi=3.1415926;

double Random_LogNormalFunction(double mean, double deviation, double randomx, double randomy)
{
  double x=sqrt(-2*log(1-randomx))*cos(2*pi*randomy);
  double R=exp(deviation*x+mean);
  return R;
}

double Random_NormalFunction(double mean, double deviation, double randomx,double randomy)
{
  double x=sqrt(-2*log(1-randomx))*cos(2*pi*randomy);
  double Rn=deviation*x+mean;
  return Rn;
}

int main(int argc,char* argv[])
{
  double sf=0;
  double rf=0;
  double randomx=0;
  double randomy=0;
  double sf_m=6.20463;
  double sf_d=0.09975;
  double rf_m=600;
  double rf_d=60;
  double N1=0;
  double N=100000;
  double R=0;
    
  stringstream sstr;
  sstr.str("");
  sstr.clear();

  if (argc!=1)
    {
      sstr<<argv[1];
      sstr>>sf_m;
      sstr.str("");
      sstr.clear();

      sstr<<argv[2];
      sstr>>sf_d;
      sstr.str("");
      sstr.clear();

      sstr<<argv[3];
      sstr>>rf_m;
      sstr.str("");
      sstr.clear();

      sstr<<argv[4];
      sstr>>rf_d;
      sstr.str("");
      sstr.clear();
    }
  else
    {
	  cout<<"Defaulted?(y,n)";
	  char flag='n';
	  cin>>flag;
	  if(flag=='y') 
		  cout<<"Stress("<<sf_m<<","<<sf_d<<"); Intension("<<rf_m<<","<<rf_d<<")"<<endl;
	  else
	  {
      cout<<"Parameters Input:"<<endl;
      cout<<"Stress mean:";
      cin>>sf_m;
      cout<<"Stress deviation:";
      cin>>sf_d;
      cout<<"Intension mean:";
      cin>>rf_m;
      cout<<"Intension deviation:";
      cin>>rf_d;
	  }
    }

  srand( time(NULL));

  for(int j=0;j<N;j++)
    {
      randomx=rand()/(double)RAND_MAX;
      randomy=(rand()/(double)RAND_MAX);
      rf=Random_NormalFunction(rf_m,rf_d,randomx,randomy);
      randomx=rand()/(double)RAND_MAX;
      randomy=(rand()/(double)RAND_MAX);
      sf=Random_LogNormalFunction(sf_m,sf_d,randomx,randomy);
      if(rf>sf) N1++;
    }

  cout<<"Result After "<<N<<" cycles: "<<N1/N<<endl;
  system("pause");  
  return 0;
}
