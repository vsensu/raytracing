#include <iostream>
#include "vec.h"

int main() {
  vec3 f(1, 2, 3);
  std::cout << f << '\n';
  vec3 f2 = -f;
  std::cout << f2 << '\n';
  f += f2;
  std::cout << f << '\n';
  f -= f2;
  std::cout << f << '\n';
  f *= 3;
  std::cout << f << '\n';
  f /= 3;
  std::cout << f << '\n';
  std::cout << f.length() << '\n';
  std::cout << f.length_squared() << '\n';
  return 0;
}
