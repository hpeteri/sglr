#include "sglr_command_buffer.h"

#include "sglr_immediate_mode.c"

static void sglr_maybe_expand_cmd_buffer(sglr_CommandBuffer2* scb);
static void sglr_push_cmd(sglr_CommandBuffer2* scb, sglr_CommandBufferCmd cmd);

static void sglr_execute_immediate_cmd(sglr_ImmediateModeCmd* im,
                                       sglr_GraphicsPipeline pipeline,
                                       SGLR_COMMAND_BUFFER_2_FLAGS command_buffer_flags,
                                       struct sglr_CommandBuffer2CamInfo cam_info);



// primary
sglr_CommandBuffer* sglr_make_command_buffer(){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_CommandBuffer* cb = allocator.alloc(sizeof(sglr_CommandBuffer));
  N1_ZERO_MEMORY(cb);

  return cb;  
}

void sglr_free_command_buffer(sglr_CommandBuffer* command_buffer){

  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;
  
  allocator.free(command_buffer);
}

void sglr_command_buffer_submit(sglr_CommandBuffer* command_buffer){
  sglr_Context* context = sglr_current_context();
  
  sglr_CommandBuffer* tail = context->command_buffers;
  
  if(!tail){
    context->command_buffers = command_buffer;
    return;
  }
  
  //find tail from linked list
  while(tail){
    if(tail->next){
      tail = tail->next;
    }else{
      break;
    }    
  }

  tail->next = command_buffer;
}

void sglr_command_buffer_set_render_target(sglr_CommandBuffer* command_buffer, sglr_RenderTarget render_target){
  command_buffer->render_target = render_target;
}

void sglr_command_buffer_set_state(sglr_CommandBuffer* command_buffer, sglr_State state){
  command_buffer->state = state;
}

void sglr_command_buffer_execute(sglr_CommandBuffer* command_buffer){
  sglr_CommandBuffer2* scb = command_buffer->cb2s;

  sglr_set_render_target(command_buffer->render_target);
  
  
  while(scb){

    sglr_command_buffer2_execute(scb);
    
    sglr_CommandBuffer2* next = scb->next;
    
    sglr_free_command_buffer2(scb);
    scb = next;    
  }
}

//sglr_ComputePipeline compute_pipeline){
sglr_CommandBuffer2* sglr_make_command_buffer2(){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_CommandBuffer2* cb = (sglr_CommandBuffer2*)allocator.alloc(sizeof(sglr_CommandBuffer2));
  N1_ZERO_MEMORY(cb);
  
  return cb;
}

void sglr_command_buffer2_add_cam(sglr_CommandBuffer2* scb, sglr_Camera camera){
  
  if(scb->cam_info.cam_count < MULTI_CAMERA_COUNT_MAX){
    const uint32_t count = scb->cam_info.cam_count;
    
    scb->cam_info.render_layers[count]   = 0;
    scb->cam_info.cam_projections[count] = sglr_camera_matrix(camera);
    
    scb->cam_info.cam_count ++;
  }
  
}

void sglr_command_buffer2_add_cam_to_layer(sglr_CommandBuffer2* scb, sglr_Camera camera, int render_layer_idx){
  
  scb->flags |= SGLR_COMMAND_BUFFER_2_MULTI_LAYER_BIT;
  
  if(scb->cam_info.cam_count < MULTI_CAMERA_COUNT_MAX){
    const uint32_t count = scb->cam_info.cam_count;
    
    scb->cam_info.render_layers[count]   = render_layer_idx;
    scb->cam_info.cam_projections[count] = sglr_camera_matrix(camera);
    
    scb->cam_info.cam_count ++;
  }
}


void sglr_command_buffer2_set_draw_layer(sglr_CommandBuffer2* scb, int layer){
  scb->draw_layer_idx = layer;
}

void sglr_free_command_buffer2(sglr_CommandBuffer2* scb){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  
  
  
  allocator.free(scb);  
}

void sglr_command_buffer2_submit(sglr_CommandBuffer2* scb, sglr_CommandBuffer* command_buffer){
  sglr_CommandBuffer2* tail = command_buffer->cb2s;
  
  if(!tail){
    command_buffer->cb2s = scb;
    return;
  }
  
  //find tail from linked list
  while(tail){
    if(tail->next){
      tail = tail->next;
    }else{
      break;
    }    
  }

  tail->next = scb;
}

