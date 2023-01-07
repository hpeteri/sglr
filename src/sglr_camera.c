#include "sglr_camera.h"

sglr_Camera sglr_make_camera(){
  sglr_Camera cam;
  N1_ZERO_MEMORY(&cam);

  cam.is_ortho = 0;
  cam.proj = mat4_make_identity();
  cam.rotation = quat_make_identity();
  
  return cam;
}

void sglr_camera_set_ortho(sglr_Camera* camera, mat4 ortho){
  camera->proj = ortho;
  camera->is_ortho = 1;
}

void sglr_camera_set_perspective(sglr_Camera* camera, mat4 proj){
  camera->proj = proj;
  camera->is_ortho = 0;
}

void sglr_camera_set_pos(sglr_Camera* camera, vec3 pos){
  camera->pos = pos;
}

void sglr_camera_move(sglr_Camera* camera, vec3 delta){
  camera->pos = vec3_addv(camera->pos, delta);
}

void sglr_camera_set_euler(sglr_Camera* camera, vec3 euler){
  camera->euler = euler;
  camera->rotation = quat_make_yaw_pitch_roll(euler.y, euler.x, -euler.z);
}

void sglr_camera_set_rot(sglr_Camera* camera, quaternion q){
  camera->rotation = q;
}

mat4 sglr_camera_matrix(sglr_Camera cam){
  mat4 view = mat4_rts(quat_inverse(cam.rotation),
                       vec3_negate(cam.pos),
                       vec3_make(1,1,1));
  
  return mat4_mulm(cam.proj, view);
}

quaternion sglr_camera_rot(sglr_Camera cam){
  //we should cache this
  return quat_make_yaw_pitch_roll(cam.euler.y, cam.euler.x, cam.euler.z);
}
