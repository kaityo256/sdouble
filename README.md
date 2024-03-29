# Single-header C++ library for double with error propagation

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

A single-header C++ for double with error propagation.

## Usage

### constructor

```cpp
stat::sdouble v(double mean, double error);
stat::sdouble v(std::vector<double> &r);
```

This constructor creates an `stat::sdouble` object whose mean is `mean` and the error (standard deviation) is `error`.

```cpp
stat::sdouble v(std::vector<double> &r);
```

This constructor creates an `stat::sdouble` object whose means and the error calculated from the given array `r`.

Without arguments, the constructor creates an uninitialized object.

### Print the values

When `stat::double` is put into stream, it will show the mean and error.

```cpp
stat::sdouble v(5.1,1.2);
std::cout << v << std::endl;
```

Here is the output.

```txt
5.1 +- 1.2
```

### Error Propagation

Calculations between `stat::sdouble` variables follows the error propagation formula.

Here is a sample code.

```cpp
  stat::sdouble x1(10, 2);
  stat::sdouble x2(5, 1);
  std::cout << x1 + x2 << std::endl;
  std::cout << x1 - x2 << std::endl;
  std::cout << x1 * x2 << std::endl;
  std::cout << x1 / x2 << std::endl;
```

Output.

```txt
15 +- 2.23607
5 +- 2.23607
50 +- 14.1421
2 +- 0.565685
```

Here is the identical python script.

```py
from uncertainties import ufloat
  
x1 = ufloat(10.0, 2.0)
x2 = ufloat(5.0, 1.0)

print(x1 + x2)
print(x1 - x2)
print(x1 * x2)
print(x1 / x2)
```

Other operators such as `-`, `*`, `/` are definined with similar manner.

## Data input

`stat::sdouble` can be created from `std::vector<double>`.

Here is the sample.

```cpp
std::vector<double> r;
r.push_back(1.0);
r.push_back(2.0);
r.push_back(3.0);
r.push_back(4.0);
stat::sdouble v(r);
std::cout << v << std::endl;
```

The output will be `average +- stddev of the mean`.

```txt
2.5 +- 0.645497
```

When `stat::double` is put into stream, it will show *the standard deviation of the mean* instead of *the sample standard deviation*. You can obtain the sample standard deviation by `stddev()` which is identical to `STDEV.S` function of Excel.

### Sample Code

Here is a sample code in `random` directory. It investigates the sample-number dependence of the standard deviation.

```cpp
#include "../sdouble.hpp"
#include <iostream>
#include <random>

int main() {
  std::mt19937 mt(1);
  std::uniform_real_distribution<double> ud(0.0, 1.0);
  const int total_loop = 100000;
  const int observe_loop = 100;
  stat::sdouble data;
  for (int i = 0; i <= total_loop; i++) {
    data << ud(mt);
    if (i % observe_loop == 0) {
      std::cout << i << " " << data << std::endl;
    }
  }
}
```

Here is the average. It converges to 0.5.

![Average](random/average.png)

Here is the standard deviation. It reduces as 1/sqrt(N) where N is the number of samples.

![Standard deviation](random/stddev.png)

## Wrapper of MPI_Allreduce

`stat::mpi::reduce` is the wrapper of `MPI_Allreduce`. You can use it by including `sdouble_mpi.hpp`.

Here is the sample.

```cpp
#include "sdouble_mpi.hpp"
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
```

When the number of proccesses is 4, the above sample is identical to

```cpp
std::vector<double> v;
v.push_back(1.0);
v.push_back(2.0);
v.push_back(3.0);
v.push_back(4.0);
stat::sdouble sd;
std::cout << sd << std::endl;
```

The output will be as follows.

```sh
$ mpic++ test.cpp
$ mpirun -np 4 ./a.out
2.5 +- 0.645497
```

## License

This software is released under the MIT License, see [LICENSE](LICENSE).
