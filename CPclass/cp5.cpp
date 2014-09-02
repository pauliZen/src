#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

void AX (double *x,double *ax, int nmax)
{
  *ax=202**x-200**(x+1);
  for (int i=1;i<=nmax-2;i++)
  {
    *(ax+i)=-200**(x+i-1)+402**(x+i)-200**(x+i+1);
  }
  *(ax+nmax-1)=200*(*(x+nmax-1)-*(x+nmax-2));
}

void gx (double *x,double *gx, int nmax)
{
  AX(x,gx,nmax);
  for (int i=0;i<=nmax-2;i++)
    *(gx+i) =-*(gx+i)+2;
  *(gx+nmax-1)=-*(gx+nmax-1);
}

double lamda (double *h,double *g,int nmax)
{
  double temp1=0;
  double temp2=0;
  double temp[100]={0};
  double *t=&temp[0];
  AX(h,t,nmax);
  for (int i=0;i<=nmax-1;i++)
  {
    temp1 +=*(h+i)**(g+i);
    temp2 +=*(h+i)**(t+i);
  }
  return temp1/temp2;
}


void hii (double *h,double *gii,double *gi, int nmax)
{
  double temp1=0;
  double temp2=0;
  double a=0;
  for (int i=0;i<=nmax-1;i++)
  {
    temp1 +=pow(*(gii+i),2);
    temp2 +=pow(*(gi+i),2);
  }
  a=temp1/temp2;
  for (int j=0;j<=nmax-1;j++)
    *(h+j)=*(gii+j)+a**(h+j);
}


void xnext (double *x, double lamda, int nmax, double *h, double *xnext)
{
  for(int i=0;i<=nmax-1;i++)
    *(xnext+i)=*(x+i)+*(h+i)*lamda;
}

double f(double *x,int nmax)
{
  double sum=0;
  for(int i=1;i<=nmax-1;i++)
    sum +=100*pow((*(x+i)-*(x+i-1)),2)+pow(1-*(x+i-1),2);
  return sum+1;
}

int main()
{
  double x[100];
  double xn[100];
  double *xi=&x[0];
  double *xii=&xn[0];
  double g[100];
  double gn[100];
  double h[100];
  double *gi=&g[0];
  double *gii=&gn[0];
  double *hi=&h[0];
  bool flag;
  int nmax;
  char cus;
  int precise;
  
  cout<<"Use CG method to find the minimum point and minimum value of the following function:\n"
      <<"f(x)=1+sum[100*(x(i)-x(i-1))^2+(1-x(i-1))^2](i=[2,n]).\n";
  cout<<endl<<"Please input the n noticed above, if input 0, n=10.(0 or 3<n<100):";
  cin>>nmax;
  if (nmax<=0)
    nmax=10;
  
  cout<<endl<<"Do you want to choose xi, if input \"y\", you can input xi, or xi=i/n.(y or n)";
  cin>>cus;
  if(cus=='y'||cus=='Y')
  {
    cout<<"Please input xi from 1 to "<<nmax<<":\n";
    for (int i=0;i<=nmax-1;i++)
    {
	  cout<<"x"<<i+1<<"=";
	  cin>>*(xi+i);
	}
    cout<<endl;
  }
  else for(int i=0;i<=nmax-1;i++)
         *(xi+i)=(i+1)/static_cast<double>(nmax);
  
  cout<<"\nPlease input the displayed precise:";
  cin>>precise;
  cout<<endl;
  
  for(int j=1;j<=nmax;j++)
  {
    if(j==1)
    {
      gx(xi,gii,nmax);
      xnext(xi,lamda(gii,gii,nmax),nmax,gii,xii);
      for(int i=0;i<=nmax-1;i++)
      {
        *(hi+i)=*(gii+i);
      }
    }
    else 
    {
      for(int i=0;i<=nmax-1;i++)
      {
        *(xi+i)=*(xii+i);
        *(gi+i)=*(gii+i);
      }
      gx(xi,gii,nmax);
      hii(hi,gii,gi,nmax);
      xnext(xi,lamda(hi,gii,nmax),nmax,hi,xii);
    }
  }
  
  cout<<"x="<<setprecision(precise)<<showpoint<<endl;
  for (int i=0;i<=nmax-1;i++)
  {
    cout<<"["<<setw(precise+3)<<*(xii+i)<<"]"<<endl;
  }
  cout<<"\nf="<<f(xii,nmax)<<endl<<endl;
  
  system("pause");
  return 0;
}
