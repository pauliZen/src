#ifndef readout3_h
#define readout3_h

//read out3 data====================================//

struct header{
  int ntot;
  int model;
  int nrun;
  int nk;
};

struct as{
  float pars[20];
};

template <struct T>
void particle_fread(const char* name, T *list, int count)
{
  FILE *stream;
  if ( (stream = fopen(name, "r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",name);
    return;
  }
  /* read the data and display it */
  fread(list, sizeof(T), count, stream);
  fclose(stream);
}

#endif
