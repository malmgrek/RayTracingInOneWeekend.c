#include <string.h>

#include "camera.h"
#include "color.h"
#include "ray.h"
#include "scatter.h"
#include "scene.h"
#include "utils.h"
#include "vec3.h"

#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH 400
#define IMAGE_HEIGHT (int) (IMAGE_WIDTH / ASPECT_RATIO)
#define SAMPLES_PER_PIXEL 4
#define MAX_DEPTH 50
#define VFOV 20.0
#define APERTURE 0.1

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

  /* Camera */
  const vec3_t lookfrom = { 13.0, 2.0, 3.0 };
  const vec3_t lookat = { 0.0, 0.0, 0.0 };
  const vec3_t vup = { 0.0, 1.0, 0.0 };
  // One option: dist_to_focus = |lookfrom - lookat|;
  double dist_to_focus = 10.0;
  camera_t cam = Camera(lookfrom,
                        lookat,
                        vup,
                        VFOV,
                        ASPECT_RATIO,
                        APERTURE,
                        dist_to_focus);

  // Initialize loop variables
  world_t *world = example_scene();
  hit_record_t rec;
  ray_t ray;
  color_t pixel_color;
  color_t acc_pixel_color;
  double s;
  double t;

  /* Render */
  printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
  for (int j = IMAGE_HEIGHT-1; j >= 0; --j) {

    if (show_progress_bar) {
      progress_bar(1.0 - (double) j / IMAGE_HEIGHT);
    }

    for (int i = 0; i < IMAGE_WIDTH; ++i) {

      // Start from black pixel
      acc_pixel_color.x = 0.0;
      acc_pixel_color.y = 0.0;
      acc_pixel_color.z = 0.0;

      for (int q = 0; q < SAMPLES_PER_PIXEL; ++q) {

        s = (i + RANDOM_DOUBLE_UNIT) / (IMAGE_WIDTH - 1);
        t = (j + RANDOM_DOUBLE_UNIT) / (IMAGE_HEIGHT - 1);
        set_ray(&ray, &cam, s, t);
        pixel_color = ray_color(&rec, &ray, world, MAX_DEPTH);
        acc_pixel_color = add(&acc_pixel_color, &pixel_color);

      }

      write_color(&acc_pixel_color, SAMPLES_PER_PIXEL);

    }

  }

  destroy_world(world);

}
