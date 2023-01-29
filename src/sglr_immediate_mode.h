#ifndef SGLR_IMMEDIATE_MODE_H
#define SGLR_IMMEDIATE_MODE_H


// immediate mode command
typedef struct sglr_IMVertex{

  vec3     pos;
  vec3     tc;
  vec3     norm;
  uint32_t color;

} sglr_IMVertex;

typedef struct sglr_ImmediateModeCmd{

  //sglr_GraphicsPipeline graphics_pipeline;
  uint32_t vert_count;
  uint32_t vert_max_count;
      
  uint32_t idx_count;
  uint32_t idx_max_count;
      
  sglr_IMVertex* vertices;
  uint32_t*  indices;
      
  sglr_IMVertex  current;


  int         submit_count;
  sglr_Buffer gpu_vert;
  sglr_Buffer gpu_idx;

} sglr_ImmediateModeCmd;


sglr_ImmediateModeCmd* sglr_immediate_begin();//sglr_GraphicsPipeline pipeline);


void sglr_immediate_vertex(sglr_ImmediateModeCmd* scb, vec3 pos);
void sglr_immediate_tc(sglr_ImmediateModeCmd* scb, vec3 tc);
void sglr_immediate_color(sglr_ImmediateModeCmd* scb, uint32_t color);
void sglr_immediate_normal(sglr_ImmediateModeCmd* scb, vec3 normal);
void sglr_immediate_index(sglr_ImmediateModeCmd* scb, uint32_t idx);

void sglr_immediate_triangle(sglr_ImmediateModeCmd* scb,
                             vec3 p0, vec3 tc0, uint32_t color0,
                             vec3 p1, vec3 tc1, uint32_t color1,
                             vec3 p2, vec3 tc2, uint32_t color2);

void sglr_immediate_quad_min_max(sglr_ImmediateModeCmd* scb,
                                 vec3 p0, vec3 tc0, uint32_t color0,
                                 vec3 p1, vec3 tc1, uint32_t color1);

void sglr_immediate_mesh(sglr_ImmediateModeCmd* scb,
                         sglr_Mesh mesh,
                         mat4 model);

void sglr_immediate_aabb_outline(sglr_ImmediateModeCmd* scb, vec3 min, vec3 max, uint32_t color, float line_width);
void sglr_immediate_cube_outline(sglr_ImmediateModeCmd* scb,
                                 vec3 p0, vec3 p1, vec3 p2, vec3 p3,
                                 vec3 p4, vec3 p5, vec3 p6, vec3 p7,
                                 uint32_t color,
                                 float line_width);
                                                  
void sglr_immediate_line_2d(sglr_ImmediateModeCmd* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float line_width);

void sglr_immediate_line_3d(sglr_ImmediateModeCmd* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float line_width);

vec2 sglr_immediate_text(sglr_ImmediateModeCmd* scb,
                         const char* text,
                         vec3 p0,
                         float scale,
                         uint32_t color);

#endif
