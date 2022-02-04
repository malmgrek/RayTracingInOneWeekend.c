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

  vec3_t tmp = sub(&lookfrom, &lookat);
  vec3_t w = unit_vector(&tmp);

  tmp = cross(&vup, &w);
  vec3_t u = unit_vector(&tmp);
  vec3_t v = cross(&w, &u);

  vec3_t origin = lookfrom;
  vec3_t horz = mul(focus_dist * viewport_width, &u);
  vec3_t vert = mul(focus_dist * viewport_height, &v);

  vec3_t lower_left_corner;
  lower_left_corner.x = origin.x - horz.x/2.0 - vert.x/2.0 - focus_dist*w.x;
  lower_left_corner.y = origin.y - horz.y/2.0 - vert.y/2.0 - focus_dist*w.y;
  lower_left_corner.z = origin.z - horz.z/2.0 - vert.z/2.0 - focus_dist*w.z;

  // Instantiate camera_t type
  camera_t cam;
  cam.lower_left_corner = lower_left_corner;
  cam.horizontal = horz;
  cam.vertical = vert;
  cam.origin = origin;
  cam.lens_radius = aperture/2.0;
  cam.u = u;
  cam.v = v;
  cam.w = w;

  return cam;
}

void set_ray(ray_t *ray, camera_t *cam, double s, double t) {
  // TODO: Use only required cam attributes
  vec3_t rand = random_in_unit_disk();
  vec3_t rd;
  rd.x = cam->lens_radius * rand.x;
  rd.y = cam->lens_radius * rand.y;
  rd.z = cam->lens_radius * rand.z;

  vec3_t offset;
  offset.x = rd.x * cam->u.x + rd.y * cam->v.x;
  offset.y = rd.x * cam->u.y + rd.y * cam->v.y;
  offset.z = rd.x * cam->u.z + rd.y * cam->v.z;

  ray->origin.x = cam->origin.x + offset.x;
  ray->origin.y = cam->origin.y + offset.y;
  ray->origin.z = cam->origin.z + offset.z;

  // direction = lower_left_corner + s * horizontal + t * vertical - origin - offset
  ray->direction.x = cam->lower_left_corner.x + s * cam->horizontal.x +
    t * cam->vertical.x - cam->origin.x - offset.x;
  ray->direction.y = cam->lower_left_corner.y + s * cam->horizontal.y +
    t * cam->vertical.y - cam->origin.y - offset.y;
  ray->direction.z = cam->lower_left_corner.z + s * cam->horizontal.z +
    t * cam->vertical.z - cam->origin.z - offset.z;
}
