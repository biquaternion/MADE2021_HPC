all: demo
demo: main.o matmul.o mat.o
	g++ main.o mat.o matmul.o -o demo

main.o: main.cpp
	g++ -c -std=c++17 -O3 main.cpp

mat.o: mat.cpp
	g++ -c -std=c++17 -O3 mat.cpp

matmul.o: matmul.cpp
	g++ -c -std=c++17 -O3 matmul.cpp

clean:
	rm -rf *.o demo

clean-all:
	rm -rf *.o demo *.csv