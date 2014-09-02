#ifndef PTIME_H
#define PTIME_H

// Provide time measure

#include <ctime>
#include <cassert>
#include <stdio.h>

struct ptime{
  clock_t start,end;
  const char* name;

  ptime(const char* n): start(0), end(0), name(n) {}

  void set() {
    start=clock();
    end=0;
  }

  void add() {
    end +=clock()-start;
  }
  
  void printall() {
    fprintf(stdout,"time cost %s = %lg s\n", name, (double)end/CLOCKS_PER_SEC);
  }

  void printn() {
    fprintf(stdout,"%10s",name);
  }

  void printc() {
    fprintf(stdout,"%10lg", (double)end/CLOCKS_PER_SEC);
  }
  
};

struct time_link{
  ptime *now;
  time_link *next;

  time_link(ptime *n): now(n),next(0) {}
  ~time_link() {
    if (next) delete next;
    now=0;
  }
};

struct time_list{
  time_link *head;
  time_link *tail;

  time_list():head(0), tail(0) {}

  void add(ptime* n) {
    if (!head) {
      head=new time_link(n);
      assert(head);
      tail=head;
    }
    else {
      tail->next=new time_link(n);
      assert(tail->next);
      tail=tail->next;
    }
  }

  void print() {
    if(!head) return;
    fprintf(stdout,"==================TIME CHECK [SECONDS]================\n");
    time_link *pnow;
    pnow=head;
    while(pnow) {
      pnow->now->printn();
      pnow=pnow->next;
    }
    fprintf(stdout,"\n");
    pnow=head;
    while(pnow) {
      pnow->now->printc();
      pnow=pnow->next;
    }
    fprintf(stdout,"\n");
  }
};
#endif
