#include "sglr_mesh.h"

sglr_Mesh sglr_make_mesh(uint32_t               vertex_count,
                         const float const*     positions,
                         const float const*     tc,
                         uint32_t               index_count,
                         const uint16_t const* indices){
  sglr_Mesh mesh;
  N1_ZERO_MEMORY(&mesh);
  
  
  return mesh;
}

void sglr_free_mesh(sglr_Mesh mesh){
  sglr_free_buffer(mesh.vertices);
  sglr_free_buffer(mesh.indices);
}

void sglr_set_mesh_debug_name(sglr_Mesh mesh, const char* name){
  if(!name)
    return;
  
  size_t l = strlen(name);
  char* vertex_name = (char*)malloc(l + 10);
  char* index_name =  (char*)malloc(l + 10);

  sprintf(vertex_name, "%s_vertex", name);
  sprintf(index_name,  "%s_index", name);
  
  sglr_set_buffer_debug_name(mesh.vertices, vertex_name);
  sglr_set_buffer_debug_name(mesh.indices, index_name);
  
  free(vertex_name);
  free(index_name);  
}
