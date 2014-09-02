#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
using namespace std;

void line(long double *Tnow, long double *Tnext, int n, long double a)
{
  long double g[100]={0};
  long double h[100]={0};
  g[n-1]=0;
  h[n-1]=*(Tnow+n);
  for(int i=n-2;i>=0;i--)
    {
      g[i]=a/(1+2*a-a*g[i+1]);
      h[i]=(*(Tnow+i+1)+a*h[i+1])/(1+2*a-a*g[i+1]);
    }
  *Tnext=*Tnow;
  for(int i=0;i<=n-1;i++)
    {
      *(Tnext+i+1)=*(Tnow+i)*g[i]+h[i];
    }
}


int main()
{
  //declaration of values
  long double b=0;
  long double a=0;
  long double T0=1.0,Tn=0.5;
  char cha=0,cht=0;
  int n_max=10;
  int n_tmax=40;
  int nt=0;
  double dt=0.1;
  long double T[100],Temp[100];
  long double *Tnow=&T[0];
  long double *Tnext=&Temp[0];
  int outstyle=0;
  int precise=8;
  //

  //A description for the function
  cout<<"The program for calculation of T'|t=¦Ë*T''|x^2:\n";

  //Input parameter ¦Ë
  cout<<"Please input parameter a:(it's better to choose the value from 0.1->0.6)If input 0, you will get defaulted a=0.3:(0 or >0)";
  cin>>a;
  if(a<=0)
    a=0.3;

  //Input division of L
  cout<<"\nPlease input the division number of L (from 2 to 100). if enter 0, defaulted number is 10,while ¦¤x=0.1 :(0 or2->100)";
  cin>>n_max;
  if (n_max<=0)
    n_max=10;

  //Input step size of time
  cout<<"\nPlease Enter the step size of the time (¦¤t), if enter 0, defaulted size is 0.1:(0 or >0)";
  cin>>dt;
  if(dt<=0)
    dt=0.1;

  //length of steps
  cout<<"\nPlease enter the number \"n\" of the steps of the time;(n*¦¤t is the total time),if enter 0; n=40:(0 or >0)";
  cin>>n_tmax;
  if (n_tmax<=0)
    n_tmax=40;

  //calculate and display a
  b=a/(dt*n_max*n_max);
  cout<<"\nThe parameter a="<<a<<", ¦Ë*¦="<<b;
  cout<<"\nThe total length of x=1(L=1),and ¦¤x="<<(1/static_cast<double>(n_max));
  cout<<"\nThe step of time is "<<dt;
  cout<<"\nTotal calculation time is "<<n_tmax*dt<<endl;

  //Input boundary condition
  cout<<"\nEnter \"y\" you can enter the boundary conditions, or the defaulted condition is T(0,0)=1.0;T(1,0)=0.5:";
  cin>>cht;
  if (cht=='y'||cht=='Y')
    {
      cout<<"\nPlease enter the boundary conditions:\n";
      cout<<"T(0,0)=";
      cin>>T0;
      cout<<"T(1,0)=";
      cin>>Tn;
    }
  else {T0=1.0;Tn=0.5;}

  //The initial for T(t=0)
  T[0]=T0;
  T[n_max]=Tn;
  for(int i=1;i<n_max;i++)
    T[i]=T[n_max];

  //The displayed style
  cout<<"\nEnter the out style of the data:\n1:display in cmd;\n2:save into the txt file;\n3:both of above;\n";
  cin>>outstyle;
  while(!(outstyle==3||outstyle==2||outstyle==1))
    {
      cout<<"Error style, please input again:";
      cin>>outstyle;
    }

  //The precision
  cout<<"\nChoose the precision of the displayed datas:(If enter 0,defaulted precision is 8)";
  cin>>precise;
  if (precise<=0)
    precise=8;
  int st=precise+3;
  cout<<setprecision(precise)<<showpoint;

  //Main calculation process.

  if(outstyle==1||outstyle==3)							//display in cmd screen
    {
      for(nt=0;nt<n_tmax;nt++)
	{
	  line(Tnow,Tnext,n_max,a);

	  if(nt==0)
	    {
	      cout<<"a="<<noshowpoint<<a<<";"<<" ¦¤t="<<dt<<";"<<" ¦¤x="<<(1/static_cast<double>(n_max))<<showpoint<<";\n";
	      for(int i=0;i<5*st;i++)
		cout<<"-";
	      cout<<endl;
	      cout<<"        |";
	      for(int i=0;i<=n_max;i++)
		{
		  if(i%4==0&&i!=0)
		    cout<<endl<<"        |";
		  cout<<"x="<<setw(st-3)<<i<<"|";
		}
	      cout<<endl;
	      for(int i=0;i<5*st;i++)
		cout<<"-";
	      cout<<endl;
	    }
	  cout<<"t="<<setw(6)<<noshowpoint<<dt*nt<<showpoint<<"|";
	  for(int i=0;i<=n_max;i++)
	    {
	      if(i%4==0&&i!=0)
		cout<<endl<<"        |";
	      cout<<setw(st-1)<<T[i]<<"|";
	    }
	  cout<<endl;
	  for(int i=0;i<5*st;i++)
	    cout<<"-";
	  cout<<endl;

	  for(int i=0;i<=n_max;i++)
	    T[i]=Temp[i];
	}
    }

  if(outstyle==2||outstyle==3)							//output into a txt file.
    {
      if(outstyle==4)
	{
	  T[0]=T0;
	  T[n_max]=Tn;
	  for(int i=1;i<n_max;i++)
	    T[i]=T[n_max];
	}
      ofstream outfile("results_cp4.txt");
      outfile<<setprecision(precise)<<showpoint;
      for(nt=0;nt<n_tmax;nt++)
	{
	  line(Tnow,Tnext,n_max,a);

	  if (nt==0)
	    {
	      cout<<"The txt file \"results_cp4\" is created in the directory of this program.\n";
	      outfile<<"a="<<noshowpoint<<a<<"; dt="<<dt<<"; dx="<<(1.0/static_cast<double>(n_max))<<showpoint<<endl;
	      outfile<<setw(9)<<"time x=";
	      for(int i=0;i<=n_max;i++)
		outfile<<setw(st+3)<<i;
	      outfile<<endl;
	    }
	  outfile<<setw(9)<<noshowpoint<<nt*dt<<"   "<<showpoint;
	  for (int i=0;i<=n_max;i++)
	    outfile<<setw(st+3)<<T[i];
	  outfile<<endl;
	  for(int i=0;i<=n_max;i++)
	    T[i]=Temp[i];
	}

    }

  system("pause");
  return 0;

}
