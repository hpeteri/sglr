#ifndef SGLR_COMMAND_BUFFER_H
#define SGLR_COMMAND_BUFFER_H

#include "sglr_state.h"
#include "sglr_mesh.h"
#include "sglr_graphics_pipeline.h"
#include "sglr_compute_pipeline.h"
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
typedef enum SGLR_COMMAND_BUFFER_2_TYPE{
  SGLR_COMMAND_BUFFER_2_TYPE_INVALID = 0,
  SGLR_COMMAND_BUFFER_2_TYPE_IM, 
  SGLR_COMMAND_BUFFER_2_TYPE_COMPUTE,
} SGLR_COMMAND_BUFFER_2_TYPE;

enum SGLR_COMMAND_BUFFER_2_FLAG_BITS{
  SGLR_COMMAND_BUFFER_2_MULTI_LAYER_BIT = 0x1,
};

typedef uint8_t SGLR_COMMAND_BUFFER_2_FLAGS;

typedef struct sglr_IMVertex{
  vec3     pos;
  vec3     tc;
  vec3     norm;
  uint32_t color;
} sglr_IMVertex;

typedef struct sglr_ComputeWorkGroup{
  int32_t width;
  int32_t height;
  int32_t depth;  
} sglr_ComputeWorkGroup;

struct sglr_CommandBuffer2{

  SGLR_COMMAND_BUFFER_2_TYPE  type;
  SGLR_COMMAND_BUFFER_2_FLAGS flags;
  int                         draw_layer_idx;
  
  sglr_Mesh             mesh;

  uint32_t    cam_count;
  sglr_Camera cams[256];
  int         render_layers[256];

  struct {
    
    uint32_t cam_count;
    uint32_t pad_0;
    uint32_t pad_1;
    uint32_t pad_2;
    
    uint32_t render_layers[12];
    mat4     cam_projections[12];
    
  } cam_info;
  
  union{
    struct {
      sglr_GraphicsPipeline graphics_pipeline;
      uint32_t vert_count;
      uint32_t vert_max_count;
      
      uint32_t idx_count;
      uint32_t idx_max_count;
      
      sglr_IMVertex* vertices;
      uint32_t*  indices;
      
      sglr_IMVertex  current;
      
    } im;

    struct {
      sglr_ComputePipeline pipeline;

      int32_t work_group_count;
      int32_t work_group_max_count;
      sglr_ComputeWorkGroup work_groups[256];
      
    } compute;
  };
  
  
  sglr_CommandBuffer2* next;
};


sglr_CommandBuffer2* sglr_make_command_buffer2_im(sglr_GraphicsPipeline graphics_pipeline);
sglr_CommandBuffer2* sglr_make_command_buffer2_compute(sglr_ComputePipeline pipeline);

void sglr_free_command_buffer2(sglr_CommandBuffer2* scb);
void sglr_command_buffer2_submit(sglr_CommandBuffer2* scb, sglr_CommandBuffer* command_buffer);
void sglr_command_buffer2_execute(sglr_CommandBuffer2* scb);

// camera functions
void sglr_command_buffer2_add_cam(sglr_CommandBuffer2* scb, sglr_Camera cam);
void sglr_command_buffer2_add_cam_to_layer(sglr_CommandBuffer2* scb, sglr_Camera cam,
                                           int render_layer_idx);
void sglr_command_buffer2_set_draw_layer(sglr_CommandBuffer2* scb, int layer);


// === IMMEDIATE_MODE ====

void sglr_immediate_vertex(sglr_CommandBuffer2* scb, vec3 pos);
void sglr_immediate_tc(sglr_CommandBuffer2* scb, vec3 tc);
void sglr_immediate_color(sglr_CommandBuffer2* scb, uint32_t color);
void sglr_immediate_normal(sglr_CommandBuffer2* scb, vec3 normal);
void sglr_immediate_index(sglr_CommandBuffer2* scb, uint32_t idx);

void sglr_immediate_triangle(sglr_CommandBuffer2* scb,
                             vec3 p0, vec3 tc0, uint32_t color0,
                             vec3 p1, vec3 tc1, uint32_t color1,
                             vec3 p2, vec3 tc2, uint32_t color2);

void sglr_immediate_quad_min_max(sglr_CommandBuffer2* scb,
                                 vec3 p0, vec3 tc0, uint32_t color0,
                                 vec3 p1, vec3 tc1, uint32_t color1);

void sglr_immediate_mesh(sglr_CommandBuffer2* scb,
                         sglr_Mesh mesh,
                         mat4 model);

void sglr_immediate_aabb_outline(sglr_CommandBuffer2* scb, vec3 min, vec3 max, uint32_t color, float line_width);
void sglr_immediate_cube_outline(sglr_CommandBuffer2* scb,
                                 vec3 p0, vec3 p1, vec3 p2, vec3 p3,
                                 vec3 p4, vec3 p5, vec3 p6, vec3 p7,
                                 uint32_t color,
                                 float line_width);
                                                  
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

vec2 sglr_immediate_text(sglr_CommandBuffer2* scb,
                         const char* text,
                         vec3 p0,
                         float scale,
                         uint32_t color);

// === COMPUTE ===
void sglr_compute_dispatch(sglr_CommandBuffer2* scb, int32_t width, int32_t height, int32_t depth);

#endif
