#include<iostream>
#include<cmath>
#include<cstdlib>
#include<time.h>
#include<iomanip>

using namespace std;

double p(double x)									//probability distribution function p(x)
{
	return (exp(1.0)/(exp(1.0)-1))*exp(-x);
}

double f(double x)									//f(x)=Exp(-x^2)
{
	return exp(-pow(x,2));
}

void main()
{
	int n=0;
	double x=0;
	double Isum=0;
	double Fsum=0;
	double F2sum=0;
	int decimal=0;
	double errorsquare=0;
	const double A=exp(1.0)/(exp(1.0)-1);
	bool flag=1;
	char change;
    srand( (unsigned)time( NULL )*1000 );
	cout<<"This program is designed to estimate the integral \"Intergrate (from 0 to 1) [Exp(-x^2)dx]\" to n decimal places.\n";
	cout<<"Do you wish to input the number of decimal places?(y or n)";
	cin>>change;
	if (change=='y'||change=='Y')
	{
		cout<<"Input the number of decimal places:";
		cin>>decimal;
	}
	else decimal=2;
    cout<<setprecision(decimal);
    while(flag)
	{
		x=log(A/(A-rand()/static_cast<double>(RAND_MAX)));
		Isum +=f(x)/p(x);
		Fsum +=f(x);
		F2sum +=pow(f(x),2);
		n++;
		errorsquare=(F2sum/static_cast<double>(n)-pow(Fsum/static_cast<double>(n),2))/static_cast<double>(n);
		if(errorsquare<pow(0.1,decimal*2+1)&&n>=100)
		{
			flag=0;
			cout<<"n(number of trial)="<<n<<endl;
			cout<<"The result I="<<Isum/static_cast<double>(n)<<endl;
			cout<<"The error estimation is "<<sqrt(errorsquare)<<endl;
		}
	}
	system("pause");
}