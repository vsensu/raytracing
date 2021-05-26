#ifndef MATH_COLOR_H_
#define MATH_COLOR_H_

#include <algorithm>
#include "vec.h"

using rgb_parent = vec3;
class rgb : public rgb_parent {
 public:
  rgb() : rgb_parent() {}
  rgb(const element_type& red,
      const element_type& green,
      const element_type& blue)
      : rgb_parent() {
    r(red);
    g(green);
    b(blue);
  }

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

  void r(const element_type& v) { x(std::clamp(v, 0.f, 1.f)); }
  void g(const element_type& v) { y(std::clamp(v, 0.f, 1.f)); }
  void b(const element_type& v) { z(std::clamp(v, 0.f, 1.f)); }
};

using rgba_parent = vec4;
class rgba : public rgba_parent {
 public:
  rgba() : rgba_parent() {}
  rgba(const element_type& red,
      const element_type& green,
      const element_type& blue,
      const element_type& alpha)
      : rgba_parent() {
    r(red);
    g(green);
    b(blue);
    a(alpha);
  }

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

  void r(const element_type& v) { x(std::clamp(v, 0.f, 1.f)); }
  void g(const element_type& v) { y(std::clamp(v, 0.f, 1.f)); }
  void b(const element_type& v) { z(std::clamp(v, 0.f, 1.f)); }
  void a(const element_type& v) { w(std::clamp(v, 0.f, 1.f)); }
};

using color = rgb;
using color4 = rgba;

#endif  // MATH_COLOR_H_