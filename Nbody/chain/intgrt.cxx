#include <particle.h>
#include <intgrt.h>
#include <map>
#include <cmath>

#include <cassert>

//shift particle ===================================//
void particle_shift(const double3 &x, const double3 &v, const int &num, particle *p) {
  double3 x0,v0;
  memcpy(x0,x,3*sizeof(double));
  memcpy(v0,v,3*sizeof(double));

  for (int i=0;i<num;i++) {
    p[i].x[0] -= x0[0];
    p[i].x[1] -= x0[1];
    p[i].x[2] -= x0[2];
    p[i].v[0] -= v0[0];
    p[i].v[1] -= v0[1];
    p[i].v[2] -= v0[2];
  }
}

//Generate chain link list==========================//
void generate_list(const int &num, const particle *p, int *list) {
  bool *is_checked=new bool[num];
  int inext=0;
  for (int i=0; i<num; i++) {
    //initial rjk=======================================//
    //mark checked particle=============================//
    is_checked[inext] = true;

    //initial chain_mem=================================//
    list[i]=inext;
    
    //make chain========================================//
    double rmin;
    bool first=true;
    for (int j=1; j<num; j++) {
      if(is_checked[j]) continue;
      double dx=p[j].x[0] - p[inext].x[0];
      double dy=p[j].x[1] - p[inext].x[1];
      double dz=p[j].x[2] - p[inext].x[2];
      double dr2=dx*dx + dy*dy + dz*dz;
      if(first) {
        rmin = dr2;
        first=false;
        inext = j;
      }
      else if(dr2<rmin) {
        rmin = dr2;
        inext = j;
      }
    }
  }
}

//Initial chain=====================================//
void chain_init(const double &t, const double3 *force, particle *p, chain *c) {
  int num=c->num;
  bool *is_checked=new bool[num];
  memset(is_checked,0,num*sizeof(bool));
  memset(c->xc,0,3*sizeof(double));
  memset(c->vc,0,3*sizeof(double));

  c->mtot=0.;

  //initial array===================================//
  //  c->m=new chain_mem[num-1];
  chain_mem *m=c->m;
  //  c->num=num;
  //  c->list=new int[num];
  int *list=c->list;
  //  c->rjk=new double4*[num];

  assert(m!=NULL);
  assert(list!=NULL);
  assert(c->rjk!=NULL);

  //Generate chain link list==========================//
  generate_list(num,p,list);

  //center mass=======================================//
  for (int i=0;i<num;i++) {
    c->xc[0] += p[i].x[0] * p[i].mass;
    c->xc[1] += p[i].x[1] * p[i].mass;
    c->xc[2] += p[i].x[2] * p[i].mass;

    c->vc[0] += p[i].v[0] * p[i].mass;
    c->vc[1] += p[i].v[1] * p[i].mass;
    c->vc[2] += p[i].v[2] * p[i].mass;

    c->mtot += p[i].mass;
  }
  c->xc[0] /= c->mtot;
  c->xc[1] /= c->mtot;
  c->xc[2] /= c->mtot;

  c->vc[0] /= c->mtot;
  c->vc[1] /= c->mtot;
  c->vc[2] /= c->mtot;

  //shift particle====================================//
  particle_shift(c->xc,c->vc,num,p);
  
  //Initial chain member==============================//
  for (int i=0;i<num-1;i++) {
    m[i].X[0]=p[list[i+1]].x[0] - p[list[i]].x[0];
    m[i].X[1]=p[list[i+1]].x[1] - p[list[i]].x[1];
    m[i].X[2]=p[list[i+1]].x[2] - p[list[i]].x[2];

    m[i].V[0]=p[list[i+1]].v[0] - p[list[i]].v[0];
    m[i].V[1]=p[list[i+1]].v[1] - p[list[i]].v[1];
    m[i].V[2]=p[list[i+1]].v[2] - p[list[i]].v[2];

  }

  //Get Wij===========================================//
  get_Wij(p,c,1);
  
  //Get initial W, acc and Pot=======================//
  get_chain_pars(p,force,c);

  //Kinetic energy====================================//
  c->Ekin = 0.;
  for (int i=0;i<num;i++) {
    c->Ekin += 0.5 * p[i].mass * (p[i].v[0]*p[i].v[0]+p[i].v[1]*p[i].v[1]+p[i].v[2]*p[i].v[2]);
  }
  
  //Initial intgrt value t, B & w=====================//
  c->t = t;
  c->B = c->Pot - c->Ekin;
  c->w = c->B;
}

