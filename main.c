#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

/* Initialize progress bar */
char bar[13];

const color_t white = { 1.0, 1.0, 1.0 };
const color_t lightblue = { 0.5, 0.7, 1.0 };

color_t ray_color(const ray_t ray, world_t world, int depth) {

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    color_t color = { 0.0, 0.0, 0.0 };
    return color;
  }

  hit_record_t rec = hit(ray, world);

  if (rec.count > 0) {
    vec3_t target = add(add(rec.p, rec.normal),
                        random_on_unit_sphere());
    ray_t ray_new;
    ray_new.origin = rec.p;
    ray_new.direction = sub(target, rec.p);
    return mul(0.5, ray_color(ray_new, world, depth-1));
  }
  vec3_t unit = unit_vector(ray.direction);
  double t = 0.5 * (unit.y + 1.0);
  color_t color = add(mul(1.0 - t, white), mul(t, lightblue));
  return color;
}

int main() {

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) image_width / aspect_ratio;
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  /* Camera */
  camera_t cam = create_default_camera();

  // NOTE: In C++ one can use shared pointers to wrap a list of
  // hittable objects (possible different) to a list that is looped over
  // in the main loop. In C, we can't do so. Instead, we create a list
  // of structs beforehand, and loop them explicitly.

  sphere_t spheres[2];
  vec3_t center0 = { 0.0, 0.0, -1.0 };
  spheres[0].center = center0;
  spheres[0].radius = 0.5;
  vec3_t center1 = { 0.0, -100.5, -1.0 };
  spheres[1].center = center1;
  spheres[1].radius = 100.0;
  world_t world;
  world.spheres = spheres;
  world.num_spheres = 2;

  /* Render */
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      /* Progress bar ------------------------------------------------------------ */
      progress_bar(bar, 1.0 - (double) j / image_height);
      /* ------------------------------------------------------------------------- */

      color_t pixel_color = { 0.0, 0.0, 0.0 };
      for (int s = 0; s < samples_per_pixel; ++s) {
        double u = (i + random_double_unit()) / (image_width - 1);
        double v = (j + random_double_unit()) / (image_height - 1);
        ray_t ray = get_ray(cam, u, v);
        pixel_color = add(pixel_color, ray_color(ray, world, max_depth));
      }
      write_color(pixel_color, samples_per_pixel);

    }
  }

}
