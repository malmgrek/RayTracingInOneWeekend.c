#include "scene.h"

world_t *example_scene() {

  world_t *world = malloc(sizeof(world_t) + 4 * sizeof(sphere_t));
  sphere_t *spheres = malloc(4 * sizeof(sphere_t));

  spheres[0] = Sphere(Point(0.0, -1000.5, -1.0), 1000.0,
                      Material(0.0, 0.0, Color(0.3, 0.3, 0.3), 1));
  spheres[1] = Sphere(Point(2.0, 0.0, -2.0), 0.5,
                      Material(0.0, 0.0, Color(0.1, 0.2, 0.5), 2));
  spheres[2] = Sphere(Point(-1.0, 0.0, -0.3), 0.5,
                      Material(1.5, 0.0, Color(1.0, 1.0, 1.0), 3));
  // Uncomment to get a hollow glass sphere
  /* spheres[3] = Sphere(Point(-1.0, 0.0, -0.3), -0.4, */
  /*                     Material(1.5, 0.0, Color(1.0, 1.0, 1.0), 3)); */
  spheres[3] = Sphere(Point(1.0, 0.0, -1.0), 0.5,
                      Material(0.0, 0.0, Color(0.9, 0.9, 0.9), 1));

  world->spheres = spheres;
  world->num_spheres = 4;

  return world;

}

world_t *random_scene() {

  /* Random seed */
  srand( time(NULL) );

  int n_spheres = 121 + 3;
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
  vec3_t unit1;
  vec3_t unit2;
  for (int a = -c_max; a < c_max; a++) {
    for (int b = -c_max; b < c_max; b++) {
      double choose_mat = RANDOM_DOUBLE_UNIT;
      vec3_t c = Point(a + 0.9 * RANDOM_DOUBLE_UNIT,
                       0.2,
                       b + 0.9 * RANDOM_DOUBLE_UNIT);
      vec3_t p = Point(4.0, 0.2, 0.0);
      vec3_t r = sub(&c, &p);
      if (norm(&r) > 0.9) {
        if (choose_mat < 0.8) {
          // Diffuse
          unit1 = random_vector_unit();
          unit2 = random_vector_unit();
          material = Material(0.0, 0.0, emul(&unit1, &unit2), 1);
        } else if (choose_mat < 0.95) {
          // Metal
          material = Material(0.0, RANDOM_DOUBLE(0, 0.5),
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
