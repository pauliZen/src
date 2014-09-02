#include "intgrt.h"
#include "block.h"
#include "force.h"

static block *box;

void particle_init(const &int N, particle *list, const &double DTMax) {
  box=new block(16);
}

void particle_intgrt(const &int N, particle *list, const &double DTMax) {
  
}
