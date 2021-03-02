#include "../sdouble_mpi.hpp"
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  double v = rank + 1.0;
  stat::sdouble sd = stat::mpi::reduce(v);
  if (rank == 0) {
    std::cout << sd << std::endl;
  }
  MPI_Finalize();
}
