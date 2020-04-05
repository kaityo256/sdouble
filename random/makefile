all: a.out

CPPFLAGS=-O3 -std=c++11

a.out: random_test.cpp ../sdouble.hpp
	g++ $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f a.out
