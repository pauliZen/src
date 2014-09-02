#!/usr/bin/env python
import os
import sys
import numpy
import random
import scipy
def randompara(i):
	i=str(i)
	ff=open('test.cfg','w')
	T0=random.uniform(0,20)
	rcool=random.uniform(100,1000)
	acool=random.uniform(0,50)
	Tmin=random.uniform(0,50)
	rt=random.uniform(100,1000)
	a=random.uniform(-1.,0)
	c=random.uniform(5,50)
	b=random.uniform(0,10)
	ff.write('/home/yao/xdata/scripts/kt.out\n')
	ff.write('kt.qdp\n')
	ff.write('T0\t'+`T0`+'\n')
	ff.write('rcool\t'+`rcool`+'\n')
	ff.write('acool\t'+`acool`+'\n')
	ff.write('Tmin\t'+`Tmin`+'\n')
	ff.write('rt\t'+`rt`+'\n')
	ff.write('a\t'+`a`+'\n')
	ff.write('c\t'+`c`+'\n')
	ff.write('b\t'+`b`+'\n')
	ff.close()
	os.system('./dynamical_fit.out test.cfg a.qdp para'+i+'.txt')
	os.system("cat a.qdp kt.qdp>b.qdp")
	os.system("qdp<<EOF\nb.qdp\n/ps\n")
	os.system('mv pgplot.ps '+i+'.ps')
for i in range(1,100):
	randompara(i)
