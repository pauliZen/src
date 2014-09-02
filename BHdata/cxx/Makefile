#target: stardatatoroot bhdatatoroot bhnbdatatoroot bhpardatatoroot stardeltaenergy totalenergychange selectstarlog stardeltaenergysimple

ROOTCFLAGS              =$(shell root-config  --cflags)
#ROOTLIBS                =$(shell root-config  --libs)
ROOTGLIBS               =$(shell root-config  --glibs)

#EXTRALIBS       +=$(ROOTLIBS)
EXTRALIBS       +=$(ROOTGLIBS)
EXTRALIBS       +=-lSpectrum -fpermissive
EXTRALIBS	+=-I${shell echo ~}/include -L${shell echo ~}/lib -linitial

#CPPFLAGS       +=$(ROOTCFLAGS)                                              

SOURCE	=$(shell ls *.cxx)
OBJECTS = $(SOURCE:.cxx=)

CC= g++ -Wall -O3 -D DRAWE #-D NOROT
#CC = g++ -Wall -g -O0 -Warray-bounds

all: $(OBJECTS)

$(OBJECTS): %: %.cxx
	$(CC) $(EXTRALIBS) $(ROOTCFLAGS) $< -o $@
	@echo $@ >>.mvlist
	@sort .mvlist|uniq >.mvlist.tmp
	@mv .mvlist.tmp .mvlist

install: $(shell cat .mvlist)
	mv -f $(shell uniq .mvlist) ~/bin/

clean:
	rm -f $(OBJECTS)
	rm -f .mvlist

# Selectstarlog: select-stars-log.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) select-stars-log.cxx -o selectstarlog

# stardatatoroot: stardatatoroot.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) stardatatoroot.cxx -o stardatatoroot

# bhdatatoroot: bhdatatoroot.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) bhdatatoroot.cxx -o bhdatatoroot

# bhnbdatatoroot: bh_nbdatatoroot.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) bh_nbdatatoroot.cxx -o bhnbdatatoroot

# bhpardatatoroot: pardatatoroot.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) pardatatoroot.cxx -o bhpardatatoroot

# stardeltaenergy: star-delta-energy.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) star-delta-energy.cxx -o stardeltaenergy

# stardeltaenergysimple: star-delta-energy-simple.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) star-delta-energy-simple.cxx -o stardeltaenergysimple

# totalenergychange: total-energy-change.cxx
# 	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) total-energy-change.cxx -o totalenergychange


# mv -f stardatatoroot ~/bin/
# mv -f bhdatatoroot ~/bin/
# mv -f bhnbdatatoroot ~/bin/
# mv -f bhpardatatoroot ~/bin/
# mv -f stardeltaenergy ~/bin/
# mv -f stardeltaenergysimple ~/bin/
# mv -f totalenergychange ~/bin/
# mv -f selectstarlog ~/bin/

# installall: stardatatoroot bhdatatoroot bhnbdatatoroot bhpardatatoroot stardeltaenergy stardeltaenergysimple  totalenergychange selectstarlog
# 	mv -f stardatatoroot ~/bin/
# 	mv -f bhdatatoroot ~/bin/
# 	mv -f bhnbdatatoroot ~/bin/
# 	mv -f bhpardatatoroot ~/bin/
# 	mv -f stardeltaenergy ~/bin/
# 	mv -f stardeltaenergysimple ~/bin/
# 	mv -f totalenergychange ~/bin/
# 	mv -f selectstarlog ~/bin/

# uninstall:
# 	rm -f ~/bin/stardatatoroot
# 	rm -f ~/bin/bhdatatoroot
# 	rm -f ~/bin/bhnbdatatoroot
# 	rm -f ~/bin/bhpardatatoroot
# 	rm -f ~/bin/stardeltaenergy
# 	rm -f ~/bin/stardeltaenergysimple
# 	rm -f ~/bin/totalenergychange
# 	rm -f ~/bin/selectstarlog

