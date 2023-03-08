#ifndef SGLR_CAMERA_H
#define SGLR_CAMERA_H

#include "cmath/n1_cmath.h"

typedef struct sglr_FrustumPlane{
  vec3  normal;
  float distance;
} sglr_FrustrumPlane;

typedef struct sglr_Camera{
  int  is_ortho;
  //mat4 proj;

  mat4 projection; 
  //mat4 view;       // position
  
  vec3 pos;
  vec3 euler;
  quaternion rotation;

  //msvc reserves near and far :)
  float ne;
  float fa;

  float aspect;
  
  struct {
    float fov;
    sglr_FrustrumPlane frustrum[6];    

    struct{
      vec3 min;
      vec3 max;
    } aabb;

  } perspective;

  struct {
    vec3 frustrum_min;
    vec3 frustrum_max;
  } ortho;
  
} sglr_Camera;

sglr_Camera sglr_make_camera();

//void sglr_camera_set_ortho(sglr_Camera* camera, mat4 ortho);
//void sglr_camera_set_perspective(sglr_Camera* camera, mat4 proj);
void sglr_camera_set_ortho_rh(sglr_Camera* camera, float left, float right, float top, float bottom, float near, float far);

void sglr_camera_set_perspective_rh(sglr_Camera* camera, float fov, float aspect, float ne, float fa);

void sglr_camera_update_frustrum_aabb(sglr_Camera* camera);

void sglr_camera_set_pos(sglr_Camera* camera, vec3 pos);
void sglr_camera_move(sglr_Camera* camera, vec3 delta);
void sglr_camera_set_euler(sglr_Camera* camera, vec3 euler);
void sglr_camera_set_rot(sglr_Camera* camera, quaternion q);

mat4 sglr_camera_matrix(sglr_Camera cam);
quaternion sglr_camera_rot(sglr_Camera cam);

#endif
