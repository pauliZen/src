target: create_histograms plot_histograms

ROOTCFLAGS		=$(shell root-config  --cflags)
ROOTLIBS		=$(shell root-config  --libs)
ROOTGLIBS		=$(shell root-config  --glibs)

EXTRALIBS	+=$(ROOTLIBS)
EXTRALIBS	+=$(ROOTGLIBS)

#CPPFLAGS	+=$(ROOTCFLAGS)
create_histograms : create_histograms.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) create_histograms.cxx -o create_histograms

plot_histograms : plot_histograms.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) plot_histograms.cxx -o plot_histograms

.PHONY : clean
clean:
	-rm -f create_histograms plot_histograms create_histograms.cxx~ plot_histograms.cxx~ Makefile~

.PHONY : cleanall
cleanall:cleanplot cleanroot cleantable

.PHONY : cleanplot
cleanplot:
	-rm -f $$gerda/data/plots/bi214/lsii/*.eps
	-rm -f $$gerda/data/plots/bi214/sii/*.eps
	-rm -f $$gerda/data/plots/bi214/lsiii/*.eps
	-rm -f $$gerda/data/plots/bi214/siii/*.eps
	-rm -f $$gerda/data/plots/bi212/lsii/*.eps
	-rm -f $$gerda/data/plots/bi212/sii/*.eps
	-rm -f $$gerda/data/plots/bi212/lsiii/*.eps
	-rm -f $$gerda/data/plots/bi212/siii/*.eps

.PHONY : cleanroot
cleanroot:
	-rm -f $$gerda/data/histograms/bi214.sii.root
	-rm -f $$gerda/data/histograms/bi214.siii.root
	-rm -f $$gerda/data/histograms/bi212.sii.root
	-rm -f $$gerda/data/histograms/bi212.siii.root

.PHONY : cleantable
cleantable:
	-rm -f $$gerda/data/table/bi214/lsii/*.txt
	-rm -f $$gerda/data/table/bi214/lsiii/*.txt
	-rm -f $$gerda/data/table/bi214/sii/*.txt
	-rm -f $$gerda/data/table/bi214/siii/*.txt
	-rm -f $$gerda/data/table/bi212/lsii/*.txt
	-rm -f $$gerda/data/table/bi212/lsiii/*.txt
	-rm -f $$gerda/data/table/bi212/sii/*.txt
	-rm -f $$gerda/data/table/bi212/siii/*.txt