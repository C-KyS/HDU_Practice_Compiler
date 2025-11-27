main:main.cpp
	g++ -o $@ $^ 
nfa.png:nfa.dot
	dot -Tpng nfa.dot -o nfa.png

.phony:clean
clean:
	rm -f main
	rm -f *.dot
	rm -f *.png
	