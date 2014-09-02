#ifndef FILE_H
#define FILE_H

// Provide particle data storing, reading

#include <cassert>
#include <stdio.h>
#include "particle.h"

void particle_fread(const char* name, particle *list, int count)
{
  FILE *stream;
  if ( (stream = fopen(name, "r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",name);
    return;
  }
  /* read the data and display it */
  fread(list, sizeof(particle), count, stream);
  fclose(stream);
}

void particle_fwrite(const char* name, particle *list, int count)
{
  FILE *stream;
  if ( (stream = fopen(name, "w")) == NULL) {
    fprintf(stderr,"Error: Cannot open output file %s.\n",name);
    return;
  }
  /* write some data to the file */
  fwrite(list, sizeof(particle), count, stream);
  fclose(stream);
}

void particle_scanf(const char* name, particle *list, int count)
{
  if ( freopen(name, "r",stdin) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",name);
    return;
  }
  for (int i=0;i<count;i++)
  {
    int sct;
    sct=scanf("%lg %lg %lg %lg %lg %lg %lg",&list[i].mass,&list[i].r[0],&list[i].r[1],
              &list[i].r[2],&list[i].v[0],&list[i].v[1],&list[i].v[2]);
    if (sct<7) fprintf(stderr, "Error: Line %d Reading Fail (intput %d < 7).\n",i,sct);
  }
  fclose(stdin);
}

void particle_fprint(particle *list, int count)
{
  fprintf(stdout, "m           x           y           z           vx           vy           vz\n");
  for (int i=0; i<count;i++)
  {
    fprintf(stdout, "%10lF %10lF %10lF %10lF %10lF %10lF %10lF\n",list[i].mass,list[i].r[0],list[i].r[1],list[i].r[2],list[i].v[0],list[i].v[1],list[i].v[2]);
  }
}

#endif
