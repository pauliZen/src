#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>


using namespace std;

int main(int argc, char* argv[])
{
  ifstream fin;
  int data[10][10];
  stringstream sstr;
  for(int k=0;k<3;k++)
  {
    //input file name: Eg.: file name is "filex" where x is 0, 1, 2...
    sstr<<"file";
    sstr<<k;
    int n=0;
    
    fin.open((sstr.str()).c_str());
    cout<<"Filename:"<<sstr.str()<<":";
    sstr.str("");
    sstr.clear();

    //check for the keyword "start"
    bool flag=1;
    bool cans=1;
    
    while(flag)
    {
      string keyword;
      fin>>keyword;
      if(keyword=="start")
        flag=0;
      if(fin.eof())
      {
        cout<<"Error: Not find the keyword";
        flag=0;
        cans=0;
        
      }
      
    }

    if(cans) // If the file has keyword "start", then read its data
      for(int i=0;i<10;i++)
      {
        
        int check=0;
        fin>>check;
        //your condition for data, here the integer is less than 50
        if(check<50)
        {
          data[n][k]=check;
          cout<<data[n][k]<<"  ";
          n++;
        }
      
      }
    cout<<endl;
    fin.close();
    
  }
  
  return 0;
}










