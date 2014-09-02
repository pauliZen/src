target: energy_scaling plot_histograms

ROOTCFLAGS		=$(shell root-config  --cflags)
ROOTLIBS		=$(shell root-config  --libs)
ROOTGLIBS		=$(shell root-config  --glibs)

EXTRALIBS	+=$(ROOTLIBS)
EXTRALIBS	+=$(ROOTGLIBS)

#CPPFLAGS	+=$(ROOTCFLAGS)
energy_divide : energy_scaling.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) energy_scaling.cxx -o energy_scaling

plot_histograms : plot_histograms.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) plot_histograms.cxx -o plot_histograms

.PHONY : clean
clean:
	-rm -f energy_scaling plot_histograms energy_scaling.cxx~ plot_histograms.cxx~ Makefile~

.PHONY : cleanall
cleanall:cleanplot cleanroot 

.PHONY : cleanplot
cleanplot:
	-rm -f $$gerda/data/plots/edscal/*.eps


.PHONY : cleanroot
cleanroot:
	-rm -f $$gerda/data/second.root



