CC=g++
FLEX=flex
BISON=bison
splfolder=src/splc
sppfolder=src/spp
ssafolder=src/ssa

spll=$(splfolder)/spl.l
sply=$(splfolder)/spl.y
spllex=$(splfolder)/gen/lex.yy.c
splsyn=$(splfolder)/gen/spl.tab.c
splsyndef=$(splfolder)/gen/spl.tab.h
splsrc=$(splfolder)/ext/ce.cpp $(splfolder)/ext/node.c $(splfolder)/gen/spl.tab.c 
splbin=bin/splc

sppsrc=$(sppfolder)/spp.cpp

ssasrc=$(ssafolder)/symtable/*.cpp $(ssafolder)/ssa.cpp
.lex: $(spll)
	-@mkdir obj ||:
	-@mkdir $(splfolder)/gen ||:
	$(FLEX) -o $(spllex) $(spll) 
.syntax: $(sply)
	-@mkdir obj ||:
	-@mkdir $(splfolder)/gen ||:
	$(BISON) -o $(splsyn) -t --defines=$(splsyndef) $(sply) 
.spp:
	$(CC) -g -c $(sppsrc)
	mv *.o obj
.ssa:
	$(CC) -g -c $(ssasrc)
	mv *.o obj
splc: .lex .syntax .spp .ssa
	-@mkdir bin ||:
	$(CC) $(splsrc) obj/*.o -g -lfl -ly -o $(splbin)
clean:
	-@rm src/splc/gen/* bin/* obj/* ||:
