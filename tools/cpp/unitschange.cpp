#include<map>
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<cmath>
#include<utility>
using namespace std;
void calculation(double value, string units);

int main(int argc,char* argv[])
{
  int sel=1;
  string str;
  int bin=10;
  double min=1;
  double max=100;
  stringstream sstr(str);
  double value;
  string units;

  if(argc==2)
  {
    sel=1;
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr.clear();
    sstr>>value;
    sstr.clear();
    sstr>>units;
    sstr.str("");

  }
  else if(argc==5)
  {
    sel=2;
    
    sstr.str("");
    sstr.clear();

    sstr<<argv[1];
    sstr>>bin;
    sstr.str("");
    sstr.clear();

    sstr<<argv[2];
    sstr>>min;
    sstr.str("");
    sstr.clear();

    sstr<<argv[3];
    sstr>>max;
    sstr.str("");
    sstr.clear();
  }
  else
  {
    bool flag=1;
    while(flag)
    {
      cout<<"Input value style:(1,single value;2,range(bin,min,max))";
      cin>>sel;
      if(sel<1||sel>2)
      {
        cout<<sel<<": error value\n";
      }
      else
        flag=0;
    }
    if(sel==1)
    {
      cout<<"Input value(energy,temperature,mass,wavelength or frequency):";
      sstr.str("");
      sstr.clear();
      cin>>str;
      sstr<<str;
      sstr>>value;
      sstr.clear();
      sstr>>units;
      sstr.str("");
    }
    if(sel==2)
    {
      cout<<"Input number of division(bin):";
      cin>>bin;
      cout<<"Input minimum value(energy,temperature,mass,wavelength or frequency):";
      cin>>min;
      cout<<"Input maximum value(energy,temperature,mass,wavelength or frequency):";
      cin>>max;
      cout<<"Units:";
      cin>>units;
      
    }
  }

  if(sel==1)
    calculation(value,units);
  else if(sel==2)
  {
    cout<<"Calculation range: from "<<min<<units<<" to "<<max<<units<<" \nndivision: "<<bin<<endl;
    double step=(max-min)/(double)bin;
    for(double i=min;i<=max;i +=step)
    {
      calculation(i,units);
      cout<<endl;
    }
  }
  return 0;
}

  
void calculation(double value, string units)
{
  
  map<string,double> un;
  map<string,double> sig;
  map<string,double> unit;
  map<string,pair<string,double> > res;
  
  map<string,double>::iterator i_un;
  map<string,double>::iterator i_sig;
  map<string,double>::iterator i_unit;
  map<string,pair<string,double> >::iterator i_res;
  

  const double kb=1.3806505E-23;  //units: J/K;
  const double e=1.60217733E-19;  //units: C;
  const double h=6.6260755E-34;   //Units: J*s;
  const double c=2.99792458E8;    //units: m/s;
  
    
  sig["k"]=sig["K"]=1000;
  sig["M"]=1.E6;
  sig["n"]=1.E-9;
  sig["m"]=1.E-3;
  sig["u"]=1.E-6;
  sig["T"]=1.E12;
  sig["G"]=sig["g"]=1.E9;
  sig["p"]=1.E-12;
  sig["f"]=1.E-15;
  sig["P"]=1.E15;

  //Transmit to J;
  un["eV"]=un["ev"]=e;
  un["K"]=3/2*kb;
  un["J"]=1.0;
  un["g"]=1.0*c*c/1000;
  un["Hz"]=un["hz"]=h;
  un["m"]=h*c;
  
    
  for (i_un =un.begin(); i_un !=un.end(); i_un++)
  {
    for (i_sig =sig.begin(); i_sig !=sig.end(); i_sig++)
    {
      unit[(i_sig->first)+(i_un->first)]=(i_sig->second)*(i_un->second);
      if (i_un->first=="m")
        unit[(i_sig->first)+(i_un->first)]=1/(i_sig->second)*(i_un->second);
    }
    unit[i_un->first]=i_un->second;
  }

 
  for(i_sig=sig.begin(); i_sig !=sig.end(); i_sig++)
  {
    if (units==((i_sig->first)+"m")) value=1.0/value;
  }
  

  res["Energy(eV)"].first="eV";
  res["Energy(eV)"].second=value*unit[units]/unit["eV"];
  res["Energy(J)"].first="J";
  res["Energy(J)"].second=value*unit[units];
  res["wavelength"].first="m";
  res["wavelength"].second=1/(value*unit[units])*unit["m"];
  res["frequency"].first="Hz";
  res["frequency"].second=value*unit[units]/unit["Hz"];
  res["mass"].first="g";
  res["mass"].second=value*unit[units]/unit["g"];
  res["temperature"].first="K";
  res["temperature"].second=value*unit[units]/unit["K"];

  cout<<setw(12)<<"Parameter"<<setw(16)<<"Value"<<setprecision(10)<<setw(6)<<"unit"<<setw(16)<<"Value"<<setw(6)<<"unit"<<endl;

  for(i_res=res.begin();i_res !=res.end(); i_res++)
  {
    float n=log10((i_res->second).second);
    cout<<setw(12)<<i_res->first<<setw(16)<<(i_res->second).second<<setw(6)<<(i_res->second).first;
    
    if (n<=-12) cout<<setw(16)<<(i_res->second).second*1.E15<<setw(3)<<"f"<<(i_res->second).first<<endl;
    else if (n>-12&&n<=-9) cout<<setw(16)<<(i_res->second).second*1.E12<<setw(3)<<"p"<<(i_res->second).first<<endl;
    else if (n>-9&&n<=-6) cout<<setw(16)<<(i_res->second).second*1.E9<<setw(3)<<"n"<<(i_res->second).first<<endl;
    else if (n>-6&&n<=-3) cout<<setw(16)<<(i_res->second).second*1.E6<<setw(3)<<"u"<<(i_res->second).first<<endl;
    else if (n>-3&&n<=0) cout<<setw(16)<<(i_res->second).second*1.E3<<setw(3)<<"m"<<(i_res->second).first<<endl;
    else if (n>0&&n<3) cout<<setw(16)<<(i_res->second).second<<setw(3)<<" "<<(i_res->second).first<<endl;
    else if (n>=3&&n<6) cout<<setw(16)<<(i_res->second).second*1.E-3<<setw(3)<<"k"<<(i_res->second).first<<endl;
    else if (n>=6&&n<9) cout<<setw(16)<<(i_res->second).second*1.E-6<<setw(3)<<"M"<<(i_res->second).first<<endl;
    else if (n>=9&&n<12) cout<<setw(16)<<(i_res->second).second*1.E-9<<setw(3)<<"G"<<(i_res->second).first<<endl;
    else if (n>=12&&n<15) cout<<setw(16)<<(i_res->second).second*1.E-12<<setw(3)<<"T"<<(i_res->second).first<<endl;
    else if (n>=15) cout<<setw(16)<<(i_res->second).second*1.E-15<<setw(3)<<"P"<<(i_res->second).first<<endl;
  }
  
}
