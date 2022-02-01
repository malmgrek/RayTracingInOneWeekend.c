#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

// TODO: Simplify vec3_t to 3-array of doubles

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

world_t *create_simple_scene() {

  world_t *world = malloc(sizeof(world_t) + 5 * sizeof(sphere_t));
  sphere_t *spheres = malloc(5 * sizeof(sphere_t));

  // Sphere center points
  vec3_t center;
  double xs[5] =    { 0.0,    0.0, -1.0, -1.0,  1.0 };
  double ys[5] =    { -1000.5, 0.0,  0.0,  0.0,  0.0 };
  double zs[5] =    { -1.0,  -1.0, -1.0, -1.0, -1.0 };
  double radii[5] = { 1000.0,  0.5,  0.5,  -0.4,  0.5 };

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
  world->num_spheres = 5;

  return world;

}

world_t *create_random_scene() {

  int n_spheres = 36 + 3;
  world_t *world = malloc(sizeof(world_t) +
                          (n_spheres+1) * sizeof(sphere_t));
  sphere_t *spheres = malloc((n_spheres+1) * sizeof(sphere_t));
  sphere_t sphere;
  material_t material;
  int class = 1;
  vec3_t albedo = { 0.5, 0.5, 0.5 };
  double fuzz = 0.0;
  double ir = 0.0;

  // Ground sphere
  material_t ground_material = Material(ir, fuzz, albedo, 1);
  vec3_t c = { 0.0, -1000.0, 0.0 };
  sphere_t ground = Sphere(c, 1000.0, ground_material);

  spheres[0] = ground;
  spheres[1] = Sphere(Vec(0.0, 1.0, 0.0),
                      1.0,
                      Material(1.5, 0.0, Vec(0.0, 0.0, 0.0), 3));
  spheres[2] = Sphere(Vec(-4.0, 1.0, 0.0),
                      1.0,
                      Material(0.0, 0.0, Vec(0.4, 0.2, 0.1), 1));
  spheres[3] = Sphere(Vec(4.0, 1.0, 0.0),
                      1.0,
                      Material(1.5, 0.0, Vec(0.7, 0.6, 0.5), 2));

  int n = 4;
  int c_max = sqrt(n_spheres - 3) / 2;
  for (int a = -c_max; a < c_max; a++) {
    for (int b = -c_max; b < c_max; b++) {
      double choose_mat = random_double_unit();
      vec3_t c = { a + 0.9 * random_double_unit(),
                   0.2,
                   b + 0.9 * random_double_unit() };
      vec3_t p = { 4.0, 0.2, 0.0 };
      if (norm(sub(c, p)) > 0.9) {
        if (choose_mat < 0.8) {
          // Diffuse
          class = 1;
          albedo = emul(random_vector_unit(),
                                random_vector_unit());
        } else if (choose_mat < 0.95) {
          // Metal
          class = 2;
          albedo = random_vector(0.5, 1.0);
          fuzz = random_double(0, 0.5);
        } else {
          // Glass
          class = 3;
          ir = 1.5;
        }
      }
      material = Material(ir, fuzz, albedo, class);
      sphere = Sphere(c, 0.2, material);
      spheres[n] = sphere;
      n++;
    }
  }

  world->spheres = spheres;
  world->num_spheres = n;

  return world;

}

void destroy_world(world_t *world) {
  free(world->spheres);
  free(world);
}

int main() {

  /* Initialize progress bar */
  char bar[13];

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) (image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  /* Camera */
  const vec3_t lookfrom = { 13.0, 2.0, 3.0 };
  const vec3_t lookat = { 0.0, 0.0, 0.0 };
  const vec3_t vup = { 0.0, 1.0, 0.0 };
  const double vfov = 20.0;
  const double aperture = 0.1;
  // double dist_to_focus = norm(sub(lookfrom, lookat));
  double dist_to_focus = 10.0;
  camera_t cam = Camera(lookfrom,
                        lookat,
                        vup,
                        vfov,
                        aspect_ratio,
                        aperture,
                        dist_to_focus);

  // NOTE: In C++ one can use shared pointers to wrap a list of hittable objects
  // (possible different ones) to a list that is looped over in the main loop.
  // In C, we can't do so. Instead, we create a list of structs beforehand, and
  // loop them explicitly.

  world_t *world = create_random_scene();

  /* Render */
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      /* Progress bar ------------------------------------------------------------ */
      progress_bar(bar, 1.0 - (double) j / image_height);
      /* ------------------------------------------------------------------------- */

      color_t pixel_color = { 0.0, 0.0, 0.0 };
      for (int q = 0; q < samples_per_pixel; ++q) {
        double s = (i + random_double_unit()) / (image_width - 1);
        double t = (j + random_double_unit()) / (image_height - 1);
        ray_t ray = get_ray(cam, s, t);
        pixel_color = add(pixel_color, ray_color(ray, *world, max_depth));
      }
      write_color(pixel_color, samples_per_pixel);

    }
  }

  destroy_world(world);

}
