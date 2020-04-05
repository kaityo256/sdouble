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
