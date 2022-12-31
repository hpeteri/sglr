#ifndef SGLR_COMMAND_BUFFER_H
#define SGLR_COMMAND_BUFFER_H

#include "sglr_state.h"
#include "sglr_mesh.h"
#include "sglr_graphics_pipeline.h"
#include "sglr_camera.h"

#include "n1_cmath.h"
// forward declare secondary
typedef struct sglr_CommandBuffer2 sglr_CommandBuffer2;

// primary
typedef struct sglr_CommandBuffer{
  sglr_State        state;
  sglr_RenderTarget render_target;

  sglr_CommandBuffer2* cb2s; //linked list of secondary buffers
  sglr_CommandBuffer* next;
  
} sglr_CommandBuffer;

sglr_CommandBuffer* sglr_make_command_buffer();
void                sglr_free_command_buffer(sglr_CommandBuffer* command_buffer);
void                sglr_command_buffer_submit(sglr_CommandBuffer* command_buffer);
void                sglr_command_buffer_set_render_target(sglr_CommandBuffer* command_buffer, sglr_RenderTarget render_target);
void                sglr_command_buffer_set_state(sglr_CommandBuffer* command_buffer, sglr_State state);

void sglr_command_buffer_execute(sglr_CommandBuffer* command_buffer);

// secondary

typedef enum sqlr_COMMAND_BUFFER_2_TYPE{
  COMMAND_BUFFER_2_TYPE_INVALID = 0,
  COMMAND_BUFFER_2_TYPE_IM,
  COMMAND_BUFFER_2_TYPE_BATCH,  
} sqlr_COMMAND_BUFFER_2_TYPE;

struct sglr_CommandBuffer2{
  sqlr_COMMAND_BUFFER_2_TYPE type;
  sglr_Mesh mesh;
  sglr_GraphicsPipeline graphics_pipeline;

  sglr_Camera cam;
  
  union{
    struct {
      uint32_t vert_count;
      uint32_t vert_max_count;
      
      uint32_t idx_count;
      uint32_t idx_max_count;
      
      vec3*     pos;
      vec3*     tc;
      uint32_t* color;

      uint32_t* indices;
      
      struct{
        vec3     pos;
        vec3     tc;
        uint32_t color;
      } current;
      
    } im;
  };

  
  sglr_CommandBuffer2* next;
};

// - batch
sglr_CommandBuffer2* sglr_make_command_buffer2(sglr_GraphicsPipeline graphics_pipeline, sglr_Mesh mesh);
void                 sglr_command_buffer2_draw_mesh(mat4 trs);

// - immediate mode
sglr_CommandBuffer2* sglr_make_command_buffer2_im(sglr_GraphicsPipeline graphics_pipeline);
void sglr_immediate_vertex(sglr_CommandBuffer2* scb, vec3 pos);
void sglr_immediate_tc(sglr_CommandBuffer2* scb, vec3 tc);
void sglr_immediate_color(sglr_CommandBuffer2* scb, uint32_t color);
void sglr_immediate_index(sglr_CommandBuffer2* scb, uint32_t idx);

void sglr_immediate_triangle(sglr_CommandBuffer2* scb,
                             vec3 p0, vec3 tc0, uint32_t color0,
                             vec3 p1, vec3 tc1, uint32_t color1,
                             vec3 p2, vec3 tc2, uint32_t color2);

void sglr_immediate_quad_min_max(sglr_CommandBuffer2* scb,
                                 vec3 p0, vec3 tc0, uint32_t color0,
                                 vec3 p1, vec3 tc1, uint32_t color1);

void sglr_immediate_aabb_outline(sglr_CommandBuffer2* scb, vec3 min, vec3 max, uint32_t color, float line_width);
                         
void sglr_immediate_line_2d(sglr_CommandBuffer2* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float line_width);

void sglr_immediate_line_3d(sglr_CommandBuffer2* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float line_width);

void sglr_immediate_text(sglr_CommandBuffer2* scb,
                         const char* text,
                         vec3 p0,
                         float scale,
                         uint32_t color);

void sglr_command_buffer2_set_cam(sglr_CommandBuffer2* scb, sglr_Camera cam);
void sglr_free_command_buffer2(sglr_CommandBuffer2* scb);
void sglr_command_buffer2_submit(sglr_CommandBuffer2* scb, sglr_CommandBuffer* command_buffer);
void sglr_command_buffer2_execute(sglr_CommandBuffer2* scb);


#endif
