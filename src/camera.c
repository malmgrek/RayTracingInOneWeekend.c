#include "camera.h"

// Vfof: vertical field-of-view
camera_t Camera(vec3_t lookfrom,
                vec3_t lookat,
                vec3_t vup,
                double vfov,
                double aspect_ratio,
                double aperture,
                double focus_dist) {
  double theta = DEG2RAD(vfov);
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

void set_ray(ray_t *ray, const camera_t *cam, double s, double t) {

  vec3_t rand = random_in_unit_disk();
  double rd_x = cam->lens_radius * rand.x;
  double rd_y = cam->lens_radius * rand.y;
  // double rd_z = cam->lens_radius * rand.z;

  vec3_t temp1 = mul(rd_x, &cam->u);
  vec3_t temp2 = mul(rd_y, &cam->v);
  vec3_t offset = add(&temp1, &temp2);

  ray->origin = add(&cam->origin, &offset);

  // direction = lower_left_corner + s * horizontal + t * vertical
  // - origin - offset
  temp1 = mul(s, &cam->horizontal);
  temp1 = add(&cam->lower_left_corner, &temp1);
  temp2 = mul(t, &cam->vertical);
  temp2 = sub(&temp2, &cam->origin);
  temp2 = sub(&temp2, &offset);
  ray->direction = add(&temp1, &temp2);

}
