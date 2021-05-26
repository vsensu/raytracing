#ifndef MATH_VEC_H_
#define MATH_VEC_H_

#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <utility>

template <typename ElementType, int N>
class vec;

template <typename ElementType, int N>
class vec_base {
 public:
  using element_type = ElementType;

  vec_base() {}
  template <typename... Tail>
  vec_base(
      typename std::enable_if<sizeof...(Tail) + 1 == N, ElementType>::type head,
      Tail... tail)
      : elems_{head, ElementType(tail)...} {}

  auto operator-() const { return minus(std::make_index_sequence<N>{}); }
  ElementType operator[](std::size_t i) const { return elems_[i]; }
  ElementType& operator[](std::size_t i) { return elems_[i]; }

  friend std::ostream& operator<<(std::ostream& os, const vec_base& v) {
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

  vec_base& operator+=(const vec_base& v) {
    for (int i = 0; i < N; ++i) {
      elems_[i] += v.elems_[i];
    }
    return *this;
  }

  vec_base& operator-=(const vec_base& v) { return this->operator+=(-v); }

  vec_base& operator*=(double t) {
    for (int i = 0; i < N; ++i) {
      elems_[i] *= t;
    };
    return *this;
  }

  vec_base& operator/=(double t) { return this->operator*=(1 / t); }

  ElementType length() const { return std::sqrt(length_squared()); }

  ElementType length_squared() const {
    ElementType temp{};
    auto square = [&](const ElementType& e) { temp += e * e; };
    transform(square);
    return temp;
  }

 private:
  template <std::size_t... I>
  vec_base minus(std::index_sequence<I...>) const {
    return vec_base(-elems_[I]...);
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

template <typename ElementType, int N>
class vec : public vec_base<ElementType, N> {
 public:
  using vec_base<ElementType, N>::vec_base;
};

template <typename ElementType>
class vec<ElementType, 3> : public vec_base<ElementType, 3> {
 public:
  using vec_base<ElementType, 3>::vec_base;
  const ElementType x() const {
    return vec_base<ElementType, 3>::operator[](0);
  }
  const ElementType y() const {
    return vec_base<ElementType, 3>::operator[](1);
  }
  const ElementType z() const {
    return vec_base<ElementType, 3>::operator[](2);
  }

  const ElementType x() { return (static_cast<const vec*>(this))->x(); }
  const ElementType y() { return (static_cast<const vec*>(this))->y(); }
  const ElementType z() { return (static_cast<const vec*>(this))->z(); }

  void x(const ElementType& v) { vec_base<ElementType, 3>::operator[](0) = v; }
  void y(const ElementType& v) { vec_base<ElementType, 3>::operator[](1) = v; }
  void z(const ElementType& v) { vec_base<ElementType, 3>::operator[](2) = v; }
};

template <typename ElementType>
class vec<ElementType, 4> : public vec_base<ElementType, 4> {
 public:
  using vec_base<ElementType, 4>::vec_base;
  const ElementType x() const {
    return vec_base<ElementType, 4>::operator[](0);
  }
  const ElementType y() const {
    return vec_base<ElementType, 4>::operator[](1);
  }
  const ElementType z() const {
    return vec_base<ElementType, 4>::operator[](2);
  }
  const ElementType w() const {
    return vec_base<ElementType, 4>::operator[](3);
  }

  const ElementType x() { return (static_cast<const vec*>(this))->x(); }
  const ElementType y() { return (static_cast<const vec*>(this))->y(); }
  const ElementType z() { return (static_cast<const vec*>(this))->z(); }
  const ElementType w() { return (static_cast<const vec*>(this))->w(); }

  void x(const ElementType& v) { vec_base<ElementType, 4>::operator[](0) = v; }
  void y(const ElementType& v) { vec_base<ElementType, 4>::operator[](1) = v; }
  void z(const ElementType& v) { vec_base<ElementType, 4>::operator[](2) = v; }
  void w(const ElementType& v) { vec_base<ElementType, 4>::operator[](3) = v; }
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

using point3 = vec3;

template <typename ElementType, std::size_t... I>
auto vec_base_plus(const vec_base<ElementType, sizeof...(I)>& lhs,
                   const vec_base<ElementType, sizeof...(I)>& rhs,
                   std::index_sequence<I...>) {
  //   return vec_base(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
  return vec_base<ElementType, sizeof...(I)>((lhs[I] + rhs[I])...);
}

template <typename ElementType, int N>
inline const vec_base<ElementType, N> operator+(
    const vec_base<ElementType, N>& u,
    const vec_base<ElementType, N>& v) {
  return vec_base_plus(u, v, std::make_index_sequence<N>{});
}

template <typename ElementType, int N>
inline const vec_base<ElementType, N> operator-(
    const vec_base<ElementType, N>& u,
    const vec_base<ElementType, N>& v) {
  return vec_base_plus(u, -v, std::make_index_sequence<N>{});
}

template <typename ElementType, std::size_t... I>
auto vec_base_mul_vec(const vec_base<ElementType, sizeof...(I)>& lhs,
                      const vec_base<ElementType, sizeof...(I)>& rhs,
                      std::index_sequence<I...>) {
  return vec_base<ElementType, sizeof...(I)>((lhs[I] * rhs[I])...);
}

template <typename T, typename ElementType, std::size_t... I>
auto vec_base_mul_number(const T& t,
                         const vec_base<ElementType, sizeof...(I)>& v,
                         std::index_sequence<I...>) {
  return vec_base<ElementType, sizeof...(I)>((t * v[I])...);
}

template <typename T, typename ElementType, int N>
inline const vec_base<ElementType, N> operator*(
    const T& t,
    const vec_base<ElementType, N>& v) requires std::is_arithmetic_v<T> {
  // return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
  return vec_base_mul_number(t, v, std::make_index_sequence<N>{});
}

template <typename T, typename ElementType, int N>
inline const vec_base<ElementType, N> operator*(
    const vec_base<ElementType, N>& v,
    const T& t) requires std::is_arithmetic_v<T> {
  // return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
  return vec_base_mul_number(t, v, std::make_index_sequence<N>{});
}

template <typename ElementType, int N>
inline const vec_base<ElementType, N> operator*(
    const vec_base<ElementType, N>& u,
    const vec_base<ElementType, N>& v) {
  return vec_base_mul_vec(u, v, std::make_index_sequence<N>{});
}

#endif  // MATH_VEC_H_