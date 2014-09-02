#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

double f(double t,double y)
{
  return -2*t*y;
}

double result(double t,int i,int c,double y,double *g,double yb)
{
  double re;
  switch(c)
  {
  case 0:
    re=y+f(t*i,y)*t;
    *(g+i)=re/y;
    return re;
    
  case 1:
    if(i==0)
      re=y+t*f(t*i,y);
    else
      re=y+t/2*(3*f(t*i,y)-f(t*(i-1),yb));
    re=y+t/2*(f(t*(i+1),re)+f(t*i,y));
    return re;
    
  case 2:
    double k1=t*f(t*i,y);
    double k2=t*f(t*(i+0.5),y+0.5*k1);
    double k3=t*f(t*(i+0.5),y+0.5*k2);
    double k4=t*f(t*(i+1),y+k3);
    re= y+1.0/6.0*(k1+2*k2+2*k3+k4);
    *(g+i)=re/y;
    return re;
  }
}

int main()
{
  double t;
  double y=1;
  double yb=1;
  char c1;
  char cg;
  double g[100];
  double *gi=&g[0];
  int precision;
  string method[3]=
    {
      "EC","PC","RK"
    };
  cout<<"This is the program to calculate the function y'=-2ty,y(0)=1";
  cout<<endl;
  cout<<"Please input the displayed precision:";
  cin>>precision;
  cout<<setprecision(precision)<<endl;

  for(int c=0;c<=2;c++)
  {
    cout<<"Use "<<method[c]<<" method:";
    if(c<2)t=0.2;
    else t=0.4;
    y=1;
    
    cout<<"Would you want to change time step? If input \"n\", step is "<<t<<".(y or n):";
    cin>>c1;
    if (c1=='y'||c1=='Y')
      cin>>t;
    
    cout<<endl<<"The result by "<<method[c]<<" is:"<<endl;
    for(int i=0;i*t<1.2;i++)
    {
      if(i==0)
      {
        cout<<"t|";
        for(int j=0;j*t<=1.2000001;j++)
        {
          cout<<setw(precision+4)<<j*t;
          if((j+1)%4==0)cout<<endl<<"  ";
        }
        cout<<endl;
        cout<<"y|";
        cout<<setw(precision+4)<<y;
      }
      y=result(t,i,c,y,g,yb);
      yb=y;
      cout<<showpoint<<setw(precision+4)<<y<<noshowpoint;
      if ((i+2)%4==0) cout<<endl<<"  ";
    }
    cout<<endl<<endl;
    if(c!=1)
    {
      cout<<"Would you wang to see the stability parameter g?(y or n)";
      cin>>cg;
      if(cg=='Y'||cg=='y')
      {
        cout<<setw(4)<<"n"<<setw(precision+4)<<"gi"<<endl;
        for(int i=0;i*t<1.2;i++)
        {
          cout<<setw(4)<<(i+1)<<setw(precision+4)<<*(g+i)<<endl;
        }
      }
      cout<<endl;
    }
    
  }
  system("pause");
  return 0;
}
