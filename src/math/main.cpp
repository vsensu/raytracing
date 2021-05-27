#include <iostream>
#include "color.h"
#include "vec.h"

int main() {
  vec3 a(1.f, 1.f, 1.f);
  vec3 b(1.f, 2.f, 3.f);
  std::cout << a + b << '\n';
  std::cout << a - b << '\n';
  std::cout << a * b << '\n';
  std::cout << 3 * a << '\n';
  std::cout << a * 4.f << '\n';
  std::cout << a / 3 << '\n';
  std::cout << dot(a, b) << '\n';
  std::cout << cross(a, b) << '\n';
  return 0;
}
