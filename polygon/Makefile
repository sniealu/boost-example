all: boost_poly

CXX = g++

OFLAGS = -pedantic -fomit-frame-pointer -funroll-all-loops -O3

LINKFLAGS = -static

boost_poly: boost_poly.o main.o
	$(CXX) $(OFLAGS) main.o boost_poly.o -o boost_poly

main.o : main.cpp
	$(CXX) $(OFLAGS)  main.cpp -c

boost_poly.o: boost_poly.cpp boost_poly.h
	$(CXX) $(OFLAGS)  boost_poly.cpp boost_poly.h -c
clean:
	rm -rf *.o *.gch boost_poly
