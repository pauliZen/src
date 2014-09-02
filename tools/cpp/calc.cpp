#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <string>

#include "initial.h"

using namespace std;

template <typename T>
T opert(const string &op,const T& a,const T& b)
{
  if (op=="*") return a*b;
  if (op=="+") return a+b;
  if (op=="-") return a-b;
  if (op=="/") return a/b;
  if (op=="%") return (int)a%(int)b;
  if (op=="**") return pow(a,b);
  if (op=="sqrt") return sqrt(a);
  if (op=="log") return log(a);
  if (op=="log10") return log10(a);
  else cerr<<"Error!: \'"<<op<<"\' operator not found!"<<endl;
  exit(1);
}

template <typename T>
string tostring(const T& data)
{
  string temp;
  stringstream sstt;
  sstt.str("");
  sstt.clear();
  sstt<<data;
  sstt>>temp;
  return temp;
}

bool check(const string& opt)
{
  vector<string> list1;
  list1.push_back("log");
  list1.push_back("log10");
  list1.push_back("sqrt");
  for (vector<string>::iterator i=list1.begin(); i!=list1.end();i++)
  {
    if (opt==*i) return 1;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  pars_initial tablepars(".calc_last");
  tablepars.add("opt","operator","");
  for (int i=1;i<argc-1;i++)
  {
    string index=tostring(i);
    tablepars.add(("value"+index).c_str(),"parameters",0.0);
  }
  tablepars.initial(argc,argv,1,0);

  //Help==============================================//
  string option=tablepars.get<string>("opt");
  if (option=="--help")
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
  }
  else
  {
    int optlength=0,varlength=0;
    bool outint=0;
    double out=0;
    string ind[2];
    switch (*(option.end()-1))
    {
    case 'p':
      cout<<setprecision(tablepars.get<int>("value1"))<<showpoint;
      optlength=1;
      varlength=1;
      break;
    case 'n':
      optlength=1;
      varlength=0;
      outint=1;
      break;
    default:
      optlength=0;
      varlength=0;
      break;
    }
    ind[0]=tostring(1+varlength);
    ind[1]=tostring(2+varlength);
    if (argc==2+varlength)
    {
      cerr<<"Error: No input value for calculation!\n";
      exit(1);
    }
    else if (argc==3+varlength)
    {
      if (check(option.substr(0,option.size()-optlength)))
      {
        out=opert(option.substr(0,option.size()-optlength),tablepars.get<double>(("value"+ind[0]).c_str()),0.0);
      }
      else
      {
        cerr<<"Error: Input incomplete!\n";
        exit(1);
      }
    }
    else
    {
      out=opert(option.substr(0,option.size()-optlength),tablepars.get<double>(("value"+ind[0]).c_str()),tablepars.get<double>(("value"+ind[1])));
      if (argc>4+varlength)
        for (int i=5+varlength;i<=argc;i++)
          out=opert(option.substr(0,option.size()-optlength),out,tablepars.get<double>(("value"+tostring(i-2)).c_str()));
    }
    if (outint)
    {
      if (out-static_cast<int>(out)>=0.5)
        cout<<static_cast<int>(out)+1<<endl;
      else if(out-static_cast<int>(out)<=-0.5)
        cout<<static_cast<int>(out)-1<<endl;
      else
        cout<<static_cast<int>(out)<<endl;
    }
    else
      cout<<out<<endl;
  }                

  return 0;
}
