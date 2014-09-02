target: energy_divide plot_histograms findpeaks resolutionf seg_ab_tot_single ecore_etot

ROOTCFLAGS		=$(shell root-config  --cflags)
ROOTLIBS		=$(shell root-config  --libs)
ROOTGLIBS		=$(shell root-config  --glibs)

EXTRALIBS	+=$(ROOTLIBS)
EXTRALIBS	+=$(ROOTGLIBS)
EXTRALIBS	+=-lSpectrum

#CPPFLAGS	+=$(ROOTCFLAGS)
energy_divide : energy_divide.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) energy_divide.cxx -o energy_divide

plot_histograms : plot_histograms.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) plot_histograms.cxx -o plot_histograms

findpeaks : findpeaks.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) findpeaks.cxx -o findpeaks

resolutionf : resolutionf.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) resolutionf.cxx -o resolutionf

seg_ab_tot_single : seg_ab_tot_single.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) seg_ab_tot_single.cxx -o seg_ab_tot_single

ecore_etot : ecore_etot.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) ecore_etot.cxx -o ecore_etot

.PHONY : clean
clean:
	-rm -f *.*~
	-rm -f *~
	-rm -f energy_divide plot_histograms findpeaks resolutionf seg_ab_tot_single ecore_etot

.PHONY : cleanall
cleanall:cleanplot cleanroot 

.PHONY : cleanplot
cleanplot:
	-rm -f $$gerda/data/plots/edsii/*.*
	-rm -f $$gerda/data/plots/edsiii/*.*
	-rm -f $$gerda/data/plots/ecore.etot.*

.PHONY : cleanroot
cleanroot:
	-rm -f $$gerda/data/histograms/h.sii.ecoto.root
	-rm -f $$gerda/data/histograms/h.siii.ecoto.root
	-rm -f $$gerda/data/histograms/sii.energy.resolution.root
	-rm -f $$gerda/data/histograms/siii.energy.resolution.root
