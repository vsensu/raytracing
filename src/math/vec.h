#ifndef MATH_VEC_H_
#define MATH_VEC_H_

#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <utility>

template <typename ElementType, int N>
class vec {
 public:
  template <typename... Tail>
  vec(typename std::enable_if<sizeof...(Tail) + 1 == N, ElementType>::type head,
      Tail... tail)
      : elems_{head, ElementType(tail)...} {}

  auto operator-() const { return minus(std::make_index_sequence<N>{}); }
  ElementType operator[](int i) const { return elems_[i]; }
  ElementType& operator[](int i) { return elems_[i]; }

  friend std::ostream& operator<<(std::ostream& os, const vec& v) {
    // v.print(os, std::make_index_sequence<N>{});
    auto print_elem = [&](const ElementType& e) { os << e << ' '; };
    v.transform(print_elem);
    return os;
  }

  // template <std::size_t... I>
  // void print(std::ostream &os, std::index_sequence<I...>) const
  // {
  //     ((os << elems_[I] << ' '), ...);
  // }

  vec& operator+=(const vec& v) {
    for (int i = 0; i < N; ++i) {
      elems_[i] += v.elems_[i];
    }
    return *this;
  }

  vec& operator-=(const vec& v) { return this->operator+=(-v); }

  vec& operator*=(double t) {
    for (int i = 0; i < N; ++i) {
      elems_[i] *= t;
    };
    return *this;
  }

  vec& operator/=(double t) { return this->operator*=(1 / t); }

  ElementType length() const { return std::sqrt(length_squared()); }

  ElementType length_squared() const {
    ElementType temp{};
    auto square = [&](const ElementType& e) { temp += e * e; };
    transform(square);
    return temp;
  }

 private:
  template <std::size_t... I>
  vec minus(std::index_sequence<I...>) const {
    return vec(-elems_[I]...);
  }

  void transform(std::function<void(const ElementType&)> p) const {
    transform_inner(p, std::make_index_sequence<N>{});
  }

  template <std::size_t... I>
  void transform_inner(std::function<void(const ElementType&)> p,
                       std::index_sequence<I...>) const {
    ((p(elems_[I])), ...);
  }

  void transform(std::function<void(ElementType&)> p) {
    transform_inner(p, std::make_index_sequence<N>{});
  }

  template <std::size_t... I>
  void transform_inner(std::function<void(ElementType&)> p,
                       std::index_sequence<I...>) {
    ((p(elems_[I])), ...);
  }

 private:
  ElementType elems_[N]{0};
};

using vec2f = vec<float, 2>;
using vec3f = vec<float, 3>;
using vec4f = vec<float, 4>;
using vec2d = vec<double, 2>;
using vec3d = vec<double, 3>;
using vec4d = vec<double, 4>;

using vec2 = vec2f;
using vec3 = vec3f;
using vec4 = vec4f;

#endif  // MATH_VEC_H_