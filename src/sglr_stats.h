#ifndef SGLR_STATS_H
#define SGLR_STATS_H

#include <stdint.h>

struct sglr_Stats{
  GLuint time_query_id;

  int32_t triangle_count;
};

const char* sglr_gpu_name();
const char* sglr_gpu_vendor();
const char* sglr_gl_version();
const char* sglr_glsl_version();


void    sglr_begin_query_time_elapsed_ns();
int64_t sglr_end_query_time_elapsed_ns();

void    sglr_stats_reset();

void    sglr_stats_reset_triangle_count();
void    sglr_stats_add_triangle_count(int32_t triangles);
void    sglr_stats_add_triangle_count_indexed(int32_t index_count, GLenum topology);
int32_t sglr_stats_triangle_count();

#endif
