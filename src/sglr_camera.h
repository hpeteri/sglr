#ifndef SGLR_CAMERA_H
#define SGLR_CAMERA_H

#include "n1_cmath.h"

typedef struct sglr_Camera{
  int is_ortho;
  mat4 proj;
  
  vec3 pos;
  vec3 euler;
  

  quaternion rotation;

  float ne;
  float fa;
  
} sglr_Camera;

sglr_Camera sglr_make_camera();

void sglr_camera_set_ortho(sglr_Camera* camera, mat4 ortho);
void sglr_camera_set_perspective(sglr_Camera* camera, mat4 proj);

void sglr_camera_set_pos(sglr_Camera* camera, vec3 pos);
void sglr_camera_move(sglr_Camera* camera, vec3 delta);
void sglr_camera_set_euler(sglr_Camera* camera, vec3 euler);
void sglr_camera_set_rot(sglr_Camera* camera, quaternion q);

mat4 sglr_camera_matrix(sglr_Camera cam);
quaternion sglr_camera_rot(sglr_Camera cam);

#endif