void sglr_command_buffer2_execute(sglr_CommandBuffer2* scb){
  glDrawBuffer(GL_COLOR_ATTACHMENT0 + scb->draw_layer_idx);

  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_GraphicsPipeline current_pipeline = {};
  
  for(uint32_t i = 0; i < scb->cmd_count; i++){
    sglr_CommandBufferCmd cmd = scb->cmds[i];
    
    switch(cmd.type){
    case SGLR_COMMAND_BUFFER_COMMAND_COMPUTE_DISPATCH:
      {
        glDispatchCompute(cmd.compute_dispatch.width,
                          cmd.compute_dispatch.height,
                          cmd.compute_dispatch.depth);
        sglr_check_error();
        break;
      }
    case SGLR_COMMAND_BUFFER_COMMAND_SET_COMPUTE_PIPELINE:
      {
        const sglr_ComputePipeline pipeline = cmd.compute_pipeline;
        sglr_set_compute_pipeline(pipeline);      
        break;
      }
    case SGLR_COMMAND_BUFFER_COMMAND_SET_GRAPHICS_PIPELINE:
      {
        current_pipeline = cmd.graphics_pipeline;
        sglr_set_graphics_pipeline(current_pipeline);

        break;
      }
    case SGLR_COMMAND_BUFFER_COMMAND_IM:
      {
        if(current_pipeline.material.shader.id == 0)
          asm("int3");

        
        sglr_execute_immediate_cmd(cmd.im,
                                   current_pipeline,
                                   scb->flags,
                                   scb->cam_info);

        if(cmd.im->submit_count == 0){
          allocator.free(cmd.im->vertices);
          allocator.free(cmd.im->indices);
          allocator.free(cmd.im);
        }
  
        break;
      }
    case SGLR_COMMAND_BUFFER_COMMAND_MEMORY_BARRIER:
      {
        glMemoryBarrier(cmd.value);
        sglr_check_error();
        break;
      }
    case SGLR_COMMAND_BUFFER_COMMAND_TEXTURE_BARRIER:
      {
        glTextureBarrier();
        sglr_check_error();
        break;
      }      
    default:
      SGLR_ASSERT(0);
      break;

    }
  }
  
  allocator.free(scb->cmds);
}

static void sglr_maybe_expand_cmd_buffer(sglr_CommandBuffer2* scb){

  if(scb->cmd_count >= scb->cmd_count_max){
    sglr_Context* context = sglr_current_context();
    n1_Allocator allocator = context->allocator;

    if(scb->cmd_count == 0){
      scb->cmd_count_max = 16;
      scb->cmds = allocator.alloc(sizeof(sglr_CommandBufferCmd) * scb->cmd_count_max);
    }else{
      scb->cmd_count_max *= 2;
      scb->cmds = allocator.realloc(scb->cmds,
                                    sizeof(sglr_CommandBufferCmd) * scb->cmd_count_max);

    }    
  }
}

static void sglr_push_cmd(sglr_CommandBuffer2* scb, sglr_CommandBufferCmd cmd){
  sglr_maybe_expand_cmd_buffer(scb);
  scb->cmds[scb->cmd_count++] = cmd;
}

void sglr_cmd_memory_barrier(sglr_CommandBuffer2* scb, GLbitfield barriers){
  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_MEMORY_BARRIER;
  cmd.value = barriers;

  sglr_push_cmd(scb, cmd);  
}

void sglr_cmd_texture_barrier(sglr_CommandBuffer2* scb){
  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_TEXTURE_BARRIER;

  sglr_push_cmd(scb, cmd);  
}

void sglr_cmd_compute_dispatch(sglr_CommandBuffer2* scb, int32_t width, int32_t height, int32_t depth){
  
  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_COMPUTE_DISPATCH;
  cmd.compute_dispatch.width = width;
  cmd.compute_dispatch.height = height;
  cmd.compute_dispatch.depth = depth;

  sglr_push_cmd(scb, cmd);  
}

void sglr_cmd_set_compute_pipeline(sglr_CommandBuffer2* scb, sglr_ComputePipeline pipeline){

  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_SET_COMPUTE_PIPELINE;
  cmd.compute_pipeline = pipeline;
  
  sglr_push_cmd(scb, cmd);  
}

void sglr_cmd_set_graphics_pipeline(sglr_CommandBuffer2* scb, sglr_GraphicsPipeline pipeline){
  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_SET_GRAPHICS_PIPELINE;
  cmd.graphics_pipeline = pipeline;
  
  sglr_push_cmd(scb, cmd);  
}

void sglr_cmd_immediate_draw(sglr_CommandBuffer2* scb, sglr_ImmediateModeCmd* im){
  sglr_CommandBufferCmd cmd;
  cmd.type = SGLR_COMMAND_BUFFER_COMMAND_IM;
  cmd.im = im;

  im->submit_count ++;
  sglr_push_cmd(scb, cmd);
}


