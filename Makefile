teste:
	g++ -std=c++11 -Wall -I include/ src/abb.cpp src/main.cpp -o bin/main
clean:
	rm bin/*.cpp
