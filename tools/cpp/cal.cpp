#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main (int argc, char* argv[])
{
  stringstream sstr;
  double *Value=new double[argc];
  string opt;
  double output=0;

  switch (argc)
  {
  case 1:
    cout<<"Need input: Operator Value1 Value2 ..."<<endl;
    return 0;
  case 2:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>opt;
    if (opt=="--help"||opt=="-h")
    {
     cout<<"-----------------------------------------------------"<<endl;
      cout<<"[operator] [Value1] [Value2] ..."<<endl;
      cout<<"-----------------------------------------------------"<<endl;
      cout<<"Operator:"<<endl<<"+: plus"<<endl<<"-: minus"<<endl<<"*: multiply"<<endl<<"/: devide by"<<endl<<"**: power of"<<endl
          <<"log: log"<<endl<<"sqrt: sqrt"<<endl<<"log10: log10"<<endl;
      cout<<"-----------------------------------------------------"<<endl;
      cout<<"Second Char:"<<endl<<"p: setprecision, first number should be integer, meaning the number of precision"<<endl
	  <<"n: Integer calculation"<<endl;
      cout<<"-----------------------------------------------------"<<endl;
      return 0;
    }
    else
    {
      cout<<"Need input: Operator Value1 Value2 ..."<<endl;
      return 0;
    }
    break;
  case 3:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>opt;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>Value[0];

    if (opt=="sqrt"||opt=="log"||opt=="log10")
      break;
    else
    {
      cout<<"Not enough input, need Value2"<<endl;
      return 0;
    }
    break;

  default:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>opt;
    for (int i=0;i<argc-2;i++)
    {
      sstr.str("");
      sstr.clear();
      sstr<<argv[2+i];
      sstr>>Value[i];
    }
    break;
  }

  double temp=Value[0];
  int tempN=Value[0];
  bool flag=1;

  for (int i=1;i<argc-2;i++)
  {
    if (i==1&&opt[opt.size()-1]=='p') temp=Value[1];
    else if (opt[opt.size()-1]=='n')
    {
      if (opt[0]=='+') tempN +=Value[i];
      if (opt[0]=='-') tempN -=Value[i];
      if (opt[0]=='*') tempN *=Value[i];
      if (opt[0]=='/') tempN /=Value[i];
    }
    else
    {
      if (opt[0]=='+') temp +=Value[i];
      if (opt[0]=='-') temp -=Value[i];
      if (opt[0]=='*') temp *=Value[i];
      if (opt[0]=='/') temp /=Value[i];
    }
  }
  if (opt.size()>=2&&opt.substr(0,1)=="**") temp=pow(Value[0],Value[1]);
  if (opt.size()>=4&&opt.substr(0,3)=="sqrt") temp=sqrt(Value[0]);
  if (opt.size()>=3&&opt.substr(0,2)=="log") temp=log(Value[0]);
  if (opt.size()>=5&&opt.substr(0,4)=="log10") temp=log10(Value[0]);

  if (opt[opt.size()-1]=='n') flag=0;
  if (opt[opt.size()-1]=='p') cout<<setprecision(static_cast<int>(Value[0]))<<showpoint;

  if (flag) cout<<temp<<endl;
  else cout<<tempN<<endl;
  return 0;
}
