teste:
	g++ -std=c++11 -Wall -I include/ src/abb.cpp src/testeABB.cpp -o bin/teste

clean:
	rm bin/teste
