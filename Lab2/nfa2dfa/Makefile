main:main.cpp
	g++ -o $@ $^ 
	
nfa:nfa.dot
	dot -Tpng nfa.dot -o nfa.png
dfa:dfa.dot
	dot -Tpng dfa.dot -o dfa.png

.phony:clean
clean:
	rm -f main
	rm -f *.dot
	rm -f *.png
	