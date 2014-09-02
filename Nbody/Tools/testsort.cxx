#include <bodysort.h>
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
  bodysort qs(43, 21, 2, 4, 33.4, 1);
  std::cout<<qs[0]<<" "<<qs[1]<<" "<<qs[2]<<" "<<qs[3]<<" "<<qs[4]<<" "<<qs.peri<<std::endl;
  std::vector<bodysort> tv;
  tv.push_back(qs);
  std::vector<int> tmp;
  tmp.push_back(33);
  tmp.push_back(23);
  tmp.push_back(341);
  tmp.push_back(3);
  qs.reset(tmp,33.3,2);
  tv.push_back(qs);
  tmp[2]=23;
  qs.reset(tmp,32.3,5);
  tv.push_back(qs);
  tmp[1]=2;
  qs.reset(tmp,54.3,5);
  tv.push_back(qs);
  tmp[4]=4;
  qs.reset(tmp,32.3,5);
  tv.push_back(qs);
  tmp[3]=1;
  qs.reset(tmp,32.3,5);
  tv.push_back(qs);
  for (size_t i=0;i<tv.size();i++)
    tv[i].print();
  std::sort(tv.begin(),tv.end(),bodyshort);
  std::cout<<"sort\n";
  for (size_t i=0;i<tv.size();i++)
    tv[i].print();
  std::cout<<"unique\n";
  std::vector<bodysort>::iterator u=std::unique(tv.begin(),tv.end(),bodyequal);
  tv.erase(u,tv.end());
  for (size_t i=0;i<tv.size();i++)
    tv[i].print();
  return 0;
}
