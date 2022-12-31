#ifndef SGLR_MESH_H
#define SGLR_MESH_H

#include "sglr_buffer.h"

typedef struct sglr_Mesh{

  sglr_Buffer vertices;
  sglr_Buffer indices;
  
} sglr_Mesh;

sglr_Mesh sglr_make_mesh(uint32_t               vertex_count,
                         const float const*     positions,
                         const float const*     tc,
                         uint32_t               index_count,
                         const uint16_t const* indices);

void sglr_free_mesh(sglr_Mesh mesh);
void sglr_set_mesh_debug_name(sglr_Mesh mesh, const char* name);

#endif
