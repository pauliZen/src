FFLAGS = -O3
#FFLAGS = -O3 -fbounds-check
FC = gfortran
LD = gfortran

SOURCE = \
hermit.f block.f input.f kscorr.f ksinit.f ksint.f kslist.f \
kspert.f kspoly.f kspred.f ksres.f matrix.f tpert.f unpert.f \
iblock.f stepk.f check.f newton.f pnpert.f

OBJECTS = $(SOURCE:.f=.o)

hermit:	$(OBJECTS)
	$(LD) $(FFLAGS) $(OBJECTS) -o hermit

clean:
	rm *.o

print:
	@- \rm -f HERMIT.TEXT
	@cat $(SOURCE) > HERMIT.TEXT
