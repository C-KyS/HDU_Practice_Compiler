ss: ss.l ss.y ast.h
	bison -d ss.y -o ss.tab.c
	flex -o ss.c ss.l
	g++ ss.c ss.tab.c -o ss

clean:
	rm -f *.c  *.tab.h ss