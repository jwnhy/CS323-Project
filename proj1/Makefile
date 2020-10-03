CC=gcc
FLEX=flex
BISON=bison


.lex: spl.l
	$(FLEX) spl.l
.syntax: spl.y
	$(BISON) -t -d spl.y
jp: .lex .syntax
	$(CC) spl.tab.c node.c -lfl -ly -o jp.out
clean:
	@rm -f lex.yy.c spl.tab.* *.out