static void sglr_execute_immediate_cmd(sglr_ImmediateModeCmd* im,
                                       sglr_GraphicsPipeline graphics_pipeline,
                                       SGLR_COMMAND_BUFFER_2_FLAGS command_buffer_flags,
                                       struct sglr_CommandBuffer2CamInfo cam_info){
  if(!im)
    return;

  im->submit_count --;
  
  const uint32_t vert_count = im->vert_count;
  const uint32_t idx_count  = im->idx_count;

  if(!vert_count || !idx_count){
    goto cleanup_im;
  }
    
  if(!im->gpu_vert.id){
    im->gpu_vert = sglr_make_buffer_vertex(sizeof(sglr_IMVertex) * vert_count, im->vertices);
    im->gpu_idx  = sglr_make_buffer_index(sizeof(uint32_t) * idx_count, im->indices);
  }
  sglr_Shader shader = graphics_pipeline.material.shader;
      
  //identity model
      
  mat4 identity = mat4_scalef(1);
  if(shader.model_loc != -1){
    glVertexAttrib4fv(shader.model_loc + 0, identity.a_v[0].a);
    glVertexAttrib4fv(shader.model_loc + 1, identity.a_v[1].a);
    glVertexAttrib4fv(shader.model_loc + 2, identity.a_v[2].a);
    glVertexAttrib4fv(shader.model_loc + 3, identity.a_v[3].a);
    sglr_check_error();
  }
      
  sglr_set_graphics_pipeline(graphics_pipeline);

  sglr_set_buffer(im->gpu_vert);
  
  if(shader.pos_loc != -1){
    //bind pos buffer
    glEnableVertexAttribArray(shader.pos_loc);
    glVertexAttribPointer(shader.pos_loc,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sglr_IMVertex),
                          (void*)offsetof(sglr_IMVertex, pos));
    sglr_check_error();
  }

  if(shader.tc_loc != -1){
    glEnableVertexAttribArray(shader.tc_loc);
    glVertexAttribPointer(shader.tc_loc,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sglr_IMVertex),
                          (void*)offsetof(sglr_IMVertex, tc));
    sglr_check_error();
  }

  if(shader.color_loc != -1){
    glEnableVertexAttribArray(shader.color_loc);
    glVertexAttribPointer(shader.color_loc,
                          4,
                          GL_UNSIGNED_BYTE,
                          GL_TRUE,
                          sizeof(sglr_IMVertex),
                          (void*)offsetof(sglr_IMVertex, color));
    sglr_check_error();
  }

  if(shader.norm_loc != -1){
    glEnableVertexAttribArray(shader.norm_loc);
    glVertexAttribPointer(shader.norm_loc,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sglr_IMVertex),
                          (void*)offsetof(sglr_IMVertex, norm));
    sglr_check_error();
  }
      
  //set renderer state
  //...

  //draw
  //set camera
  if(command_buffer_flags & SGLR_COMMAND_BUFFER_2_MULTI_LAYER_BIT){
    GLuint cam_info_loc = glGetUniformBlockIndex(shader.id, "cam_info");
    if(cam_info_loc != GL_INVALID_INDEX){

      sglr_Buffer cam_buf = sglr_make_buffer_uniform(sizeof(cam_info),
                                                      &cam_info);

      sglr_set_buffer_debug_name(cam_buf, "cam_info");
            
      //@todo, check that buffers on cpu and gpu are the same size
      glBindBufferBase(GL_UNIFORM_BUFFER, cam_info_loc, cam_buf.id);
      sglr_check_error();
          
      glDrawElements(graphics_pipeline.topology, idx_count, GL_UNSIGNED_INT, NULL);
      sglr_stats_add_triangle_count_indexed(idx_count, GL_TRIANGLES);
      sglr_stats_add_draw_call_count(1);
          
      sglr_free_buffer(cam_buf);

          
    }else{
      SGLR_ASSERT(0);
    }
  }else{
    sglr_set_uniform_mat4(shader, "cam_proj", cam_info.cam_projections[0]);
    //sglr_set_uniform_float(shader, "cam_far", cam_info);
    
    
    glDrawElements(graphics_pipeline.topology, idx_count, GL_UNSIGNED_INT, 0);
    sglr_stats_add_triangle_count_indexed(idx_count, GL_TRIANGLES);
    sglr_stats_add_draw_call_count(1);
    
  }
      
  if(shader.pos_loc != -1){
    glDisableVertexAttribArray(shader.pos_loc);
    sglr_check_error();
  }
  if(shader.tc_loc != -1){
    glDisableVertexAttribArray(shader.tc_loc);
    sglr_check_error();
  }
  if(shader.color_loc != -1){
    glDisableVertexAttribArray(shader.color_loc);
    sglr_check_error();
  }
  if(shader.norm_loc != -1){
    glDisableVertexAttribArray(shader.norm_loc);
    sglr_check_error();
  }

  sglr_unset_shader();
  
 cleanup_im:

  if(im->submit_count == 0){
    sglr_free_buffer(im->gpu_vert);
    sglr_free_buffer(im->gpu_idx);
  }
}
