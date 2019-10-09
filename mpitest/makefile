all: a.out

CC=mpic++
CPPFLAGS=-Wall -Wextra -std=c++11

a.out: test.cpp ../sdouble_mpi.hpp ../sdouble.hpp
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f a.out
