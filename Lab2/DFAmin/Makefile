main:main.cpp
	g++ -o $@ $^ 
	
nfa:nfa.dot
	dot -Tpng nfa.dot -o nfa.png
dfa:dfa.dot
	dot -Tpng dfa.dot -o dfa.png
mindfa:mindfa.dot
	dot -Tpng mindfa.dot -o mindfa.png

.phony:clean
clean:
	rm -f main
	rm -f *.dot
	rm -f *.png
	