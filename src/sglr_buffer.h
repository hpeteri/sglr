#ifndef SGLR_BUFFER_H
#define SGLR_BUFFER_H

typedef struct sglr_Buffer{
  GLuint id;

  GLenum type;
  uint32_t size;
  GLenum usage;
} sglr_Buffer;

sglr_Buffer sglr_make_buffer_index(uint32_t size, void* data);
sglr_Buffer sglr_make_buffer_vertex(uint32_t size, void* data);
sglr_Buffer sglr_make_buffer_uniform(uint32_t size, void* data);
sglr_Buffer sglr_make_buffer_instance(uint32_t size, void* data);
sglr_Buffer sglr_make_buffer_transfer(uint32_t size, void* data);
void        sglr_copy_buffer(sglr_Buffer src, sglr_Buffer dst, uint32_t src_offset, uint32_t dst_offset, uint32_t size);
void        sglr_fill_buffer(sglr_Buffer src, uint32_t size, void* data);
void        sglr_free_buffer(sglr_Buffer buffer);
void        sglr_set_buffer(sglr_Buffer buffer);
void        sglr_unset_buffer(GLenum type);
void        sglr_set_buffer_debug_name(sglr_Buffer buffer, const char* name);

#endif
