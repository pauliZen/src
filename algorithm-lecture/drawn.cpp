#include <iostream>
#include <cmath>

struct node
{
  const char* name;
  int color;

  //initial===========================================//
  node(const char *na,int n): name(na), linknum(n), next(0), color(0) { if (n>0) connect=new node*[linknum]; }

  void link(node* target)
  {
    if (next>=linknum) std::cerr<<"Error: "<<name<<" Link maximum reach!\n";
    else
    {
      connect[next]=target;
      next++;
    }
  }
  
  bool search(node* target)
  {
    for (int i=0;i<next;i++)
      if (target==connect[i]) return 1;
    return 0;
  }

private:
  int linknum,next;
  node **connect;
};

void connect(node *a, node *b)
{
  if (a->search(b)) return;
  a->link(b);
  b->link(a);
}

int main(int argc, char *argv[])
{
  //initial road======================================//
  node **road=new node*[13];
  road[0]=new node("ab",4);
  road[1]=new node("ba",0);
  road[2]=new node("da",5);
  road[3]=new node("ea",3);
  road[4]=new node("ac",5);
  road[5]=new node("bc",3);
  road[6]=new node("db",3);
  road[7]=new node("eb",5);
  road[8]=new node("ad",3);
  road[9]=new node("bd",5);
  road[10]=new node("dc",0);
  road[11]=new node("ec",4);
  road[12]=new node("ed",0);

  //connect===========================================//
  connect(road[0],road[2]);
  connect(road[0],road[3]);
  connect(road[0],road[5]);
  connect(road[0],road[9]);

  connect(road[2],road[9]);
  connect(road[2],road[7]);
  connect(road[2],road[11]);

  connect(road[3],road[4]);
  connect(road[3],road[8]);

  connect(road[4],road[6]);
  connect(road[4],road[7]);
  connect(road[4],road[9]);

  connect(road[5],road[6]);
  connect(road[5],road[7]);

  connect(road[6],road[11]);

  connect(road[7],road[8]);
  connect(road[7],road[9]);

  connect(road[8],road[11]);

  connect(road[9],road[11]);

  //draw==============================================//
  int map[13],map1[13],map2[13];
  int count1=0,count2=0;
  int max1=13;
  int colorgroup=0;
  for (int i=0;i<13;i++) map[i]=i;
  while(max1>1)
  {
    colorgroup++;
    while(max1>1)
    {
      for (int j=1;j<max1;j++)
      {
        if (road[map[0]]->search(road[map[j]]))
        {
          road[map[j]]->color++;
          map2[count2]=map[j];
          count2++;
        }
        else
        {
          map1[count1]=map[j];
          count1++;
        }
      }
      for (int j=0;j<count1;j++) map[j]=map1[j];
      max1=count1;
      count1=0;
    }
    for (int i=0;i<count2;i++) map[i]=map2[i];
    max1=count2;
    count2=0;
  }

  //output============================================//
  for (int i=0;i<colorgroup;i++)
  {
    std::cout<<"Group "<<i<<":\t";
    for (int j=0;j<13;j++)
      if (road[j]->color==i) std::cout<<road[j]->name<<" ";
    std::cout<<std::endl;
  }
  
  return 0;
}