void get_Wij(const particle *p, const chain *c, int option) {
  double **Wij=c->Wij;
  assert(Wij!=NULL);
  int num=c->num;
  //  if(Wij==NULL) Wij=new double*[num];
  if(option==0) {
    double m2=0.;
    for (int i=0;i<num;i++) {
      //    if(Wij[i]==NULL) Wij[i]=new double[num];
      for (int j=i+1;j<num;j++) {
        m2 += p[i].mass * p[j].mass;
      }
    }
    m2 /= num * (num - 1) / 2;
    for (int i=0;i<num;i++) {
      for (int j=0;j<num;j++) {
        if (p[c->list[i]].mass*p[c->list[j]].mass<1E-3*m2) Wij[i][j] = m2;
        else Wij[i][j]=0;
      }
    }
  }
  else {
    for (int i=0;i<num;i++) {
      for (int j=0;j<num;j++) {
        Wij[i][j] = p[c->list[i]].mass * p[c->list[j]].mass;
      }
    }
  }
}
  

//Chech and update chain member=====================//
void check_chain(particle *p, chain *c) {
  //generate new chain link list======================//
  int *list=new int[c->num];
  generate_list(c->num,p,list);
  
  // #ifdef DEBUG
  //   printf("List New :");
  //   for (int i=0;i<c->num;i++) printf("%d ",list[i]);
  //   printf("\n");
  //   printf("List Old :");
  //   for (int i=0;i<c->num;i++) printf("%d ",c->list[i]);
  //   printf("\n");  
  // #endif  

  //Generate transform matrix=========================//
  int istart=-1;
  for (int i=0;i<c->num;i++) {
    if (list[i]!=c->list[i]) {
      istart=i;
      break;
    }
  }
  if (istart==-1) return; //No change
  int iend=c->num;
  for (int i=c->num-1;i>=0;i--) {
    if (list[i]!=c->list[i]) {
      iend=i;
      break;
    }
  }
  int ntr=iend - istart + 2;
  int *direct=new int[ntr+1];
  direct[0] = istart-1;
  for (int i=istart;i<=iend;i++) {
    for (int j=istart;j<=iend;j++) {
      if(list[i]==c->list[j]) {
        if(istart>0) direct[i-istart+1]=j;
        else direct[i-istart]=j;
        break;
      }
    }
  }
  direct[ntr] = iend+1;
  
  if(istart==0) ntr--;
  if(iend==c->num-1) ntr--;

  chain_mem *nm=new chain_mem[ntr];

  int ia,ib;
  for (int i=0;i<ntr;i++) {
    ia=direct[i];
    ib=direct[i+1];
    memset(nm[i].X,0,3*sizeof(double));
    memset(nm[i].V,0,3*sizeof(double));
    assert(ia!=ib);
    if (ia<ib) {
      for (int j=ia;j<ib;j++) {
        nm[i].X[0] +=c->m[j].X[0];
        nm[i].X[1] +=c->m[j].X[1];
        nm[i].X[2] +=c->m[j].X[2];
        nm[i].V[0] +=c->m[j].V[0];
        nm[i].V[1] +=c->m[j].V[1];
        nm[i].V[2] +=c->m[j].V[2];
      }
    }
    if (ia>ib) {
      for (int j=ib;j<ia;j++) {
        nm[i].X[0] -=c->m[j].X[0];
        nm[i].X[1] -=c->m[j].X[1];
        nm[i].X[2] -=c->m[j].X[2];
        nm[i].V[0] -=c->m[j].V[0];
        nm[i].V[1] -=c->m[j].V[1];
        nm[i].V[2] -=c->m[j].V[2];
      }
    }
  }

  if(istart==0) memcpy(&c->m[istart],nm,ntr*sizeof(chain_mem));
  else memcpy(&c->m[istart-1],nm,ntr*sizeof(chain_mem));
  memcpy(&c->list[istart],&list[istart],(iend-istart+1)*sizeof(chain_mem));

  get_Wij(p,c,1);
}


