#ifndef block_h
#define block_h

// Provide block defination to store particle links table in blocks

#include "particle.h"
#include <cassert>
#include <iostream>
#include <cstdlib>

struct block{
  unsigned int depth;
  particle_header *blocks;
  double *dtlist;
  bool **flags;

  block(const unsigned int dep): depth(dep) {
    blocks=new particle_header[dep];
    flags=new *bool[dep];
    for (int i=0;i<dep;i++) {
      flags[i]=new bool[2];
      flags[i][0]=0;               //step flag
      flags[i][1]=1;               //down flag
    }
    dtlist-new double[dep];
    assert(blocks);
  }

  block(const unsigned int dep, const double tm): depth(dep), tmax(tm) {
    blocks=new particle_header[dep];
    flags=new *bool[dep];
    for (int i=0;i<dep;i++) {
      flags[i]=new bool[2];
      flags[i][0]=0;
      flags[i][1]=1;
    }
    dtlist=new double[dep];
    assert(blocks);
  }

  ~block() {
    delete blocks;
    depth=0;
  }

  //calculate time steps==============================//
  void tstep_calc(const double &tmax) {
    long long ti=(long long)1;
    for (int i=0;i<depth;i++) {
      dtlist[i]=tmax/ti;
      ti = (ti << 1) ;
    }
  }
  
  //Fill one particle with pindex in bindex block=====//
  void fill(const unsigned int bindex, const int pindex) {
    assert(bindex<depth);
    blocks[bindex].push_back(pindex);
  }

  //loop function for block===========================//
  // idep: begin index of blocks, idepmax: end index  //
  // eta: time step coefficient                       //
  void block::reloop(int &idep, int &idepmax, particle *list, neighbor *nblist, force *firr, force *freg, const double &eta);
  
  //intgrt one block step=============================//
  void intgrt(particle *list, neighbor *nblist, force *firr, force *freg, const double &eta);

  //move particle now in binow to binew===============//
  void move(const unsigned int binow, const unsigned int binew) {
    assert(binow<depth);
    assert(binew<depth);
    blocks[binew].push_back(blocks[binow].drop_now());
  }

  //clear each block to zero particle=================//
  void clear() {
    for (int i=0; i<depth;i++) blocks[i].clear();
  }

  particle_header &operator[] (const unsigned int index) {
    assert(index<depth);
    return blocks[index];
  }

private:
  unsigned int depth;
  particle_header *blocks;
};

//Fill particle based on time step==================//
int locate(double dt);, const int pindex);

#endif
