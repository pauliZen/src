#include <iostream>
#include <string>
#include <fstream>

#ifdef LINK
template <typename Data>
struct ListMember{
  Data info;
  ListMember *next;

  //constructor=======================================//
  ListMember(Data i): info(i) {}
  
  //destructor========================================//
  ~ListMember() {
    if (next) delete next;
  }
};

template <typename Data> struct ListHeader{
  ListMember<Data> *p;
  ListMember<Data> *last;
  int n;

  //constructor=======================================//  
  ListHeader(): p(0), last(0), n(0) {}

  //destructor========================================//
  ~ListHeader() {
    if (p) delete p;
    last=0;
    n=0;
  }
  
  void push_back(Data i){
    if (!n) {
      p=new ListMember<Data>(i);
      last=p;
      n++;
    }
    else{
      ListMember<Data> *inew=new ListMember<Data>(i);
      last->next=inew;
      last=inew;
      n++;
    }
  }

  ListMember<Data>* search(Data i){
    if (!p) return 0; //Empty List;
    if (p->info==i) return p; //First element;
    else if(p->next){
      ListMember<Data> *n1=p;
#ifdef EX_INFO    //Exchange information only
      std::cout<<"EX_INFO"<<std::endl;
      ListMember<Data> *n2=p->next;
      while(n2){
        if (n2->info==i) {
          n2->info=n1->info;
          n1->info=i;
          return n1;
        }
        else {
          n1=n1->next;
          n2=n2->next;
        }
      }
#else             //Rebuild link;
      if (p->next->info==i) {
        p=p->next;
        n1->next=p->next;
        p->next=n1;
        return p;
      }
      else if(p->next->next){
        ListMember<Data> *n2=p->next->next;
        while(n2){
          if(n2->info==i) {
            ListMember<Data> *tmp=n1->next;
            n1->next=n2;
            tmp->next=n2->next;
            n2->next=tmp;
            return n1->next;
          }
          else {
            n1=n1->next;
            n2=n2->next;
          }
        }
      }
#endif        
    }
    return 0; //No match;
  }
  
  void print(){
    std::cout<<"DataList: ";
    ListMember<Data> *inow=p;
    while (inow){
      std::cout<<inow->info<<" ";
      inow=inow->next;
    }
    std::cout<<std::endl;
  }
};

#else
template <typename Data> struct ListHeader{
  Data *list;
  int N_MAX;
  int N_STORE;

  //constructor=======================================//
  ListHeader(int n): N_MAX(n), N_STORE(0) {
    list=new Data[n];
  }

  //destructor========================================//
  ~ListHeader() {
    if (list) delete list;
    N_STORE=0;
    N_MAX=0;
  }

  //add data==========================================//
  void push_back(Data i){
    if (N_STORE<N_MAX) {
      list[N_STORE]=i;
      N_STORE++;
    }
    else {
      fprintf(stderr,"Error: List Overflow!\n");
      exit(0);
    }
  }

  //search============================================//
  int search(Data i) {
    if (!list) return -1; //Empty List;
    if (list[0]==i) return 0; //First element match;
    else for (int j=1;j<N_STORE;j++) {
        if (list[j]==i) {
          list[j]=list[j-1];
          list[j-1]=i;
          return j-1;
        }
      }
    return -3; //No match
  }

  //print=============================================//
  void print(){
    std::cout<<"Datalist: ";
    for (int i=0;i<N_STORE;i++) std::cout<<list[i]<<" ";
    std::cout<<std::endl;
  }
};

#endif

int main(int argc, char *argv[]){
  std::string list;
  if (argc>1)
    list=argv[1];
  else  {
    std::cout<<"Name: ";
    std::cin>>list;
  }
  std::ifstream f(list.c_str());
  if (!f.is_open()) return 0;
  std::cout<<"List name "<<list<<std::endl;

#ifdef LINK
  ListHeader<int> d;
#else
  ListHeader<int> d(1000);
#endif
  
  while (1){
    int tmp;
    f>>tmp;
    if(f.eof()) break;
    d.push_back(tmp);
  }
  d.print();
  
  int forsearch;
  std::cout<<"search data: ";
  std::cin>>forsearch;
#ifdef LINK  
  std::cout<<"Index: "<<d.search(forsearch)->info<<std::endl;
#else
  std::cout<<"Index: "<<d.search(forsearch)<<std::endl;
#endif  
  d.print();
  
  return 0;
}
