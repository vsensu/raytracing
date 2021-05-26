#ifndef MATH_COLOR_H_
#define MATH_COLOR_H_

#include "vec.h"

using rgb_parent = vec3;
class rgb : public rgb_parent {
 public:
  using rgb_parent::rgb_parent;

  // rgb limited in [0, 1], so make operator[] readonly
  const auto operator[](std::size_t i) const {
    return rgb_parent::operator[](i);
  }
  const auto operator[](std::size_t i) {
    return (static_cast<const rgb*>(this))->operator[](i);
  }

  const auto r() const { return x(); }
  const auto g() const { return y(); }
  const auto b() const { return z(); }

  const auto r() { return (static_cast<const rgb*>(this))->r(); }
  const auto g() { return (static_cast<const rgb*>(this))->g(); }
  const auto b() { return (static_cast<const rgb*>(this))->b(); }
};

using rgba_parent = vec4;
class rgba : public rgba_parent {
 public:
  using rgba_parent::rgba_parent;

  // rgb limited in [0, 1], so make operator[] readonly
  const auto operator[](std::size_t i) const {
    return rgba_parent::operator[](i);
  }
  const auto operator[](std::size_t i) {
    return (static_cast<const rgba*>(this))->operator[](i);
  }

  const auto r() const { return x(); }
  const auto g() const { return y(); }
  const auto b() const { return z(); }
  const auto a() const { return w(); }

  const auto r() { return (static_cast<const rgba*>(this))->r(); }
  const auto g() { return (static_cast<const rgba*>(this))->g(); }
  const auto b() { return (static_cast<const rgba*>(this))->b(); }
  const auto a() { return (static_cast<const rgba*>(this))->a(); }
};

using color = rgb;
using color4 = rgba;

#endif  // MATH_COLOR_H_