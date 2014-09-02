#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
  map<string, pair<string,int> > mapStudent;
  mapStudent["d"].first="student_two";
  mapStudent["d"].second=121221;
  mapStudent["s"].first="student_three";
  mapStudent["s"].second=121221;
  map<string, pair<string,int> >::iterator  iter;
  for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
  {
    cout<<iter->first<<" "<<(iter->second).first<<":"<<(iter->second).second<<endl;
    if (mapStudent.count("d"))
    {
      cin>>(iter->second).second;
      cout<<iter->first<<" "<<(iter->second).first<<":"<<(iter->second).second<<endl;
      exit(1);
    }
  }
  cerr<<"out of range"<<endl;
  cout<<"finish"<<endl;
  return 0;
}

