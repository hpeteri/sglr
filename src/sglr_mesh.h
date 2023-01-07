#ifndef SGLR_MESH_H
#define SGLR_MESH_H

#include "sglr_buffer.h"

typedef struct sglr_Mesh{

<<<<<<< HEAD
  sglr_Buffer vertices;
  sglr_Buffer indices;
  
} sglr_Mesh;

sglr_Mesh sglr_make_mesh(uint32_t               vertex_count,
                         const float const*     positions,
                         const float const*     tc,
                         uint32_t               index_count,
                         const uint16_t const* indices);
=======
  uint32_t vertex_count;
  uint32_t index_count;
  
  float* pos;
  float* tc;
  float* norm;
  
  uint32_t* indices;
  
  sglr_Buffer buffer_pos;
  sglr_Buffer buffer_tc;
  sglr_Buffer buffer_norm;
  sglr_Buffer buffer_idx;
  
} sglr_Mesh;

sglr_Mesh sglr_make_mesh(uint32_t              vertex_count,
                         const float const*    positions,
                         const float const*    tc,
                         const float const*    norm,
                         uint32_t              index_count,
                         const uint32_t const* indices);

sglr_Mesh sglr_make_mesh_primitive_cube();
>>>>>>> dev

void sglr_free_mesh(sglr_Mesh mesh);
void sglr_set_mesh_debug_name(sglr_Mesh mesh, const char* name);

<<<<<<< HEAD
=======

>>>>>>> dev
#endif
