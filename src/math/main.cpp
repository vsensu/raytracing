#include <iostream>
#include "color.h"
#include "vec.h"

int main() {
  color c(1.f, 2.f, 3.f);
  std::cout << c << '\n';
  color4 a(2.f, 3.f, 4.f, 5.f);
  std::cout << a << '\n';
  return 0;
}
