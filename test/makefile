all: a.out

CPPFLAGS=-O3 -std=c++11

a.out: test.cpp ../sdouble.hpp
	g++ $(CPPFLAGS) $< -o $@

.PHONY: clean

test: a.out
	./a.out > test.txt
	diff test.txt expected_results.txt

clean:
	rm -f a.out
