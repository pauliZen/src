FFLAGS = -O
FC = gfortran

SOURCE = \
hermit.f block.f input.f kscorr.f ksinit.f ksint.f kslist.f \
kspert.f kspoly.f kspred.f ksres.f matrix.f tpert.f unpert.f

OBJECTS = $(SOURCE:.f=.o)

hermit:	$(OBJECTS)
	$(FC) $(FFLAGS) $(OBJECTS) -o hermit

install: hermit
	mv hermit ~/bin/

clean:
	rm *.o

print:
	@- \rm -f HERMIT.TEXT
	@cat $(SOURCE) > HERMIT.TEXT
