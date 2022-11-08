parse: parse.o scan.o
	g++ -o parse parse.o scan.o
	g++ -c scantest.cpp
	g++ -o scantest scan.o scantest.o

clean:
	rm *.o parse

primes:
	./parse < primes.cl

average:
	./parse < average.cl

scantest:
	g++ -c scantest.cpp
	g++ -o scantest scan.o scantest.o

parse.o: scan.h
scan.o: scan.h
