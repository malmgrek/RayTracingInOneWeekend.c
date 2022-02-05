#include <string.h>

#include "camera.h"
#include "color.h"
#include "ray.h"
#include "scatter.h"
#include "scene.h"
#include "utils.h"
#include "vec3.h"

// TODO: Refactor to reasonable modules
// TODO: Makefile
// TODO: Readme
// TODO: GitHub

color_t ray_color(hit_record_t *rec, ray_t *ray, world_t *world, int depth) {

  color_t color = { 0.0, 0.0, 0.0 };

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    return color;
  }

  hit(rec, ray, world);

  if (rec->count > 0) {
    color_t attenuation;
    ray_t scattered;
    if (scatter(ray, rec, &attenuation, &scattered)) {
      color = ray_color(rec, &scattered, world, depth-1);
      color.x *= attenuation.x;
      color.y *= attenuation.y;
      color.z *= attenuation.z;
      return color;
    }
    return color;
  }

  double unit_y = ray->direction.y / norm(&ray->direction);
  double t = 0.5 * (unit_y + 1.0);

  color.x = (1.0 - t) * 1.0 + t * 0.5;
  color.y = (1.0 - t) * 1.0 + t * 0.7;
  color.z = (1.0 - t) * 1.0 + t * 1.0;

  return color;

}

int main(int argc, char *argv[]) {

  bool show_progress_bar = false;
  if (argc > 1) {
    if (strcmp(argv[1], "--bar") == 0) {
      show_progress_bar = true;
    }
  }

  /* Image */
  const double aspect_ratio = 3.0 / 2.0;
  const int image_width = 400;
  const int image_height = (int) (image_width / aspect_ratio);
  const int samples_per_pixel = 4;
  const int max_depth = 50;

  /* Camera */
  const vec3_t lookfrom = { 13.0, 2.0, 3.0 };
  const vec3_t lookat = { 0.0, 0.0, 0.0 };
  const vec3_t vup = { 0.0, 1.0, 0.0 };
  const double vfov = 20.0;
  const double aperture = 0.1;
  // One option: dist_to_focus = |lookfrom - lookat|;
  double dist_to_focus = 10.0;
  camera_t cam = Camera(lookfrom,
                        lookat,
                        vup,
                        vfov,
                        aspect_ratio,
                        aperture,
                        dist_to_focus);

  // Initialize loop variables
  world_t *world = example_scene();
  hit_record_t rec;
  ray_t ray;
  color_t pixel_color;
  color_t added_pixel_color;
  double s;
  double t;

  /* Render */
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {

    if (show_progress_bar) {
      progress_bar(1.0 - (double) j / image_height);
    }

    for (int i = 0; i < image_width; ++i) {

      // Start from black pixel
      pixel_color.x = 0.0;
      pixel_color.y = 0.0;
      pixel_color.z = 0.0;

      for (int q = 0; q < samples_per_pixel; ++q) {

        s = (i + random_double_unit()) / (image_width - 1);
        t = (j + random_double_unit()) / (image_height - 1);
        set_ray(&ray, &cam, s, t);
        added_pixel_color = ray_color(&rec, &ray, world, max_depth);
        pixel_color.x += added_pixel_color.x;
        pixel_color.y += added_pixel_color.y;
        pixel_color.z += added_pixel_color.z;

      }

      write_color(&pixel_color, samples_per_pixel);

    }

  }

  destroy_world(world);

}
