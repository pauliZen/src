#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>

using namespace std;

void Abx(double u[5][5],double bp[3][3], char chs)
{
	if(chs=='w')
		for(int j=0;j<=2;j++)
		{
			bp[0][j]=-2*u[1][j+1]+u[2][j+1];
			bp[1][j]=u[1][j+1]-2*u[2][j+1]+u[3][j+1];
			bp[2][j]=u[2][j+1]-2*u[3][j+1];
		}
	else if(chs=='v')
		for(int i=0;i<=2;i++)
		{
			bp[i][0]=-2*u[i+1][1]+u[i+1][2];
			bp[i][1]=u[i+1][1]-2*u[i+1][2]+u[i+1][3];
			bp[i][2]=u[i+1][2]-2*u[i+1][3];
		}
}

void Axb(double w,double b[3][3],double x[5][5],char chs)
{
	double g2=1.0/(2-w);
	double g1=1.0/(2-w-g2);
	if(chs=='w')
		for(int i=0;i<3;i++)
		{
			double h2=b[i][2]/(-2+w);
			double h1=(b[i][1]-h2)/(-2+w+g2);
			x[i+1][1]=(b[i][0]-h1)/(-2+w+g1);
			x[i+1][2]=g1*x[i+1][1]+h1;
			x[i+1][3]=g2*x[i+1][2]+h2;
		}
	else if(chs=='v')
		for(int j=0;j<3;j++)
		{
			double h2=b[2][j]/(-2+w);
			double h1=(b[1][j]-h2)/(-2+w+g2);
			x[1][j+1]=(b[0][j]-h1)/(-2+w+g1);
			x[2][j+1]=g1*x[1][j+1]+h1;
			x[3][j+1]=g2*x[2][j+1]+h2;
		}
}

int main()
{
	const double w0=-1.4142;
	double u[5][5]={0};
	char initial;
	char wch;
	double w=0;
	double b[3][3]={0};
	double bp[3][3]={0};
	double bn[3][3]={0};
	char chs;
	
	cout<<"Custom boundary conditions? (y or n)";
	cin>>initial;
	if(initial=='y'||initial=='Y')
	{
		for(int i=0;i<5;i +=4)
		{	for(int j=0;j<5;j++)
			{
				cout<<"u("<<i+1<<","<<j+1<<")=";
				cin>>u[i][j];
			}
		}
		for(int i=1;i<4;i++)
		{
			cout<<"u("<<i+1<<","<<1<<")=";
			cin>>u[i][0];
			cout<<"u("<<i+1<<","<<5<<")=";
			cin>>u[i][4];
		}
	}
	else 
	{
		for(int i=0;i<5;i++)
		{
			u[i][0]=0;
			u[i][4]=1;
		}
		for(int j=0;j<5;j++)
		{
			u[0][j]=u[4][j]=j*0.25;
		}
	}
	cout<<endl;

	cout<<"change parameter w? the defaulted is "<<w0<<". (y or n)";
	cin>>wch;
	if(wch!='y'&& wch!='Y')
		w=w0;
	else {
		cout<<"Input w:";
		cin>>w;
	}
	cout<<endl;

	b[0][0]=-u[1][0]-u[0][1];
	b[0][1]=-u[0][2];
	b[0][2]=-u[0][3]-u[1][4];
	b[1][0]=-u[2][0];
	b[1][1]=0;
	b[1][2]=-u[2][4];
	b[2][0]=-u[3][0]-u[4][1];
	b[2][1]=-u[4][2];
	b[2][2]=-u[3][4]-u[4][3];

	for(int n=0;n<=50; n++)
	{
		if(n%2==0) chs='w';
		else if(n%2!=0) chs='v';
		Abx(u,bp,chs);

		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				bn[i][j]=b[i][j]-bp[i][j]+w*u[i+1][j+1];

		Axb(w,bn,u,chs);
	}

	cout<<setprecision(8)<<showpoint<<"Result u(x,y):"<<endl;

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
			cout<<setw(16)<<u[i][j];
		cout<<endl;
	}
	system("pause");
	return 0;

}