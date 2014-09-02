#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <sstream>
#include <fstream>

using namespace std;

double calculate(map<int,double> m, int n, double t, double nx)  //A->B, from B(n) get A(n+1).
{
  return nx/(1/m[n+1]/(1/m[n]-1/m[n+1])*(exp(-1/m[n+1]*t)-exp(-1/m[n]*t)));
}

int main(int argc, char* argv[]) // (chain number, {lifetime, probability}, observated events, time, output filename)
{
  //================================================================//
  //parameter================================================//

  stringstream sstr;
  int nlink=8;
  bool flagf=1;
  map<int,double> decay;
  map<int,double> weight;
  int events;
  ofstream dout;
  string outputfile="decay_calculation.txt";
  double timed;
  
  
  //input================================================//
  if (argc!=1)
  {
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>nlink;
    sstr.str("");
    sstr.clear();

    for(int i=0;i<2*nlink; i +=2)
    {
      sstr<<argv[i+2];
      sstr>>decay[i];
      sstr.str("");
      sstr.clear();
      sstr<<argv[i+3];
      sstr>>weight[i];
      sstr.str("");
      sstr.clear();
    }

    sstr<<argv[2*nlink+2];
    sstr>>events;
    sstr.str("");
    sstr.clear();


    sstr<<argv[2*nlink+3];
    sstr>>timed;
    sstr.str("");
    sstr.clear();

    sstr<<argv[2*nlink+4];
    sstr>>outputfile;
    sstr.str("");
    sstr.clear();

    flagf=0;
  }
  
  if(flagf)
  {
    char flag;
    cout<<"Custom parameters, or U234(y or n):";
    cin>>flag;
    if(flag!='n')
    {
      while(flagf)
      {
        cout<<"cascade decay times:";
        cin>>nlink;
        if (nlink>0)
          flagf=0;
        else
        {
          flagf=1;
          cout<<"Error"<<endl;
        }
      }
      
      for (int i=0;i<nlink;i++)
      {
        flagf=1;
        while(flagf)
        {
          cout<<"mean lifetime "<<i+1<<"(unit:second):";
          cin>>decay[i];
          if (decay[i]>0)
            flagf=0;
          else
          {
            flagf=1;
            cout<<"Error"<<endl;
          }
        }

        while(flagf)
        {
          cout<<"probability of decay mode "<<i+1<<":";
          cin>>weight[i];
          if (weight[i]>0&&weight[i]<=1)
            flagf=0;
          else
          {
            flagf=1;
            cout<<"Error"<<endl;
          }
        }
        
      }
      
    }

    else
    {
      decay[0]=164.3e-6; //Po214 a
      weight[0]=1;
      decay[1]=19.7*60;    //Bi214 b-
      weight[1]=0.998;
      decay[2]=26.4*60;  //Pb214 b-
      weight[2]=1;
      decay[3]=3.05*60;   //Po218 a
      weight[3]=1;
      decay[4]=3.82*24*3600; //Rn222 a
      weight[4]=1;
      decay[5]=1602.0*365*24*3600; //Ra226 a
      weight[5]=1;
      decay[6]=80000.0*365*24*3600; //Th234 a
      weight[6]=1;
      decay[7]=247000.0*365*24*3600; //U234 a
      weight[7]=1;
    }

    flagf=1;
    while(flagf)
    {
      cout<<"Observated events number:";
      cin>>events;
      if(events>0)
        flagf=0;
      else
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }

    flagf=1;
    while(flagf)
    {
      cout<<"Observation run time:";
      cin>>timed;
      if(timed>0)
        flagf=0;
      else
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }

    cout<<"Output file directory and name:";
    cin>>outputfile;

  }
  
  dout.open(outputfile.c_str());

  //================================================================//
  //test================================================//
  
  for(int i=0;i<nlink;i++)
    cout<<"Decay lifetime "<<nlink-i<<":"<<decay[i]<<endl;
  
  //================================================================//
  
  //calculation================================================//

  int *now=new int [nlink+1];
  now[0]=events;

  for(int i=0;i<nlink;i++)
  {
    now[i+1]=calculate(decay,i,timed,now[i]);
    cout<<"Numbers of atoms at Decay Chain "<<nlink-i<<":"<<now[i+1]<<endl;
    dout<<"Numbers of atoms at Decay Chain "<<nlink-i<<":"<<now[i+1]<<endl;
  }
  
  dout.close();
  delete [] now;
  return 0;
  
}
