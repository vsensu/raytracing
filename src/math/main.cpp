#include <iostream>
#include "color.h"
#include "vec.h"

int main() {
  color c(1.f, 2.f, 3.f);
  std::cout << c.x();
  return 0;
}
