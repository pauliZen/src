#include <iostream>
#include <iomanip>
#include <cmath>
#include <ofstream>
#include <sstring>

using namespace std;

int main (int argc, char* argv[])
{
  stringstream sstr;
  string filename;
  string outname="fort.10";

  //input=============================================//
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
  
  //operator==========================================//
  ifstream out3(c_str(filename));
  for 
}
