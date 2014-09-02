CC= g++ -O0 -g -D LINK -D EX_INFO

MYCFLAGS =-I$(shell echo ~)/include
CPPEXTRALIBS	+= -L$(shell echo ~)/lib -linitial

CPPSOURCE	=$(shell ls *.cpp)
CPOBJECTS = $(CPPSOURCE:.cpp=)

all: $(CPOBJECTS)

$(CPOBJECTS): %: %.cpp
	$(CC)  $< -o $@ $(MYCFLAGS) $(CPPEXTRALIBS)
	@echo $@ >>.mvlist
	@sort .mvlist|uniq >.mvlist.tmp
	@mv .mvlist.tmp .mvlist

install: $(shell cat .mvlist)
	mv -f $(shell uniq .mvlist) ~/bin/

clean:
	rm -f $(CPOBJECTS)
	rm -f .mvlist
	rm -rf *.dSYM
