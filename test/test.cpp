#include "../sdouble.hpp"
#include <iostream>
#include <random>

std::mt19937 mt(1);
std::normal_distribution<> nd1(100.0, 3.0);
std::normal_distribution<> nd2(50.0, 1.0);
const int loop = 1000000;

void test_without_uncertainty_compound() {
  std::cout << "Test for compound operators" << std::endl;
  stat::sdouble x(10.0, 1.0), y;
  std::cout << "x = " << x << std::endl;
  y = x;
  y += 1.0;
  std::cout << "(x += 1.0) " << y << std::endl;
  y = x;
  y -= 1.0;
  std::cout << "(x -= 1.0) " << y << std::endl;
  y = x;
  y *= 2.0;
  std::cout << "(x *= 2.0) " << y << std::endl;
  y = x;
  y /= 2.0;
  std::cout << "(x /= 2.0) " << y << std::endl;
  std::cout << std::endl;
}
void test_binary_operators() {
  std::cout << "Test for binary operators" << std::endl;
  stat::sdouble x(100.0, 3.0);
  stat::sdouble y(50.0, 1.0);
  stat::sdouble z;

  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;
  std::cout << "(x + y) " << x + y << std::endl;
  std::cout << "(x - y) " << x - y << std::endl;
  std::cout << "(x * y) " << x * y << std::endl;
  std::cout << "(x / y) " << x / y << std::endl;
  std::cout << std::endl;
}

void test() {
  stat::sdouble v;
  for (int i = 0; i < 1000; i++) {
    v << nd1(mt);
  }
  std::cout << "Mean and standard deviation" << std::endl;
  std::cout << v.mean() << " +- " << v.stddev() << std::endl;
  std::cout << "Mean and standard deviation of the mean" << std::endl;
  std::cout << v << std::endl;
  std::cout << std::endl;
}

void add_test() {
  std::cout << "Add Test" << std::endl;
  stat::sdouble d1, d2, d3;
  for (int i = 0; i < loop; i++) {
    double v1 = nd1(mt);
    double v2 = nd2(mt);
    d1 << v1;
    d2 << v2;
    d3 << (v1 + v2);
  }
  stat::sdouble d4 = d1 + d2;
  std::cout << "d1    = " << d1 << std::endl;
  std::cout << "d2    = " << d2 << std::endl;
  std::cout << "d1+d2 = " << d3 << std::endl;
  std::cout << "d1+d2 = " << d4 << std::endl;
  std::cout << std::endl;
}

void sub_test() {
  std::cout << "Subtraction Test" << std::endl;
  stat::sdouble d1, d2, d3;
  for (int i = 0; i < loop; i++) {
    double v1 = nd1(mt);
    double v2 = nd2(mt);
    d1 << v1;
    d2 << v2;
    d3 << (v1 - v2);
  }
  stat::sdouble d4 = d1 - d2;
  std::cout << "d1    = " << d1 << std::endl;
  std::cout << "d2    = " << d2 << std::endl;
  std::cout << "d1-d2 = " << d3 << std::endl;
  std::cout << "d1-d2 = " << d4 << std::endl;
  std::cout << std::endl;
}

void mul_test() {
  std::cout << "Multiplication Test" << std::endl;
  stat::sdouble d1, d2, d3;
  for (int i = 0; i < loop; i++) {
    double v1 = nd1(mt);
    double v2 = nd2(mt);
    d1 << v1;
    d2 << v2;
    d3 << (v1 * v2);
  }
  stat::sdouble d4 = d1 * d2;
  std::cout << "d1    = " << d1 << std::endl;
  std::cout << "d2    = " << d2 << std::endl;
  std::cout << "d1*d2 = " << d3 << std::endl;
  std::cout << "d1*d2 = " << d4 << std::endl;
  std::cout << std::endl;
}

void div_test() {
  std::cout << "Division Test" << std::endl;
  stat::sdouble d1, d2, d3;
  for (int i = 0; i < loop; i++) {
    double v1 = nd1(mt);
    double v2 = nd2(mt);
    d1 << v1;
    d2 << v2;
    d3 << (v1 / v2);
  }
  stat::sdouble d4 = d1 / d2;
  std::cout << "d1    = " << d1 << std::endl;
  std::cout << "d2    = " << d2 << std::endl;
  std::cout << "d1/d2 = " << d3 << std::endl;
  std::cout << "d1/d2 = " << d4 << std::endl;
  std::cout << std::endl;
}

int main() {
  test_without_uncertainty_compound();
  test_binary_operators();
  std::cout << "Test for standard deviation" << std::endl;
  std::cout << "----------------" << std::endl;
  test();
  std::cout << "Tests for error propagation" << std::endl;
  std::cout << "----------------" << std::endl;
  add_test();
  sub_test();
  mul_test();
  div_test();
}
