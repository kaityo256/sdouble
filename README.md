# Single-header C++ library for double with error propagation

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

A single-header C++ for double with error propagation.

## Usage

Here is the sample.

```cpp
#include "sdouble.hpp"
#include <iostream>
#include <random>

std::mt19937 mt(1);
std::normal_distribution<> nd(100.0, 3.0);

int main() {
  stat::sdouble v;
  for (int i = 0; i < 1000; i++) {
    v << nd(mt);
  }
  std::cout << "Mean and standard deviation" << std::endl;
  std::cout << v.mean() << " +- " << v.stddev() << std::endl;
  std::cout << "Mean and standard deviation of the mean" << std::endl;
  std::cout << v << std::endl;
}
```

And here is the expected results.

```txt
Mean and standard deviation
99.9247 +- 2.9753
Mean and standard deviation of the mean
99.9247 +- 0.0941344
```

When `stat::double` is put into stream, it will show the standard deviation of the mean instead of the sample standard deviation. You can obtain the sample standard deviation by `stddev()`.

## Test

```cpp
make
./a.out
```

Expected results.

```txt
Test for standard deviation
----------------
Mean and standard deviation
99.9247 +- 2.9753
Mean and standard deviation of the mean
99.9247 +- 0.0941344

Tests for error propagation
----------------
Add Test
d1    = 100.006 +- 0.00300081
d2    = 49.9986 +- 0.000999754
d1+d2 = 150.005 +- 0.00316399
d1+d2 = 150.005 +- 0.00316297

Subtraction Test
d1    = 99.9992 +- 0.00300174
d2    = 49.9996 +- 0.000998951
d1-d2 = 49.9996 +- 0.00316422
d1-d2 = 49.9996 +- 0.0031636

Multiplication Test
d1    = 99.998 +- 0.00299997
d2    = 49.9999 +- 0.000999695
d1*d2 = 4999.89 +- 0.180274
d1*d2 = 4999.89 +- 0.180258

Division Test
d1    = 100.002 +- 0.00299843
d2    = 49.9996 +- 0.00100151
d1/d2 = 2.00086 +- 7.22068e-05
d1/d2 = 2.00006 +- 7.21197e-05
```

## License

This software is released under the MIT License, see [LICENSE](LICENSE).
