#include <iostream>
#include <string.h>
#include <cassert>

template <typename Data>
struct ListMember{
  Data info;
  ListMember *next;

  //constructor=======================================//
  ListMember(const Data i): info(i), next(0) {}
  
  //destructor========================================//
  ~ListMember() {
    if (next) delete next;
    next=0;
    info=0;
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
  }

  void reset() {
    if (p) delete p;
    p=0;
    last=0;
    n=0;
  }
  
  void push_back(const Data i){
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

  ListMember<Data>* search(const Data i){
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

// void sort_insert(ListHeader<char*>* h, char* i, const int index){
//   if (!h->n) {
//     h->p=new ListMember<char*>(i);
//     h->last=h->p;
//     h->n++;
//   }
//   else {
//     ListMember<char*> *inew=new ListMember<char*>(i);
//     ListMember<char*> *inow=h->p;
//     if (!inow->next) {
//       if (inow->info[index]>inew->info[index]) {
//         inew->next=inow;
//         h->p=inew;
//         h->n++;
//         return;
//       }
//     }
//     else {
//       while (inow->next&&inow->next->info[index]<inew->info[index]) {
//         inow=inow->next;
//       }
//     }
//     inew->next=inow->next;
//     inow->next=inew;
//     h->n++;
//   }
// }

void word_sort(int n, const int d, char * list[]){
  ListHeader<char*> dlist[27];
  //Store the length of word in the last element of array===//
  for (int j=0;j<n;j++) list[j][d]=strlen(list[j]);
  for (int i=0;i<d;i++) {
    for (int j=0;j<n;j++){
      if (list[j][d]<d-i)
        dlist[0].push_back(list[j]);
      else{
        //Assume (int)A-Z is continual======================//
        int index=list[j][d-i-1]-'A'+1;
        assert(index<27);
        assert(index>0);
        dlist[index].push_back(list[j]);
      }
    }
    int counts=0;
    for (int j=0;j<27;j++) {
      ListMember<char*> *di=dlist[j].p;
      while (di) {
        list[counts++]=di->info;
        di=di->next;
      }
      dlist[j].reset();
    }
  }
}

int main(int argc, char *argv[]){

  const int N_T=100;
  const int LENGTH=10;

  FILE *pFile;
  pFile = fopen ("word.txt","r");

  if (!pFile) return 0;

  char **n=new char*[N_T];
  for (int i=0;i<N_T;i++) {
    n[i]=new char[LENGTH];
    fscanf(pFile,"%s",n[i]);
  }

  for (int i=0;i<N_T;i++) {
    fprintf(stdout,"orignal %s\n",n[i]);
  }
    
  word_sort(N_T,LENGTH-1,n);

  for (int i=0;i<N_T;i++) {
    fprintf(stdout,"sort %s\n",n[i]);
  }
  
  return 0;
}
