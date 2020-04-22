all: a.out

CPPFLAGS=-O3 -std=c++11

a.out: random_test.cpp ../sdouble.hpp
	g++ -Wall -Wextra $(CPPFLAGS) $< -o $@

.PHONY: clean

graph: average.png stddev.png

average.png: test.dat

stddev.png: test.dat

test.dat: a.out
	./a.out > test.dat


%.png: %.plt
	gnuplot $<


clean:
	rm -f a.out
