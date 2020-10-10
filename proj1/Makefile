CC=g++
FLEX=flex
BISON=bison
splfolder=src/splc

spll=$(splfolder)/spl.l
sply=$(splfolder)/spl.y
spllex=$(splfolder)/gen/lex.yy.c
splsyn=$(splfolder)/gen/spl.tab.c
splsyndef=$(splfolder)/gen/spl.tab.h
splsrc=$(splfolder)/ext/ce.c $(splfolder)/ext/node.c $(splfolder)/gen/spl.tab.c 
splbin=bin/splc


.lex: $(spll)
	$(FLEX) -o $(spllex) $(spll) 
.syntax: $(sply)
	$(BISON) -o $(splsyn) -t --defines=$(splsyndef) $(sply) 
splc: .lex .syntax
	$(CC) $(splsrc) -g -lfl -ly -o $(splbin)
spp:
	g++ src/spp/spp.cpp -o bin/spp
clean:
	@rm src/splc/gen/*
