#include "camera.h"

// Vfof: vertical field-of-view
camera_t Camera(vec3_t lookfrom,
                vec3_t lookat,
                vec3_t vup,
                double vfov,
                double aspect_ratio,
                double aperture,
                double focus_dist) {
  double theta = degrees_to_radians(vfov);
  double h = tan(theta / 2.0);
  double viewport_height = 2.0 * h;
  double viewport_width = aspect_ratio * viewport_height;

  vec3_t tmp;
  tmp.x = lookfrom.x - lookat.x;
  tmp.y = lookfrom.y - lookat.y;
  tmp.z = lookfrom.z - lookat.z;
  vec3_t w = unit_vector(&tmp);

  tmp = cross(vup, w);
  vec3_t u = unit_vector(&tmp);
  vec3_t v = cross(w, u);

  vec3_t origin = lookfrom;
  vec3_t horizontal = mul(focus_dist * viewport_width, u);
  vec3_t vertical = mul(focus_dist * viewport_height, v);
  vec3_t lower_left_corner = add(add(origin,
                                     mul(-0.5, horizontal)),
                                 add(mul(-0.5, vertical),
                                     mul(-1.0 * focus_dist, w)));

  // Instantiate camera_t type
  camera_t cam;
  cam.lower_left_corner = lower_left_corner;
  cam.horizontal = horizontal;
  cam.vertical = vertical;
  cam.origin = origin;
  cam.lens_radius = aperture / 2.0;
  cam.u = u;
  cam.v = v;
  cam.w = w;

  return cam;
}

void set_ray(ray_t *ray, camera_t *cam, double s, double t) {
  // TODO: Use only required cam attributes
  vec3_t rd = mul(cam->lens_radius, random_in_unit_disk());
  vec3_t offset = add(mul(rd.x, cam->u), mul(rd.y, cam->v));
  ray->origin = add(cam->origin, offset);
  // direction = lower_left_corner + s * horizontal + t * vertical - origin
  ray->direction = add(add(cam->lower_left_corner,
                           mul(s, cam->horizontal)),
                       add(mul(t, cam->vertical),
                           add(mul(-1.0, cam->origin),
                               mul(-1.0, offset))));
}
