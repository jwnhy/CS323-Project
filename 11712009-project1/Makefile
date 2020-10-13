CC=g++
FLEX=flex
BISON=bison
splfolder=src/splc
sppfolder=src/spp

spll=$(splfolder)/spl.l
sply=$(splfolder)/spl.y
spllex=$(splfolder)/gen/lex.yy.c
splsyn=$(splfolder)/gen/spl.tab.c
splsyndef=$(splfolder)/gen/spl.tab.h
splsrc=$(splfolder)/ext/ce.c $(splfolder)/ext/node.c $(splfolder)/gen/spl.tab.c $(sppfolder)/spp.cpp
splbin=bin/splc


.lex: $(spll)
	$(FLEX) -o $(spllex) $(spll) 
.syntax: $(sply)
	$(BISON) -o $(splsyn) -t --defines=$(splsyndef) $(sply) 
splc: .lex .syntax
	$(CC) $(splsrc) -g -lfl -ly -o $(splbin)
clean:
	@rm src/splc/gen/* bin/*
