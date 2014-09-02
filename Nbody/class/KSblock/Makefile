FFLAGS = -O
FORTRAN = f77

SOURCE = \
hermit.f block.f input.f kscorr.f ksinit.f ksint.f kslist.f \
kspert.f kspoly.f kspred.f ksres.f matrix.f tpert.f unpert.f

OBJECTS = $(SOURCE:.f=.o)

hermit:	$(OBJECTS)
	$(FORTRAN) $(FFLAGS) $(OBJECTS) -o hermit

print:
	@- \rm -f HERMIT.TEXT
	@cat $(SOURCE) > HERMIT.TEXT
