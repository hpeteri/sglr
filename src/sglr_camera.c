#include "sglr_camera.h"

sglr_Camera sglr_make_camera(){
  sglr_Camera cam;
  N1_ZERO_MEMORY(&cam);

  cam.is_ortho   = 0;
  cam.projection = mat4_make_identity();
  cam.rotation   = quat_make_identity();
  
  return cam;
}

void sglr_camera_set_ortho_rh(sglr_Camera* camera, float left, float right, float top, float bottom, float ne, float fa){

  const mat4 ortho = mat4_ortho_rh(left, right, top, bottom, ne, fa);

  camera->is_ortho = 1;
  camera->projection = ortho;
  camera->fa = fa;
  camera->ne = ne;

}

void sglr_camera_set_perspective_rh(sglr_Camera* camera, float fov, float aspect, float ne, float fa){
  
  const mat4 perspective = mat4_perspective_rh(fov, aspect, ne, fa);

  camera->is_ortho        = 0;
  camera->aspect          = aspect;
  camera->projection      = perspective;
  camera->perspective.fov = fov;
  camera->fa             = fa;
  camera->ne            = ne;

  vec3 forward = quat_mulv(camera->rotation, vec3_make(0, 0, -1));
  
  const float half_vertical   = fa * tanf(fov * .5f);
  const float half_horizontal = half_vertical * aspect;
  const vec3  front_mult_fa  = vec3_mulv(forward, vec3_make1(fa));
  
#if 0
  frustum.neFace = { cam.Position + zNe * cam.Front, cam.Front };
  frustum.faFace = { cam.Position + frontMultFa, -cam.Front };
  frustum.rightFace = { cam.Position,
    glm::cross(cam.Up,frontMultFa + cam.Right * halfHSide) };
  frustum.leftFace = { cam.Position,
    glm::cross(frontMultFa - cam.Right * halfHSide, cam.Up) };
  frustum.topFace = { cam.Position,
    glm::cross(cam.Right, frontMultFa - cam.Up * halfVSide) };
  frustum.bottomFace = { cam.Position,
    glm::cross(frontMultFa + cam.Up * halfVSide, cam.Right) };
#endif
}

void sglr_camera_update_frustrum_aabb(sglr_Camera* camera){
  
  float height = tan(camera->perspective.fov / camera->aspect / 180 * PI / 2) * camera->fa;
  float width = tan(camera->perspective.fov / 180 * PI / 2) * camera->fa;
  // === fa ====
  vec3 f_tl = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(-width, height, -camera->fa)));
  vec3 f_tr = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(width, height, -camera->fa)));
  vec3 f_bl = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(-width, -height, -camera->fa)));
  vec3 f_br = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(width, -height, -camera->fa)));

  height = tan(camera->perspective.fov / camera->aspect / 180 * PI / 2) * camera->ne;
  width = tan(camera->perspective.fov / 180 * PI / 2) * camera->ne;
        
  vec3 n_tl = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(-width, height, -camera->ne)));
  vec3 n_tr = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(width, height, -camera->ne)));
  vec3 n_bl = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(-width, -height, -camera->ne)));
  vec3 n_br = vec3_addv(camera->pos, quat_mulv(camera->rotation, vec3_make(width, -height, -camera->ne)));

  camera->perspective.aabb.min = n_bl;
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_br);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_tl);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_tr);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_bl);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_br);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_tl);
  camera->perspective.aabb.min = vec3_minv(camera->perspective.aabb.min, f_tr);

  camera->perspective.aabb.max = n_bl;
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_br);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_tl);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_tr);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_bl);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_br);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_tl);
  camera->perspective.aabb.max = vec3_maxv(camera->perspective.aabb.max, f_tr);
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
  
  return mat4_mulm(cam.projection, view);
}

quaternion sglr_camera_rot(sglr_Camera cam){
  //we should cache this
  return quat_make_yaw_pitch_roll(cam.euler.y, cam.euler.x, cam.euler.z);
}
