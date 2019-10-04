/*
MIT License

Copyright (c) 2019 - present H. Watanabe
The latest version is available at
https://github.com/kaityo256/sdouble

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

namespace stat {

struct sdouble {
  double value; // mean
  double error; // std. dev. of mean

  std::vector<double> x; // X_i
  bool isCalculated;
  sdouble()
      : value(0.0), error(0.0), isCalculated(false) {
  }

  sdouble(double v, double e)
      : value(v), error(e), isCalculated(true) {
  }

  sdouble(const sdouble &obj) {
    if (obj.isCalculated) {
      value = obj.value;
      error = obj.error;
    } else {
      x.resize(obj.x.size());
      std::copy(obj.x.begin(), obj.x.end(), x.begin());
      calculate();
    }
    isCalculated = obj.isCalculated;
  }

  double mean() {
    calculate();
    return value;
  }

  double stddev() {
    calculate();
    return error * sqrt(x.size() - 1.0);
  }

  // Calculate value (mean) and error (std. dev. of mean)
  void calculate() {
    if (isCalculated) return;
    value = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    double e = 0.0;
    for (auto v : x) {
      e += (v - value) * (v - value);
    }
    e /= static_cast<double>((x.size() - 1));
    e /= static_cast<double>(x.size());
    error = sqrt(e);
    isCalculated = true;
  }

  // store X_i
  void add(double v) {
    x.push_back(v);
  }

  // Alias of add
  void operator<<(double v) {
    add(v);
  }
  /*
    Error Propagation
  */
  sdouble operator+(sdouble &rhs) const {
    sdouble x1(*this);
    sdouble x2(rhs);
    x1.calculate();
    x2.calculate();
    double v = x1.value + x2.value;
    double e = sqrt(x1.error * x1.error + x2.error * x2.error);
    return sdouble(v, e);
  }

  sdouble operator-(sdouble &rhs) const {
    sdouble x1(*this);
    sdouble x2(rhs);
    x1.calculate();
    x2.calculate();
    double v = x1.value - x2.value;
    double e = sqrt(x1.error * x1.error + x2.error * x2.error);
    return sdouble(v, e);
  }

  sdouble operator*(sdouble &rhs) const {
    sdouble x1(*this);
    sdouble x2(rhs);
    x1.calculate();
    x2.calculate();
    double v = x1.value * x2.value;
    double e1 = x1.error * x2.value;
    double e2 = x2.error * x1.value;
    double e = sqrt(e1 * e1 + e2 * e2);
    return sdouble(v, e);
  }

  sdouble operator/(sdouble &rhs) const {
    sdouble x1(*this);
    sdouble x2(rhs);
    x1.calculate();
    x2.calculate();
    double v = x1.value / x2.value;
    double e1 = x1.error / x1.value;
    double e2 = x2.error / x2.value;
    double e = v * sqrt(e1 * e1 + e2 * e2);
    return sdouble(v, e);
  }
};

std::ostream &operator<<(std::ostream &stream, const sdouble &v) {
  sdouble v2 = v;
  v2.calculate();
  stream << v2.value << " +- " << v2.error;
  return stream;
}

} // namespace stat
