#include <glm/glm.hpp>
#include <iostream>

#include "basic.h"
#include "ray.h"

vec3 ray_color(const ray& r) {
  vec3 unit_direction = glm::normalize(r.direction());
  auto t = 0.5f * (unit_direction.y + 1.0f);
  return (1.f - t) * color(1.f, 1.f, 1.f) + t * color(0.5f, 0.7f, 1.f);
}

void write_color(std::ostream& out, color pixel_color) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixel_color.x) << ' '
      << static_cast<int>(255.999 * pixel_color.y) << ' '
      << static_cast<int>(255.999 * pixel_color.z) << '\n';
}

int main() {
  // Image
  const auto aspect_ratio = 16.0f / 9.0f;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  auto viewport_height = 2.f;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.f;

  auto origin = vec3(0);
  auto horizontal = vec3(viewport_width, 0.f, 0.f);
  auto vertical = vec3(0.f, viewport_height, 0.f);
  auto lower_left_corner =
      origin - horizontal / 2.f - vertical / 2.f - vec3(0, 0, focal_length);

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = float(i) / (image_width - 1);
      auto v = float(j) / (image_height - 1);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
