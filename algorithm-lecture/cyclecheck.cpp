#include <initial.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <cassert>

bool cyclecheck(const int n, int **AdjacencyMatrix) {
  int INTMAX=std::numeric_limits<int>::max();
  int deletecount=0;
  //  int totcount=0;
  for (int i=0;i<n;i++) {
    //A.M[i][i] is -1 means this vertex is deleted, >1 means this vertex has degree > 1, thus ignore.
    if (AdjacencyMatrix[i][i]==-1||AdjacencyMatrix[i][i]>1) continue; 
    int edgeindex=i;                        //For save the last next vertex, only useful for 1 degree vertex
    while (true){
      int inow=edgeindex;
      //      assert(AdjacencyMatrix[inow][inow]!=-1);
      if (inow>=i&&!AdjacencyMatrix[inow][inow]) {
        for (int j=0;j<n;j++)
          if (AdjacencyMatrix[inow][j]!=INTMAX&&AdjacencyMatrix[inow][j]>0&&inow!=j) {
            AdjacencyMatrix[inow][inow]++;
            edgeindex=j;
          }
        //        totcount++;
      }
      if (AdjacencyMatrix[inow][inow]==0) {
        AdjacencyMatrix[inow][inow]=-1;
        deletecount++;
        break;
      }
      else if (AdjacencyMatrix[inow][inow]==1) {
        AdjacencyMatrix[inow][inow]=-1;
        if (AdjacencyMatrix[edgeindex][edgeindex]) AdjacencyMatrix[edgeindex][edgeindex]--;
        //        assert(AdjacencyMatrix[edgeindex][edgeindex]>=-1);
        AdjacencyMatrix[inow][edgeindex]=-AdjacencyMatrix[inow][edgeindex];
        AdjacencyMatrix[edgeindex][inow]=-AdjacencyMatrix[edgeindex][inow];
        deletecount++;
      }
      else break;
    }
    std::cout<<"Now I = "<<i<<std::endl;
    for (int ii=0;ii<n;ii++) {
      for (int j=0;j<n;j++) {
        if (AdjacencyMatrix[ii][j]==INTMAX) std::cout<<"F"<<" ";
        else std::cout<<AdjacencyMatrix[ii][j]<<" ";
      }
      std::cout<<std::endl;
    }
  }
  //  assert(totcount==n);
  if (deletecount<n) return true;
  else return false;
}

int main (int argc, char *argv[])
{
  const int INTMAX=std::numeric_limits<int>::max();
  
  pars_initial init(".cyclecheck_config");
  init.add("N","Number of vertex",(int)5);
  init.add("M","AdjacencyMatrix file name, -10 for INF","AM.dat");
  init.initial(argc,argv);

  int n=init.geti("N");
  int **am=new int*[n];
  for (int i=0;i<n;i++) am[i]=new int[n];
  std::ifstream f(init.gets("M").c_str());
  if (!f.is_open()) return 0;

  std::cout<<"A.M. Matrix:\n";
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      f>>am[i][j];
      if (i==j) am[i][j]=0;
      if (am[i][j]==-10) am[i][j]=INTMAX;
      std::cout<<am[i][j]<<" ";
      if (f.eof()) std::cerr<<"Warning: file reach end when reading "<<i<<" "<<j<<"!\n";
    }
    std::cout<<std::endl;
  }
  if (cyclecheck(n,am)) std::cout<<"Have cycle\n";
  else std::cout<<"No cycle\n";

  return 0;
}
