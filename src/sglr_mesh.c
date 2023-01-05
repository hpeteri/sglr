#include "sglr_mesh.h"

sglr_Mesh sglr_make_mesh(uint32_t               vertex_count,
                         const float const*     positions,
                         const float const*     tc,
                         const float const*     norm,
                         uint32_t               index_count,
                         const uint32_t const* indices){
  sglr_Mesh mesh;
  N1_ZERO_MEMORY(&mesh);

  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  mesh.vertex_count = vertex_count;
  mesh.index_count  = index_count;

  // pos
  mesh.pos = (float*)allocator.alloc(sizeof(float) * 3 * vertex_count);
  memcpy(mesh.pos, positions, sizeof(float) * 3 * vertex_count);
  mesh.buffer_pos = sglr_make_buffer_vertex(sizeof(float) * 3 * vertex_count, mesh.pos);
  

  // tc
  mesh.tc = (float*)allocator.alloc(sizeof(float) * 3 * vertex_count);
  memcpy(mesh.tc, tc, sizeof(float) * 3 * vertex_count);
  mesh.buffer_tc = sglr_make_buffer_vertex(sizeof(float) * 3 * vertex_count, mesh.tc);

  // norm
  mesh.norm = (float*)allocator.alloc(sizeof(float) * 3 * vertex_count);
  memcpy(mesh.norm, norm, sizeof(float) * 3 * vertex_count);
  mesh.buffer_norm = sglr_make_buffer_vertex(sizeof(float) * 3 * vertex_count, mesh.norm);

  
  // idx
  mesh.indices = (uint32_t*)allocator.alloc(sizeof(uint32_t) * index_count);
  memcpy(mesh.indices, indices, sizeof(uint32_t)  * index_count);
  mesh.buffer_idx = sglr_make_buffer_vertex(sizeof(uint32_t) * index_count, mesh.indices);
  
  return mesh;
}

void sglr_free_mesh(sglr_Mesh mesh){
  sglr_free_buffer(mesh.buffer_pos);
  sglr_free_buffer(mesh.buffer_tc);
  sglr_free_buffer(mesh.buffer_norm);
  sglr_free_buffer(mesh.buffer_idx);
}

sglr_Mesh sglr_make_mesh_primitive_cube(){

  static sglr_Mesh mesh;
  if(mesh.index_count){
    return mesh;
  }

  vec3 min = vec3_make(-0.5f, -0.5f, 0.5);
  vec3 max = vec3_make(0.5f, 0.5f, -0.5);
  
  float pos[] = {
    //front
    min.x, min.y, min.z,
    max.x, min.y, min.z,
    max.x, max.y, min.z,
    min.x, max.y, min.z,

    //back
    min.x, min.y, max.z,
    max.x, min.y, max.z,
    max.x, max.y, max.z,
    min.x, max.y, max.z,

    //left
    min.x, min.y, max.z,
    min.x, min.y, min.z,
    min.x, max.y, min.z,
    min.x, max.y, max.z,

    //right
    max.x, min.y, max.z,
    max.x, min.y, min.z,
    max.x, max.y, min.z,
    max.x, max.y, max.z,

    //top
    min.x, max.y, min.z,
    max.x, max.y, min.z,
    max.x, max.y, max.z,
    min.x, max.y, max.z,

    //bottom
    min.x, min.y, min.z,
    max.x, min.y, min.z,
    max.x, min.y, max.z,
    min.x, min.y, max.z,  
  };

  min = vec3_zero(0, 0, 0);
  max = vec3_make(1, 1, 0);
  
  float tc[] = {
    min.x, min.y, 0,
    max.x, min.y, 0,
    max.x, max.y, 0,
    min.x, max.y, 0,
    
    max.x, min.y, 0,
    min.x, min.y, 0,
    min.x, max.y, 0,
    max.x, max.y, 0,

    max.x, min.y, 0,
    min.x, min.y, 0,
    min.x, max.y, 0,
    max.x, max.y, 0,

    min.x, min.y, 0,
    max.x, min.y, 0,
    max.x, max.y, 0,
    min.x, max.y, 0,

    max.x, min.y, 0,
    min.x, min.y, 0,
    min.x, max.y, 0,
    max.x, max.y, 0,

    min.x, min.y, 0,
    max.x, min.y, 0,
    max.x, max.y, 0,
    min.x, max.y, 0,
    
  };

  float norm[] = {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,

    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,

    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,

    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
  };
  
  uint32_t indices[] = 
    {
      0, 1, 3,
      1, 2, 3,
      
      4, 7, 5,
      5, 7, 6,

      8, 9,  11,
      9, 10, 11,
      
      12, 15, 13,
      13, 15, 14,

      16, 17, 18,
      16, 18, 19,

      20, 22, 21,
      20, 23, 22,
    };

  mesh = sglr_make_mesh(sizeof(pos) / sizeof(*pos),
                        pos,
                        tc,
                        norm,
                        sizeof(indices) / sizeof(*indices),
                        indices);
  return mesh;
}

void sglr_set_mesh_debug_name(sglr_Mesh mesh, const char* name){
  if(!name)
    return;
  
  size_t l = strlen(name);
  char* buf = (char*)malloc(l + 10);
    
  // pos
  sprintf(buf,  "%s_pos", name);
  sglr_set_buffer_debug_name(mesh.buffer_pos, buf);

  // tc
  sprintf(buf,  "%s_tc", name);
  sglr_set_buffer_debug_name(mesh.buffer_tc, buf);

  // id
  sprintf(buf,  "%s_idx", name);
  sglr_set_buffer_debug_name(mesh.buffer_idx, buf);
  
  free(buf);
}
