#include "scene.h"

world_t *example_scene() {

  world_t *world = malloc(sizeof(world_t) + 5 * sizeof(sphere_t));
  sphere_t *spheres = malloc(5 * sizeof(sphere_t));

  spheres[0] = Sphere(Point(0.0, -1000.5, -1.0), 1000.0,
                      Material(0.0, 0.0, Color(0.8, 0.8, 0.0), 2));
  spheres[1] = Sphere(Point(0.0, 0.0, -1.0), 0.5,
                      Material(0.0, 0.0, Color(0.1, 0.2, 0.5), 2));
  spheres[2] = Sphere(Point(-1.0, 0.0, -1.0), 0.5,
                      Material(1.5, 0.0, Color(1.0, 1.0, 1.0), 2));
  spheres[3] = Sphere(Point(-1.0, 0.0, -1.0), -0.4,
                      Material(1.5, 0.0, Color(1.0, 1.0, 1.0), 2));
  spheres[4] = Sphere(Point(1.0, 0.0, -1.0), 0.5,
                      Material(0.0, 0.0, Color(0.8, 0.6, 0.2), 2));

  world->spheres = spheres;
  world->num_spheres = 5;

  return world;

}

world_t *random_scene() {

  int n_spheres = 36 + 3;
  world_t *world = malloc(sizeof(world_t) +
                          (n_spheres+1) * sizeof(sphere_t));
  sphere_t *spheres = malloc((n_spheres+1) * sizeof(sphere_t));
  material_t material = Material(1.5, 0.0, Color(0.5, 0.5, 0.5), 1);
  sphere_t ground = Sphere(Point(0.0, -1000.0, 0.0), 1000.0, material);

  spheres[0] = ground;
  spheres[1] = Sphere(Point(0.0, 1.0, 0.0), 1.0,
                      Material(1.5, 0.0, Color(0.0, 0.0, 0.0), 3));
  spheres[2] = Sphere(Point(-4.0, 1.0, 0.0), 1.0,
                      Material(0.0, 0.0, Color(0.4, 0.2, 0.1), 1));
  spheres[3] = Sphere(Point(4.0, 1.0, 0.0), 1.0,
                      Material(1.5, 0.0, Color(0.7, 0.6, 0.5), 2));

  int n = 4;
  int c_max = sqrt(n_spheres - 3) / 2;
  for (int a = -c_max; a < c_max; a++) {
    for (int b = -c_max; b < c_max; b++) {
      double choose_mat = random_double_unit();
      vec3_t c = Point(a + 0.9 * random_double_unit(),
                       0.2,
                       b + 0.9 * random_double_unit());
      vec3_t p = Point(4.0, 0.2, 0.0);
      if (norm(sub(c, p)) > 0.9) {
        if (choose_mat < 0.8) {
          // Diffuse
          material = Material(0.0, 0.0, emul(random_vector_unit(),
                                             random_vector_unit()), 1);
        } else if (choose_mat < 0.95) {
          // Metal
          material = Material(0.0, random_double(0, 0.5),
                              random_vector(0.5, 1.0), 2);
        } else {
          // Glass
          material = Material(1.5, 0.0, Color(1.0, 1.0, 1.0), 3);
        }
      }
      spheres[n] = Sphere(c, 0.2, material);
      n++;
    }
  }

  world->spheres = spheres;
  world->num_spheres = n;

  return world;

}