//Get Potential, Acceleration, Transformation coefficient
void get_chain_pars(const particle *p, const double3 *force, chain *c) {
  int num=c->num;
  double4 **rjk=c->rjk;
  chain_mem *m=c->m;
  double **Wij=c->Wij;
  double3 *acc=c->acc;
  assert(num>0);
  assert(rjk!=NULL);
  assert(m!=NULL);
  assert(Wij!=NULL);
  assert(acc!=NULL);

  //Distance Matrix===================================//
  for (int j=0;j<num;j++) {
    for (int k=j;k<num;k++) {
      if(k==j) memset(rjk[j][k],0,4*sizeof(double));
      else {
        if(k==j+1) memcpy(rjk[j][k],m[j].X,3*sizeof(double));
        else if(k==j+2) {
          rjk[j][k][0] = m[j].X[0] + m[j+1].X[0];
          rjk[j][k][1] = m[j].X[1] + m[j+1].X[1];
          rjk[j][k][2] = m[j].X[2] + m[j+1].X[2];
        }
        else {
          rjk[j][k][0] = p[c->list[k]].x[0]-p[c->list[j]].x[0];
          rjk[j][k][1] = p[c->list[k]].x[1]-p[c->list[j]].x[1];
          rjk[j][k][2] = p[c->list[k]].x[2]-p[c->list[j]].x[2];
        }
        rjk[j][k][3] = std::sqrt(rjk[j][k][0]*rjk[j][k][0]+rjk[j][k][1]*rjk[j][k][1]+rjk[j][k][2]*rjk[j][k][2]);
      }
    }
  }
  for (int j=0;j<num;j++) {
    for (int k=0;k<j;k++) {
      rjk[j][k][0] = -rjk[k][j][0];
      rjk[j][k][1] = -rjk[k][j][1];
      rjk[j][k][2] = -rjk[k][j][2];
      rjk[j][k][3] = rjk[k][j][3];
    }
  }

  //Initial===========================================//
  c->Pot  = 0.;
  c->W    = 0.;

  for (int k=0; k<num; k++) {
    const particle *pk= &p[c->list[k]];

    //Acceleration==========================================//
    memset(acc[k],0,3*sizeof(double));

    for (int j=0; j<num; j++) {
      if(k==j) continue;
      const particle *pj = &p[c->list[j]];

      //Acceleration======================================//
      double rjk3 = rjk[j][k][3]*rjk[j][k][3]*rjk[j][k][3];
      acc[k][0] -= pj->mass * rjk[j][k][0] / rjk3;
      acc[k][1] -= pj->mass * rjk[j][k][1] / rjk3;
      acc[k][2] -= pj->mass * rjk[j][k][2] / rjk3;

#ifdef DEBUG
      NAN_CHECK(rjk3);
#endif    
    
      if(j>k) continue;
      //Potential energy==================================//
      c->Pot += pk->mass * p[c->list[j]].mass / rjk[j][k][3];

      //Transformation coefficient========================//
      c->W += Wij[j][k] / rjk[j][k][3];
    }
    //Acceleration======================================//
    acc[k][0] += force[c->list[k]][0];
    acc[k][1] += force[c->list[k]][1];
    acc[k][2] += force[c->list[k]][2];
  }
}

//Integrate position================================//
//Update position, time=============================//
void chain_intgrt_X(const double *intpar, const double &s, particle *p, chain *c) {
  chain_mem *m=c->m;
  assert(m!=NULL);
  
  double dt = s / (intpar[0] * (c->Ekin + c->B) + intpar[1] * c->w + intpar[2]);
  c->t += dt;

  double3 XT = {0., 0., 0.};
  double3 Xcm = {0., 0., 0.};
  for (int k=0;k<c->num-1;k++) {
#ifdef DEBUG
    NAN_CHECK(m[k].V[0]);
    NAN_CHECK(m[k].V[1]);
    NAN_CHECK(m[k].V[2]);
#endif    
    m[k].X[0] += dt * m[k].V[0];
    m[k].X[1] += dt * m[k].V[1];
    m[k].X[2] += dt * m[k].V[2];

    XT[0] += m[k].X[0];
    XT[1] += m[k].X[1];
    XT[2] += m[k].X[2];

    particle *pk=&p[c->list[k+1]];
    //Update position===================================//
    memcpy(pk->x,XT,3*sizeof(double));

    //Calculate center mass position====================//
    Xcm[0]+= pk->mass * pk->x[0];
    Xcm[1]+= pk->mass * pk->x[1];
    Xcm[2]+= pk->mass * pk->x[2];
  }
  Xcm[0] /= c->mtot;
  Xcm[1] /= c->mtot;
  Xcm[2] /= c->mtot;

  //Center mass correction============================//
  memset(p[c->list[0]].x,0,3*sizeof(double));
  for (int k=0;k<c->num;k++) {
    p[k].x[0] -= Xcm[0];
    p[k].x[1] -= Xcm[1];
    p[k].x[2] -= Xcm[2];

#ifdef DEBUG
    NAN_CHECK(p[k].x[0]);
    NAN_CHECK(p[k].x[1]);
    NAN_CHECK(p[k].x[2]);
#endif    
  }
}

