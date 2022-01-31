#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

color_t ray_color(const ray_t ray, world_t world, int depth) {

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    return black;
  }

  hit_record_t rec = hit(ray, world);

  if (rec.count > 0) {
    color_t attenuation;
    ray_t scattered;
    if (scatter(ray, rec, &attenuation, &scattered)) {
      return emul(attenuation, ray_color(scattered, world, depth-1));
    }
    return black;
  }

  vec3_t unit = unit_vector(ray.direction);
  double t = 0.5 * (unit.y + 1.0);
  color_t color = add(mul(1.0 - t, white), mul(t, lightblue));
  return color;

}

void init_world(world_t *world, sphere_t *spheres) {

  // Sphere center points
  vec3_t center;
  double xs[5] =    { 0.0,    0.0, -1.0, -1.0,  1.0 };
  double ys[5] =    { -100.5, 0.0,  0.0,  0.0,  0.0 };
  double zs[5] =    { -1.0,  -1.0, -1.0, -1.0, -1.0 };
  double radii[5] = { 100.0,  0.5,  0.5,  -0.4,  0.5 };

  // Sphere materials
  material_t material;
  vec3_t albedo;
  double rs[5] = { 0.8, 0.1, 1.0, 1.0, 0.8 };
  double gs[5] = { 0.8, 0.2, 1.0, 1.0, 0.6 };
  double bs[5] = { 0.0, 0.5, 1.0, 1.0, 0.2 };
  double fuzzes[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
  double irs[5] = { 0.0, 0.0, 1.5, 1.5, 0.0 };
  int classes[5] = { 1, 1, 3, 3, 2 };

  for (int i = 0; i < 5; ++i) {

    center.x = xs[i];
    center.y = ys[i];
    center.z = zs[i];

    albedo.x = rs[i];
    albedo.y = gs[i];
    albedo.z = bs[i];
    material.albedo = albedo;
    material.class = classes[i];
    material.fuzz = fuzzes[i];
    material.index_of_refraction = irs[i];

    spheres[i].center = center;
    spheres[i].radius = radii[i];
    spheres[i].material = material;

  }

  world->spheres = spheres;

}

int main() {

  /* Initialize progress bar */
  char bar[13];

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) image_width / aspect_ratio;
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  /* Camera */
  camera_t cam = create_default_camera();

  // NOTE: In C++ one can use shared pointers to wrap a list of hittable objects
  // (possible different ones) to a list that is looped over in the main loop.
  // In C, we can't do so. Instead, we create a list of structs beforehand, and
  // loop them explicitly.

  world_t world;
  world.num_spheres = 5;
  sphere_t spheres[world.num_spheres];
  init_world(&world, spheres);

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
