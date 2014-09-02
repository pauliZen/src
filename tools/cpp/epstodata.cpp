#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	string filename="1.txt";
	string outname="out.txt";
	stringstream sstr;
	sstr.str("");
	sstr.clear();
	
	switch (argc)
	{
	case '2':
		sstr<<argv[1];
		sstr>>filename;
		sstr.str("");
		sstr.clear();
		break;
	case '3':
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
		cout<<"Input file name: ";
		cin>>filename;
		cout<<"Output file name: ";
		cin>>outname;
		break;
	}
	
	ifstream orgdata(filename.c_str());
	ofstream outdata(outname.c_str());
	
	while(!orgdata.is_open())
	{
		cout<<"No such file, input again: "<<endl;
		cin>>filename;
	}
	while(!orgdata.eof())
	{
		string temp;
//		sstr.str("");
//		sstr.clear();
		orgdata>>temp;
		outdata<<temp<<endl;
	}

	orgdata.close();
	outdata.close();

	return 0;
}