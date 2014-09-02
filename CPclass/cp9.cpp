#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

void point(bool table[64][64],int x,int y,/*int *l,int *r,int *t,int *b,int *m,int *lt,int *lb,int *rt,int *rb*/int *lab)
{
  /*
  *m=table[x][y]?1:-1;
  if(x==0) *l=table[63][y]?1:-1;
  else *l=table[x-1][y]?1:-1;
  if(x==63) *r=table[0][y]?1:-1;
  else *r=table[x+1][y]?1:-1;
  if(y==0) *t=table[x][63]?1:-1;
  else *t=table[x][y-1]?1:-1;
  if(y==63) *b=table[x][0]?1:-1;
  else *b=table[x][y+1]?1:-1;
  if(x==0&&y==0) *lt=table[63][63]?1:-1;
  else if(x==0&&y!=0) *lt=table[63][y-1]?1:-1;
  else if(x!=0&&y==0) *lt=table[x-1][63]?1:-1;
  if(x==0&&y==63) *lb=table[63][0]?1:-1;
  else if(x==0&&y!=63) *lt=table[63][y+1]?1:-1;
  else if(x!=0&&y==63) *lt=table[x-1][0]?1:-1;
  if(x==63&&y==0) *rt=table[0][63]?1:-1;
  else if(x==63&&y!=0) *lt=table[0][y-1]?1:-1;
  else if(x!=63&&y==0) *lt=table[x+1][63]?1:-1;
  if(x==63&&y==63) *lt=table[0][0]?1:-1;
  else if(x==63&&y!=63) *lt=table[0][y+1]?1:-1;
  else if(x!=63&&y==63) *lt=table[x+1][0]?1:-1;
  */

  int pa[2];
  int pb[2];
  
  for(int i=0;i<9;i++)
  {
    
    pb[0]=-1+i%3;
    pb[1]=-1+i/3;
    
    
    switch(i%3)
    {
    case 0:
      pa[0]=0;
      break;
    case 1:
      pa[0]=63-x-pb[0];
      break;
    case 2:
      pa[0]=63;
      break;
    }
    switch(i/3)
    {
    case 0:
      pa[1]=0;
      break;
    case 1:
      pa[1]=63-y-pb[1];
      break;
    case 2:
      pa[1]=63;
      break;
    }
    
    if(x==pa[0]&&y==pa[1]) *(lab+i)=table[63-pa[0]][63-pa[1]]?1:-1;
    else if(x!=pa[0]&&y==pa[1]) *(lab+i)=table[x+pb[0]][63-pa[1]]?1:-1;
    else if(x==pa[0]&&y!=pa[1]) *(lab+i)=table[63-pa[0]][y+pb[1]]?1:-1;
    else *(lab+i)=table[x+pb[0]][y+pb[1]]?1:-1;
  }
  
}

double Ek(bool table[64][64],int x,int y,double J)
{
  int lab[9];
  int sum=0;
  
  point(table,x,y,&lab[0]);
  for(int i=0;i<9;i++) sum +=lab[i];
  
  return J*lab[4]*(sum-lab[4]);
  
}

double E(bool table[64][64],double J)
{
  double e=0;
  for(int x=0;x<64;x++)
    for(int y=0;y<64;y++)
    {
      e +=-Ek(table,x,y,J)/2;
    }
  return e;
}

double M(bool table[64][64])
{
  int lab[9];
  double M=0;
  for(int x=0;x<64;x++)
    for(int y=0;y<64;y++)
    {
      point(table,x,y,&lab[0]);
      M +=lab[4];
      
    }
  return M;
}

void random(int *x,int *y)
{
  int i=(rand()/static_cast<double>(RAND_MAX)*64*64);
  *y=i/64;
  *x=i%64;
}

double Zk(double Ek,double T,double kb)
{
  return exp(-Ek/kb/T);
}

int main()
{
  int x,y;
  double J=0;
  double E_k=0;
  double Msum=0;
  double M2sum=0;
  double mk=0;
  double Cv=0;
  double X=0;
  double Esum=0;
  double E2sum=0;
  double Et=0;
  double t0=1;
  double tn=6;
  double tp=0.02;
  
  char diy;
  char out;
  
  const int n=3000000;
  const double kb=1;
  const int stat=2500000;
  const int k=16;
  
  bool table[64][64];
  
  srand((unsigned)time(0)*1000);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      if(rand()>RAND_MAX/2.0)
        table[i][j]=1;
      else table[i][j]=0;
    }
  }
  
  cout<<"input J:";
  cin>>J;
  cout<<"Would you want to input the temperature range,and step size?(y or n)";
  cin>>diy;
  if(diy=='y'||diy=='Y')
    
  {
    cout<<"Begin temperature:";
    cin>>t0;
    cout<<"End temperature:";
    cin>>tn;
    cout<<"Temperature step size:";
    cin>>tp;
  }

  cout<<"Would you want to see the final table of data in the txt file?(y or n)";
  cin>>out;
  
  ofstream outfile("results_cp9.txt");
  
  cout<<setprecision(k-6);
  outfile<<setprecision(k-6);
  
  for(double t=t0;t<tn;t +=tp){
    for(int i=0;i<=n;i++)
    {
      random(&x,&y);
      E_k=Ek(table,x,y,J);
      if(i==stat)
      {
        Et =E(table,J);
        mk =M(table);
      }
      if(E_k<0||(E_k>0&&Zk(E_k,t,kb)>(rand()/static_cast<double>(RAND_MAX))))
      {
		table[x][y]=table[x][y]?0:1;
        if(i>stat)
        {
		  Et +=E_k;
		  mk +=table[x][y]?2:-2;
        }
      }
      if(i>stat)
      {
		Esum +=Et;
		E2sum +=pow(Et,2);
		Msum +=mk;
		M2sum +=pow(mk,2);
        //		Esum +=E(table,J);
        //		Msum +=M(table);
		
      }
    }
    if(t==t0)
    {
	  cout<<setw(k)<<"T"<<setw(k)<<"E"<<setw(k)<<"M"<<setw(k)<<"Cv"<<setw(k)<<"X"<<endl;
	  cout<<setw(k)<<"K"<<setw(k)<<" "<<setw(k)<<" "<<endl;
	  outfile<<setw(k)<<"T"<<setw(k)<<"E"<<setw(k)<<"M"<<setw(k)<<"Cv"<<setw(k)<<"X"<<endl;
	  outfile<<setw(k)<<"K"<<setw(k)<<" "<<setw(k)<<" "<<endl;
    }
    
    Cv=1.0/(n-(stat-1))*pow((J/kb/t),2)*(E2sum/(n-(stat-1))-pow(Esum/(n-(stat-1)),2));
    X=1.0/(n-(stat-1))*J/kb/t*(M2sum/(n-(stat-1))-pow(Msum/(n-(stat-1)),2));
    
    cout<<setw(k)<<t<<setw(k)<<Esum/(n-(stat-1))<<setw(k)<<Msum/(n-(stat-1))<<setw(k)<<Cv<<setw(k)<<X<<endl;
    outfile<<setw(k)<<t<<setw(k)<<Esum/(n-(stat-1.0))<<setw(k)<<Msum/(n-(stat-1.0))<<setw(k)<<Cv<<setw(k)<<X<<endl;
    
    Esum=0;
    E2sum=0;
    Msum=0;
    M2sum=0;

    if(out=='y'||out=='Y')
      for(int i=0;i<64;i++)
      {
        for(int j=0;j<64;j++)
        {
          outfile<<(table[i][j]?"*":" ");
        }
        outfile<<endl;
      }
  }
  system("pause");
  return 0;
  
}