//Integrate velocity================================//
//Update velocity, time momemtum B, w===============//
void chain_intgrt_V(const double *intpar, const double &s, const double3 *force, particle *p, chain *c) {
  chain_mem *m=c->m;
  double3 *acc=c->acc;
  double4 **rjk=c->rjk;
  assert(m!=NULL);
  assert(acc!=NULL);
  assert(rjk!=NULL);

  double dt = s / (intpar[0] * c->Pot + intpar[1] * c->W + intpar[2]);
  double3* VT = new double3[c->num];
  VT[0][0]=VT[0][1]=VT[0][2]=0.;
  double3 Vcm = {0., 0., 0.};
  for (int k=0;k<c->num-1;k++) {
    particle *pk= &p[c->list[k+1]];
    //Velocity==========================================//
    m[k].V[0] += dt * (acc[k+1][0] - acc[k][0]);
    m[k].V[1] += dt * (acc[k+1][1] - acc[k][1]);
    m[k].V[2] += dt * (acc[k+1][2] - acc[k][2]);

    VT[k+1][0] = VT[k][0] + m[k].V[0];
    VT[k+1][1] = VT[k][1] + m[k].V[1];
    VT[k+1][2] = VT[k][2] + m[k].V[2];

    //Calculate center mass velocity====================//
    Vcm[0] += pk->mass * VT[k+1][0];
    Vcm[1] += pk->mass * VT[k+1][1];
    Vcm[2] += pk->mass * VT[k+1][2];
  }
  Vcm[0] /= c->mtot;
  Vcm[1] /= c->mtot;
  Vcm[2] /= c->mtot;

  //Initial Ekin======================================//
  c->Ekin = 0.;
  
  for (int k=0;k<c->num;k++) {
    particle *pk= &p[c->list[k]];
    VT[k][0] -= Vcm[0];
    VT[k][1] -= Vcm[1];
    VT[k][2] -= Vcm[2];
    
    double3 Vh; //Average velocity
    Vh[0] = VT[k][0] + pk->v[0];
    Vh[1] = VT[k][1] + pk->v[1];
    Vh[2] = VT[k][2] + pk->v[2];

    //Update velocity===================================//
    memcpy(pk->v,VT[k],3*sizeof(double));

    //time momentum=====================================//
    c->B -= dt * (pk->mass * 0.5 *
                  (Vh[0] * force[c->list[k]][0] +
                   Vh[1] * force[c->list[k]][1] +
                   Vh[2] * force[c->list[k]][2]));

    //transformation coefficient========================//
    double dw=0.;
    for (int j=0;j<c->num;j++) {
      if (k<j) dw -= c->Wij[k][j] * (Vh[0] * rjk[k][j][0] + Vh[1] * rjk[k][j][1] + Vh[2] * rjk[k][j][2]) / (rjk[k][j][3] * rjk[k][j][3] * rjk[k][j][3]);
      if (k>j) dw += c->Wij[k][j] * (Vh[0] * rjk[k][j][0] + Vh[1] * rjk[k][j][1] + Vh[2] * rjk[k][j][2]) / (rjk[k][j][3] * rjk[k][j][3] * rjk[k][j][3]);
    }
    c->w += 0.5 * dt * dw;

    //Kinetic energy====================================//
    c->Ekin += 0.5 * pk->mass * (pk->v[0]*pk->v[0]+pk->v[1]*pk->v[1]+pk->v[2]*pk->v[2]);
  }
}
