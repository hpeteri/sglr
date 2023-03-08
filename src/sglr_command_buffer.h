#ifndef SGLR_COMMAND_BUFFER_H
#define SGLR_COMMAND_BUFFER_H

#include "sglr_state.h"
#include "sglr_mesh.h"
#include "sglr_graphics_pipeline.h"
#include "sglr_compute_pipeline.h"
#include "sglr_camera.h"

#include "cmath/n1_cmath.h"

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

#include "sglr_immediate_mode.h"

// compute dispatch
typedef struct sglr_ComputeDispatchCmd{

  int32_t width;
  int32_t height;
  int32_t depth;  

} sglr_ComputeDispatchCmd;

typedef enum SGLR_COMMAND_BUFFER_COMMAND_TYPE{

  SGLR_COMMAND_BUFFER_COMMAND_INVALID = 0,
  SGLR_COMMAND_BUFFER_COMMAND_IM,
  SGLR_COMMAND_BUFFER_COMMAND_COMPUTE_DISPATCH,
  SGLR_COMMAND_BUFFER_COMMAND_SET_COMPUTE_PIPELINE,
  SGLR_COMMAND_BUFFER_COMMAND_SET_GRAPHICS_PIPELINE,
  SGLR_COMMAND_BUFFER_COMMAND_MEMORY_BARRIER,
  SGLR_COMMAND_BUFFER_COMMAND_TEXTURE_BARRIER,
  
} SGLR_COMMAND_BUFFER_COMMAND_TYPE;
  
typedef struct sglr_CommandBufferCmd{

  SGLR_COMMAND_BUFFER_COMMAND_TYPE type;
  
  union{
    sglr_ImmediateModeCmd*  im;
    sglr_ComputeDispatchCmd compute_dispatch;
    
    sglr_ComputePipeline  compute_pipeline;
    sglr_GraphicsPipeline graphics_pipeline;    
    int                   value;
  };
  
} sglr_CommandBufferCmd;


#define MULTI_CAMERA_COUNT_MAX (4)
struct sglr_CommandBuffer2CamInfo{
  uint32_t cam_count;
  uint32_t pad_0;
  uint32_t pad_1;
  uint32_t pad_2;
    
  uint32_t render_layers[MULTI_CAMERA_COUNT_MAX];
  mat4     cam_projections[MULTI_CAMERA_COUNT_MAX];
};

struct sglr_CommandBuffer2{

  SGLR_COMMAND_BUFFER_2_FLAGS flags;
  int                         draw_layer_idx;

  struct sglr_CommandBuffer2CamInfo cam_info;
  
  uint32_t cmd_count;
  uint32_t cmd_count_max;
  sglr_CommandBufferCmd* cmds;
  
  sglr_CommandBuffer2* next;
};

sglr_CommandBuffer2* sglr_make_command_buffer2();

void sglr_free_command_buffer2(sglr_CommandBuffer2* scb);
void sglr_command_buffer2_submit(sglr_CommandBuffer2* scb, sglr_CommandBuffer* command_buffer);
void sglr_command_buffer2_execute(sglr_CommandBuffer2* scb);

// camera functions
void sglr_command_buffer2_add_cam(sglr_CommandBuffer2* scb, sglr_Camera cam);
void sglr_command_buffer2_add_cam_to_layer(sglr_CommandBuffer2* scb, sglr_Camera cam,
                                           int render_layer_idx);
void sglr_command_buffer2_set_draw_layer(sglr_CommandBuffer2* scb, int layer);

// commands
void sglr_cmd_memory_barrier(sglr_CommandBuffer2* scb, GLbitfield barriers);
void sglr_cmd_texture_barrier(sglr_CommandBuffer2* scb);

// compute
void sglr_cmd_set_compute_pipeline(sglr_CommandBuffer2* scb, sglr_ComputePipeline pipeline);
void sglr_cmd_compute_dispatch(sglr_CommandBuffer2* scb, int32_t width, int32_t height, int32_t depth);

//draw 
void sglr_cmd_set_graphics_pipeline(sglr_CommandBuffer2* scb, sglr_GraphicsPipeline pipeline);
void sglr_cmd_immediate_draw(sglr_CommandBuffer2* scb, sglr_ImmediateModeCmd* batch);
#endif
