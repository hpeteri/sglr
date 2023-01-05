#include "sglr_buffer.h"

static sglr_Buffer sglr_make_buffer(GLenum type, uint32_t size, void* data, GLenum usage){
  sglr_Buffer buffer;
  N1_ZERO_MEMORY(&buffer);

  buffer.type = type;
  buffer.size = size;
  buffer.usage = usage;
    
  glGenBuffers(1, &buffer.id);
  glBindBuffer(buffer.type, buffer.id);
  sglr_check_error();
  
  glNamedBufferData(buffer.id,
                    size,
                    data,
                    usage);
  
  if(sglr_check_error()){
    printf("failed glNamedBufferData\n");
  }

  return buffer;
}

sglr_Buffer sglr_make_buffer_index(uint32_t size, void* data){
  return sglr_make_buffer(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

sglr_Buffer sglr_make_buffer_vertex(uint32_t size, void* data){
  return sglr_make_buffer(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

sglr_Buffer sglr_make_buffer_uniform(uint32_t size, void* data){
  return sglr_make_buffer(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

sglr_Buffer sglr_make_buffer_instance(uint32_t size, void* data){
  return sglr_make_buffer(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

sglr_Buffer sglr_make_buffer_transfer(uint32_t size, void* data){
  sglr_Buffer buffer = sglr_make_buffer(GL_COPY_READ_BUFFER, size, data, GL_DYNAMIC_DRAW);
  
  return buffer;
}

void sglr_copy_buffer(sglr_Buffer src, sglr_Buffer dst, uint32_t src_offset, uint32_t dst_offset, uint32_t size){
  glCopyNamedBufferSubData(src.id,
                           dst.id,
                           src_offset,
                           dst_offset,
                           size);
  sglr_check_error();
}

void sglr_fill_buffer(sglr_Buffer src, uint32_t size, void* data){
  
  void * dst = glMapNamedBuffer(src.id,
                                 GL_WRITE_ONLY);
  
  memcpy(dst, data, size);
  
  glUnmapNamedBuffer(src.id);
  sglr_check_error();
}
void sglr_free_buffer(sglr_Buffer buffer){
  glDeleteBuffers(1, &buffer.id);
  sglr_check_error();
}

void sglr_set_buffer(sglr_Buffer buffer){
  glBindBuffer(buffer.type, buffer.id);
  sglr_check_error();
}

void sglr_unset_buffer(GLenum type){
  glBindBuffer(type, 0);
  sglr_check_error();
}

void sglr_set_buffer_debug_name(sglr_Buffer buffer, const char* name){
  glObjectLabel(GL_BUFFER,
                buffer.id,
                strlen(name),
                name);
  sglr_check_error();
}
