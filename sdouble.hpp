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

  sdouble(double value, double error)
      : value(value), error(error), isCalculated(true) {
  }

  sdouble(const sdouble &obj)
      : value(0.0), error(0.0), isCalculated(true) {
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
    return error * sqrt(x.size());
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
    isCalculated = false;
  }

  // Alias of add
  void operator<<(double v) {
    add(v);
  }

  /*
    Error Propagation
  */
  sdouble operator+=(const sdouble &rhs) {
    sdouble y(rhs);
    calculate();
    y.calculate();
    value = value + y.value;
    error = sqrt(error * error + y.error * y.error);
    return *this;
  }

  sdouble operator+(const sdouble &rhs) const {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    x += y;
    return sdouble(x);
  }

  sdouble operator-=(const sdouble &rhs) {
    sdouble y(rhs);
    calculate();
    y.calculate();
    value = value - y.value;
    error = sqrt(error * error + y.error * y.error);
    return *this;
  }

  sdouble operator-(const sdouble &rhs) const {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    x -= y;
    return sdouble(x);
  }

  sdouble operator*=(const sdouble &rhs) {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    value = x.value * y.value;
    double e1 = x.error * y.value;
    double e2 = y.error * x.value;
    error = sqrt(e1 * e1 + e2 * e2);
    return *this;
  }

  sdouble operator*(const sdouble &rhs) const {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    x *= y;
    return sdouble(x);
  }

  sdouble operator/=(const sdouble &rhs) {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    value = x.value / y.value;
    double e1 = x.error / x.value;
    double e2 = y.error / y.value;
    error = value * sqrt(e1 * e1 + e2 * e2);
    return sdouble(*this);
  }

  sdouble operator/(const sdouble &rhs) const {
    sdouble x(*this);
    sdouble y(rhs);
    x.calculate();
    y.calculate();
    x /= y;
    return sdouble(x);
  }

  /*
    Calculation without uncertainty
  */
  sdouble &operator+=(const double v) {
    operator+=(sdouble(v, 0.0));
    return *this;
  }

  sdouble &operator-=(const double v) {
    operator-=(sdouble(v, 0.0));
    return *this;
  }

  sdouble &operator*=(const double v) {
    operator*=(sdouble(v, 0.0));
    return *this;
  }

  sdouble &operator/=(const double v) {
    operator/=(sdouble(v, 0.0));
    return *this;
  }
};

std::ostream &operator<<(std::ostream &stream, const sdouble &v) {
  sdouble v2 = v;
  v2.calculate();
  stream << v2.value << " +- " << v2.error;
  return stream;
}

} // namespace stat

stat::sdouble operator+(const stat::sdouble &obj, double v) {
  stat::sdouble x = obj;
  //x.calculate();
  x += v;
  return stat::sdouble(x);
}

stat::sdouble operator+(double v, const stat::sdouble &obj) {
  return operator+(obj, v);
}

stat::sdouble operator-(const stat::sdouble &obj, double v) {
  stat::sdouble x = obj;
  x.calculate();
  x -= v;
  return stat::sdouble(x);
}

stat::sdouble operator-(double v, const stat::sdouble &obj) {
  stat::sdouble x = obj;
  x.calculate();
  return stat::sdouble(v - x.value, x.error);
}

stat::sdouble operator*(const stat::sdouble &obj, double v) {
  stat::sdouble x = obj;
  x.calculate();
  x *= v;
  return stat::sdouble(x);
}

stat::sdouble operator*(double v, const stat::sdouble &obj) {
  return operator*(obj, v);
}

stat::sdouble operator/(const stat::sdouble &obj, double v) {
  stat::sdouble x = obj;
  x.calculate();
  x /= v;
  return stat::sdouble(x);
}

stat::sdouble operator/(double v, const stat::sdouble &obj) {
  stat::sdouble x = obj;
  x.calculate();
  double e = x.error / x.value;
  x.value = v / x.value;
  x.error = x.value * e;
  return stat::sdouble(x);
}
