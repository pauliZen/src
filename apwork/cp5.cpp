#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

void initiala(double *x,double *y,double A[256][256],int m,int n)
{
	*(x+m/2*n+n/2)=255;
	*(x+m/4*n+n/3)=255;
	*(x+m/5*n+n/4)=255;
	*(x+m/5*3*n+n/3)=255;
	for(int i=0;i<m*n;i++)
	{
		*(y+i)=0;
		for(int j=0;j<m*n;j++)
			*(y+i) +=*(x+j)*A[i][j];
	}
}

double f(int x,int y,double pij,int m)
{
	double r=sqrt(static_cast<double>(x*x+y*y));
	double a=r;
	double thi=atan(y/static_cast<double>(x));
	if (a==0) return pij;
	else return pij*pow(sin(a)/a,2);
}


void makeA(double A[256][256],int m,int n)
{
	int nmax=m*n;
	for(int k=0;k<nmax;k++)
		for(int p=0;p<nmax;p++)
		{
			A[k][p]=f(k/n-p/n,k%n-p%n,1,m);
		}
}

void AX (double *x,double *ax,int nmax,double A[256][256])
{
  for (int i=0;i<nmax;i++)
  {
	  *(ax+i)=0;
	  for (int j=0;j<nmax;j++)
	  {
		  *(ax+i) +=A[i][j]*(*(x+j));
	  }
  }
}

void gx (double *x,double *gx,int nmax,double *b,double A[256][256])
{
//  double *gt=new double[nmax];
  AX(x,gx,nmax,A);
  for (int i=0;i<nmax;i++)
    *(gx+i) =-(*(gx+i)-*(b+i));
/*  for (int i=0;i<nmax;i++)
  {
	  *(gx+i)=0;
	  for(int j=0;j<nmax;j++)
		  *(gx+i) +=-(*(gt+i));
  }
 */// delete []gt;
}

double lamda (double *h,double *g,int nmax,double A[256][256])
{
  double temp1=0;
  double temp2=0;
  double *t=new double[nmax];
  AX(h,t,nmax,A);
  for (int i=0;i<=nmax-1;i++)
  {
    temp1 +=*(h+i)**(g+i);
    temp2 +=*(h+i)**(t+i);
  }
  delete []t;
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


void trans(double *x,double *b,double *xn,int m,int n)
{
  int nmax=m*n;
  double *xi=new double[nmax];
  double *xii=new double[nmax];
  double *gi=new double[nmax];
  double *gii=new double[nmax];
  double *hi=new double[nmax];
  double FA[256][256]={0};
//  char cus;
//  int precise;
  /*
  cout<<"Use CG method to find the minimum point and minimum value of the following function:\n"
      <<"f(x)=1+sum[256*(x(i)-x(i-1))^2+(1-x(i-1))^2](i=[2,n]).\n";
  cout<<endl<<"Please input the n noticed above, if input 0, n=10.(0 or 3<n<256):";
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
  */
  for(int i=0;i<nmax;i++)
		  *(xi+i)=*(x+i);

  makeA(FA,m,n);
 
  for(int j=1;j<=nmax;j++)
  {
    if(j==1)
    {
      gx(xi,gii,nmax,b,FA);
      xnext(xi,lamda(gii,gii,nmax,FA),nmax,gii,xii);
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
      gx(xi,gii,nmax,b,FA);
      hii(hi,gii,gi,nmax);
      xnext(xi,lamda(hi,gii,nmax,FA),nmax,hi,xii);
    }
  }
  
  for(int i=0;i<nmax;i++)
		  *(xn+i)=*(xii+i);

  delete []xi;
  delete []xii;
  delete []gi;
  delete []gii;
  delete []hi;
}

int main()
{
	int m=15;
	int n=15;
	double *x=new double[m*n];
	double *b=new double[m*n];
	double *xn=new double[m*n];
	double *y=new double[m*n];
	double FB[256][256];
    
	for(int i=0;i<m*n;i++)
			*(x+i)=1/(i+0.1);
	for(int i=0;i<m*n;i++)
		*(b+i)=0;
	makeA(FB,m,n);
	initiala(b,y,FB,m,n);

	trans(x,y,xn,m,n);

	ofstream outfile("x.txt");

  cout<<endl;
  for (int i=0;i<m;i++)
  {
	  for(int j=0;j<n;j++)
		  outfile<<setw(14)<<*(b+i*n+j);
	  outfile<<endl;
  }	
  
  outfile<<endl;
  for (int i=0;i<m;i++)
  {
	  for(int j=0;j<n;j++)
		  outfile<<setw(14)<<*(y+i*n+j);
	  outfile<<endl;
  }

	outfile<<endl;

  for (int i=0;i<m*n;i++)
  {
	  for(int j=0;j<m*n;j++)
		  outfile<<setw(14)<<FB[i][j];
	  outfile<<endl;
  }


	outfile<<endl;
  for (int i=0;i<m;i++)
  {
	  for(int j=0;j<n;j++)
		  outfile<<setw(14)<<*(xn+i*n+j);
	  outfile<<endl;
  }


  delete []x;
  delete []b;
  delete []xn;
  system("pause");
  return 0;
}
