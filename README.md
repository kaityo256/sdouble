# Single-header C++ library for double with error propagation

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

A single-header C++ for double with error propagation.

## Usage

### constructor

```cpp
stat::sdouble v;
stat::sdouble v(mean, error);
```

The constructor `stat::sdouble v(mean, error)` creates an `stat::sdouble` object whose mean is `mean` and the error (standard deviation) is `error`. Without arguments, the constructor creates an uninitialized object.

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
stat::sdouble x1(10,2);
stat::sdouble x2(5,1);
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

`stat::sdouble` can store the data with `<<` operator.

Here is the sample.

```cpp
stat::sdouble x;
x << 1.0;
x << 2.0;
x << 3.0;
x << 4.0;
std::cout << v << std::endl;
```

The output will be `average +- stddev of the mean`.

```txt
2.5 +- 0.645497
```

When `stat::double` is put into stream, it will show *the standard deviation of the mean* instead of *the sample standard deviation*. You can obtain the sample standard deviation by `stddev()` which is identical to `STDEV.S` function of Excel.

## License

This software is released under the MIT License, see [LICENSE](LICENSE).
