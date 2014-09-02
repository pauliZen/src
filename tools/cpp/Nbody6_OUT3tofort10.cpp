#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
	string filename="OUT3";
	string outname="fort.10";
	stringstream sstr;
	sstr.str("");
	sstr.clear();
	
	switch (argc)
	{
    case 1:
      cout<<"Input: ";
      cin>>filename;
      break;
      
    case 2:
      sstr.str("");
      sstr.clear();
      sstr<<argv[1];
      sstr>>filename;
      sstr.str("");
      sstr.clear();
      break;
    
    case 3:
      sstr.str("");
      sstr.clear();
      sstr<<argv[1];
      sstr>>filename;
      sstr.str("");
      sstr.clear();
      sstr<<argv[2];
      sstr>>outname;
      sstr.str("");
      sstr.clear();
      break;

    default:
      sstr.str("");
      sstr.clear();
      sstr<<argv[1];
      sstr>>filename;
      sstr.str("");
      sstr.clear();
      sstr<<argv[2];
      sstr>>outname;
      sstr.str("");
      sstr.clear();
      break;
	}

    cout<<filename<<" to "<<outname<<endl;

    ifstream orgdata(filename.c_str());
	ofstream outdata(outname.c_str());
	int count=1;
    string firstindex;
    string time;

    while(!orgdata.is_open())
	{
		cout<<"No such file, input again: "<<endl;
		cin>>filename;
	}
    if(!orgdata.eof())
    {
      orgdata>>firstindex;
      orgdata>>time;
    }
    
    while(!orgdata.eof())
	{
      sstr.str("");
      sstr.clear();
      string tempstr;
      orgdata>>tempstr;
      double temp;
      if (count==1)
      {
        tempstr.replace(0,1," ");
        sstr<<tempstr;
        //cout<<"("<<tempstr<<")";
      }
      else
        sstr<<tempstr;
      sstr>>temp;
      if (abs(temp)<0.1)
      {
        cout<<setprecision(17)<<scientific<<temp<<" ";
        outdata<<setprecision(17)<<scientific<<temp<<" ";
      }
      else
      {
        cout<<setprecision(17)<<fixed<<temp<<" ";
        outdata<<setprecision(17)<<fixed<<temp<<" ";
      }
      
      if (count==7)
      {
        cout<<endl;
        outdata<<endl;
        count=0;
      }
      count++;
    }

	orgdata.close();
	outdata.close();
    cout<<"Total Number "<<firstindex<<endl;
    cout<<"Time "<<time<<endl;
    return 0;
}
