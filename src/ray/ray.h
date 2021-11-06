#pragma once

#include "basic.h"

class ray {
 public:
  ray() {}
  ray(const vec3& origin, const vec3& direction)
      : origin_(origin), direction_(direction) {}

  vec3 origin() const { return origin_; }
  vec3 direction() const { return direction_; }

  vec3 at(float t) const { return origin_ + t * direction_; }

 private:
  vec3 origin_;
  vec3 direction_;
};