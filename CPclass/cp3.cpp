#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

long double function_1(long double x)				//function f(x)=2x+3x^2+4x^3
{
  return 2*x+3*x*x+4*x*x*x;
}
long double function_2(long double x)				//function f(x)=e^-x
{
  return 1.0/exp(x);
}
long double function_1D(long double x)				//the differential coefficient of f(x)=2x+3x^2+4x^3
{
  return 6*x+12*pow(x,2);
}
long double function_3(long double x)				//function f(x)=(2*Pi)^-2*Exp(-x^2)
{
  return pow(2*3.1415926,-0.5)*exp(-pow(x,2));
}
long double function_3DDD(long double x)			//the multiple derivative of 3 degree to f(x)=(2*Pi)^-2*Exp(-x^2)
{
  return pow(2*3.1415926,-0.5)*(12*exp(-pow(x,2))*x-8*exp(-pow(x,2))*pow(x,3));
}

long double fun_sum(long double x,int n, bool flag,int choose)    //function for approximation to estimate the integral of function_1/2
{
  long double sum=0;
  long double interval=1/static_cast<double>((choose==3?2:1)*n);
  for(int j=0 ; j<=n ; j++)
    {
      switch (choose)
	{
	case 2:
	  sum +=(j==0||j==n?0.5:1)*(flag==1?function_1(x+j*interval):function_2(x+j*interval));
	  break;
	case 1:
	  sum +=(flag==1?function_1(x+(j-0.5)*interval):function_2(x+(j-0.5)*interval))*(j==0?0:1);
	  break;
	case 3:
	  if (flag&&j!=n)
	    sum +=function_1(x+2*j*interval)+4*function_1(x+(2*j+1)*interval)+function_1(x+2*(j+1)*interval);
	  else if (j!=n)
	    sum +=function_2(x+2*j*interval)+4*function_2(x+(2*j+1)*interval)+function_2(x+2*(j+1)*interval);
	  break;
	}
    }
  return (choose==3?(1.0/3.0):1.0)*sum*interval;
}
long double fun_3(long double x,int n)				//function for Simpson's rule to estimate the integral of function_3
{
  long double sum=0;
  long double interval=2*x/static_cast<double>(2*n);
  for(int j=0;j<n;j++)
    {
      sum +=function_3(-x+2*j*interval)+4*function_3(-x+(2*j+1)*interval)+function_3(-x+2*(j+1)*interval);
    }
  return 1.0/3.0*sum*interval;
}

long double fun_error(long double x,int n,bool flag,int choose)		//Error estimation for fun_sum
{
  long double sum=0;
  long double num=(choose==3?2:1)*n;
  long double interval=1/num;
  
  for (int j=1; j>=0;j--)
    {
      switch (choose)
	{
	case 2:
	  sum +=(j==0?-1:1)*(flag==1?function_1D(x+j):-function_2(x+j));
	  break;
	case 1:
	  sum +=(j==0?-1:1)*(flag==1?function_1D(x+j):-function_2(x+j));
	  break;
	case 3:
	  sum +=(j==0?-1:1)*(flag==1?0:-function_2(x+j));
	  break;
	}
    }
  switch (choose)
    {
    case 1: return sum/(24*pow(num,2));break;
    case 2: return -sum/(12*pow(num,2));break;
    case 3: return -sum/(180*pow(num,4));break;
    }
}

long double fun_3error(long double x,int n)				//error estimation for fun_3
{
  long double sum=0;
  sum =(function_3DDD(x)-function_3DDD(-x))/(2*x);
  return -pow((2*x),5)*sum/(180*pow(2*static_cast<double>(n),4));
}

int main()
{
  int n=0;				//numbers of panels
  bool flag=1;
  const string style[3]={"mid-point","trapezoidal","Simpson's rule"};
  const string fun[3]={"f(x)=2x+3x^2+4x^3","f(x)=e^-x","f(x)=(2*Pi)^-2*Exp(-x^2)"};
  for (int i=0;i<2;i++)				//loop statement for choosing one f(x) each time
    {
      for (int cho=0;cho<3;cho++)	//loop statement for choosing one approximation mean each time
	{
	  cout<<"Use the "<<style[cho]<<" apporximation to estimate the definite integrals of "<<fun[1-flag]<<" from 0 to 1;\n"
	      <<"Please input the n of panels:";
	  cin>>n;
	  if(cho==3) n=n/2;
	  cout<<"Result:"<<fun_sum(0,n,flag,cho+1)<<"     ";
	  cout<<"Error Estimation of "<<style[cho]<<" is:"<<fun_error(0,n,flag,cho+1)<<endl<<endl;
	}
      cout<<endl;
      flag=0;
    }

  for(int x=1;x<=3;x++)				//loop statement for choosing interval of function_3.
    {
      cout<<"Use the "<<style[2]<<" apporximation to estimate the definite integrals of "<<fun[2]<<" from "<<-x<<" to "<<x<<";\n"
	  <<"Please input the n of panels:";
      cin>>n;
      n=n/2;
      cout<<"Result:"<<fun_3(x,n)<<"     ";
      cout<<"Error Estimation of "<<style[2]<<" is:"<<fun_3error(x,n)<<endl<<endl;
    }

  system("pause");
  return 0;
}
