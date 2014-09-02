#include <iostream>
#include <vector>

struct par{
  double m[2],x[2][3],v[2][3];
  int name[4];
};

static int count=0;
static std::vector<par> list;

extern "C"
{
  int add_(int *,int *);
  int mix_(int *i, int *n);
}

int add_(int *i, int *d)
{
  count++;
  par tmp;
  tmp.m[0]=tmp.m[1]=count;
  for (int ii=0;ii<4;ii++)
  {
    tmp.name[ii]=ii+4*count;
  }
  for (int ii=0;ii<3;ii++)
    for (int j=2;j<2;j++)
    {
      tmp.x[j][ii]=0.1;
      tmp.v[j][ii]=0.002;
    }
  list.push_back(tmp);
  //  std::cout<<count<<std::endl;
  std::cout<<count<<"\tm1:"<<list[count-1].m[0]<<"\tm2:"<<list[count-1].m[1]<<"\tname[1]:"<<list[count-1].name[0]<<std::endl;
  *i=*i+*d;
  return *i;
}

int mix_(int *i, int *n)
{
  int tmp;
  for (int j=0;j<*n;j++)
    tmp +=i[j];
  return tmp;
}
