#include "sglr_command_buffer.h"


// primary
sglr_CommandBuffer* sglr_make_command_buffer(){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_CommandBuffer* cb = (sglr_CommandBuffer*)allocator.alloc(sizeof(sglr_CommandBuffer));
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

// secondary

// - batch
sglr_CommandBuffer2* sglr_make_command_buffer2(sglr_GraphicsPipeline graphics_pipeline, sglr_Mesh mesh){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_CommandBuffer2* cb = (sglr_CommandBuffer2*)allocator.alloc(sizeof(sglr_CommandBuffer2));
  N1_ZERO_MEMORY(cb);

  cb->type     = COMMAND_BUFFER_2_TYPE_BATCH;
  cb->graphics_pipeline = graphics_pipeline;
  cb->mesh     = mesh;
  cb->cam      = sglr_make_camera();

  return cb;
}

void sglr_command_buffer2_draw_mesh(mat4 trs);

// - immediate mode
sglr_CommandBuffer2* sglr_make_command_buffer2_im(sglr_GraphicsPipeline graphics_pipeline){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_CommandBuffer2* cb = (sglr_CommandBuffer2*)allocator.alloc(sizeof(sglr_CommandBuffer2));
  N1_ZERO_MEMORY(cb);

  cb->type              = COMMAND_BUFFER_2_TYPE_IM;
  cb->graphics_pipeline          = graphics_pipeline;
  cb->im.vert_max_count = 256;
  cb->im.pos            = (vec3*)allocator.alloc(sizeof(vec3) * cb->im.vert_max_count);
  cb->im.tc             = (vec3*)allocator.alloc(sizeof(vec3) * cb->im.vert_max_count);
  cb->im.color          = (uint32_t*)allocator.alloc(sizeof(uint32_t) * cb->im.vert_max_count);
  cb->im.idx_max_count  = 256;
  cb->im.indices        = (uint32_t*)allocator.alloc(sizeof(uint32_t) * cb->im.idx_max_count);
  return cb;
}

void sglr_immediate_vertex(sglr_CommandBuffer2* scb, vec3 pos){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  scb->im.current.pos = pos;

  if(scb->im.vert_count == scb->im.vert_max_count){

    scb->im.vert_max_count *= 2;
    
    scb->im.pos = (vec3*)allocator.realloc(scb->im.pos,
                                           sizeof(vec3) * scb->im.vert_max_count);
    
    scb->im.tc = (vec3*)allocator.realloc(scb->im.tc,
                                          sizeof(vec3) * scb->im.vert_max_count);

    scb->im.color = (uint32_t*)allocator.realloc(scb->im.color,
                                                 sizeof(uint32_t) * scb->im.vert_max_count);
                                   
  }

  scb->im.pos[scb->im.vert_count]   = scb->im.current.pos;
  scb->im.tc[scb->im.vert_count]    = scb->im.current.tc;
  scb->im.color[scb->im.vert_count] = scb->im.current.color;

  scb->im.vert_count++;
}

void sglr_immediate_tc(sglr_CommandBuffer2* scb, vec3 tc){
  scb->im.current.tc = tc;
}

void sglr_immediate_color(sglr_CommandBuffer2* scb, uint32_t color){
  scb->im.current.color = color;  
}

void sglr_immediate_index(sglr_CommandBuffer2* scb, uint32_t idx){

  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  if(scb->im.idx_count == scb->im.idx_max_count){
    scb->im.idx_max_count *= 2;  
    scb->im.indices = (uint32_t*)allocator.realloc(scb->im.indices,
                                                   sizeof(uint32_t) * scb->im.idx_max_count);
  }

  scb->im.indices[scb->im.idx_count] = idx;
  scb->im.idx_count ++;
}

void sglr_immediate_triangle(sglr_CommandBuffer2* scb,
                             vec3 p0, vec3 tc0, uint32_t color0,
                             vec3 p1, vec3 tc1, uint32_t color1,
                             vec3 p2, vec3 tc2, uint32_t color2){
  
  uint32_t idx = scb->im.vert_count;
  
  sglr_immediate_tc(scb, tc0);
  sglr_immediate_color(scb, color0);
  sglr_immediate_vertex(scb, p0);
    
  sglr_immediate_tc(scb, tc1);
  sglr_immediate_color(scb, color1);
  sglr_immediate_vertex(scb, p1);
  
  sglr_immediate_tc(scb, tc2);
  sglr_immediate_color(scb, color2);
  sglr_immediate_vertex(scb, p2);

  sglr_immediate_index(scb, idx);
  sglr_immediate_index(scb, idx + 1);
  sglr_immediate_index(scb, idx + 2);
}

void sglr_immediate_quad_min_max(sglr_CommandBuffer2* scb,
                                 vec3 p0, vec3 tc0, uint32_t color0,
                                 vec3 p1, vec3 tc1, uint32_t color1){

  uint32_t idx = scb->im.vert_count;
  sglr_immediate_color(scb, color0);
  sglr_immediate_tc(scb, tc0);
  sglr_immediate_vertex(scb, p0);

  sglr_immediate_tc(scb, vec3_make(tc0.x, tc1.y, tc0.z));
  sglr_immediate_vertex(scb, vec3_make(p0.x, p1.y, p0.z));

  
  sglr_immediate_color(scb, color1);
  sglr_immediate_tc(scb, tc1);
  sglr_immediate_vertex(scb, p1);

  sglr_immediate_tc(scb, vec3_make(tc1.x, tc0.y, tc0.z));
  sglr_immediate_vertex(scb, vec3_make(p1.x, p0.y, p0.z));

                        
  sglr_immediate_index(scb, idx);
  sglr_immediate_index(scb, idx + 1);
  sglr_immediate_index(scb, idx + 2);
  
  sglr_immediate_index(scb, idx);
  sglr_immediate_index(scb, idx + 2);
  sglr_immediate_index(scb, idx + 3);

}

void sglr_immediate_aabb_outline(sglr_CommandBuffer2* scb, vec3 min, vec3 max, uint32_t color, float line_width){
  
  vec3 normal = vec3_make(0, 1, 0);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(min.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, max.y, min.z), color, vec3_make(min.x, max.y, max.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(max.x, min.y, min.z), color, vec3_make(max.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(max.x, max.y, min.z), color, vec3_make(max.x, max.y, max.z), color, line_width);
  

  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(max.x, min.y, min.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, min.y, max.z), color, vec3_make(max.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, max.y, min.z), color, vec3_make(max.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, max.y, max.z), color, vec3_make(max.x, max.y, max.z), color, line_width);

  normal = vec3_make(1, 0, 0);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(min.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(max.x, min.y, min.z), color, vec3_make(max.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(min.x, min.y, max.z), color, vec3_make(min.x, max.y, max.z), color, line_width);
  sglr_immediate_line_3d(scb, normal, vec3_make(max.x, min.y, max.z), color, vec3_make(max.x, max.y, max.z), color, line_width);
}
void sglr_immediate_line_2d(sglr_CommandBuffer2* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float width){

  const vec3 dir = vec3_subv(p0, p1);
  normal = vec3_normalize(vec3_cross(dir, normal));
  normal = vec3_mulv(normal,
                     vec3_make1(width));
  
  vec3 p0_l = vec3_addv(p0, normal);
  vec3 p0_r = vec3_subv(p0, normal);
  
  vec3 p1_l = vec3_addv(p1, normal);
  vec3 p1_r = vec3_subv(p1, normal);

  vec3 zerov = vec3_zero();
  sglr_immediate_triangle(scb,
                          p0_l, zerov, color0,
                          p1_l, zerov, color1,
                          p0_r, zerov, color0);

  sglr_immediate_triangle(scb,
                          p0_r, zerov, color0,
                          p1_l, zerov, color1,
                          p1_r, zerov, color1);
  
}
void sglr_immediate_line_3d(sglr_CommandBuffer2* scb,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float width){
  sglr_immediate_line_2d(scb,
                         normal,
                         p0, color0,
                         p1, color1,
                         width);

  normal = vec3_cross(normal,
                      vec3_subv(p1, p0));

  sglr_immediate_line_2d(scb,
                         normal,
                         p0, color0,
                         p1, color1,
                         width);
}

void sglr_immediate_text(sglr_CommandBuffer2* scb,
                         const char* text,
                         vec3 p0,
                         float scale,
                         uint32_t color){

  int pad_x = 0;
  int pad_y = 2;
  
  vec3 tc = vec3_make((8 + pad_x) / 128.0f,
                      (8 + pad_y) / 256.0f,
                      0);
  
  char* at = (char*)text;

  float size = 8.0f * scale;

  vec3 cursor = p0;
  while(*at){
    const char character = *(char*)at;

    if(character == '\n'){
      cursor.y -= size * 1.5;
      cursor.x = p0.x;
      at++;
      continue;
    }
    
    uint32_t codepoint = 0;
    { //codepoint
      int len = 0;
      
      //decode utf-8
      
      if((character & 0b11110000) == 0b11110000){
        asm("int3");
        
        len = 4;
        //this should be masked
        codepoint = *(uint32_t*)at;

      }else if((character & 0b11100000) == 0b11100000){

        asm("int3");
        len = 3;
        //this should be masked
        codepoint = ((at[2] << 16) & (at[1] << 8) & at[0]);
                     
      }else if((character & 0b110000000) == 0b110000000){

        len = 2;
        codepoint = ((at[0] & 0b11111) << 6) | (at[1] & 0b111111);
        
      }else if((character & 0b000000000) == 0b000000000){

        //ascii representation
        len = 1;
        codepoint = character;

      }else{
        asm("int3");
        //should not be possible if valid encoding
      }

      for(int i = 0; i < len; i++){
        
        if(!*at){
          //overrun
          asm("int3");
        }
        at ++;
      }
    }
    
    if(codepoint > 256){
      printf("%d is greater than 256\n", codepoint);
      codepoint = 0;
    }
    
    
    const int row    = codepoint / 16;
    const int column = codepoint % 16;

    vec3 tc_0 = vec3_make(column * tc.x,
                          row *  tc.y,
                          0);

    vec3 tc_1 = vec3_addv(tc_0, tc);

    float tmp = tc_0.y;
    tc_0.y = tc_1.y;
    tc_1.y = tmp;


    //tc_0 = bottom,
    tc_0.y -= 2.0 / 256.0f;
    
    
    sglr_immediate_quad_min_max(scb,
                                vec3_make(cursor.x, cursor.y, cursor.z),
                                tc_0,
                                color,
                                vec3_make(cursor.x + size, cursor.y + size, cursor.z),
                                tc_1,
                                color);
                                
    cursor.x += size;
  }  
}
void sglr_command_buffer2_set_cam(sglr_CommandBuffer2* scb, sglr_Camera camera){
  scb->cam = camera;
}

void sglr_free_command_buffer2(sglr_CommandBuffer2* scb){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  if(scb->type == COMMAND_BUFFER_2_TYPE_IM){
    allocator.free(scb->im.pos);
    allocator.free(scb->im.tc);
    allocator.free(scb->im.color);
    allocator.free(scb->im.indices);
  }
  
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
  if(scb->type == COMMAND_BUFFER_2_TYPE_IM){
    const uint32_t vert_count = scb->im.vert_count;
    const uint32_t idx_count  = scb->im.idx_count;
    
    if(vert_count){
      
      sglr_Buffer position_buffer = sglr_make_buffer_vertex(sizeof(vec3) * vert_count, scb->im.pos);
      sglr_set_buffer_debug_name(position_buffer, "im_pos");

      sglr_Buffer tc_buffer = sglr_make_buffer_vertex(sizeof(vec3) * vert_count, scb->im.tc);
      sglr_set_buffer_debug_name(tc_buffer, "im_tc");

      sglr_Buffer color_buffer = sglr_make_buffer_vertex(sizeof(uint32_t) * vert_count, scb->im.color);
      sglr_set_buffer_debug_name(color_buffer, "im_color");
      
      sglr_Buffer idx_buffer = sglr_make_buffer_index(sizeof(uint32_t) * idx_count, scb->im.indices);
      sglr_set_buffer_debug_name(tc_buffer, "im_idx");

      sglr_GraphicsPipeline graphics_pipeline = scb->graphics_pipeline;
      sglr_Shader shader = graphics_pipeline.material.shader;
      
      //identity model
      
      mat4 identity = mat4_scalef(1);
      if(shader.model_loc != -1){
        glVertexAttrib4fv(shader.model_loc + 0, identity.a_v[0].a);
        glVertexAttrib4fv(shader.model_loc + 1, identity.a_v[1].a);
        glVertexAttrib4fv(shader.model_loc + 2, identity.a_v[2].a);
        glVertexAttrib4fv(shader.model_loc + 3, identity.a_v[3].a);
      }
      sglr_set_graphics_pipeline(graphics_pipeline);
      
      //set camera
      sglr_set_uniform_mat4(shader, "cam_proj", sglr_camera_matrix(scb->cam));
      

      if(shader.pos_loc != -1){
        //bind pos buffer
        glEnableVertexAttribArray(shader.pos_loc);
        sglr_set_buffer(position_buffer);
        glVertexAttribPointer(shader.pos_loc,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(vec3),
                              (void*)0);
        sglr_check_error();
      }

      if(shader.tc_loc != -1){
        glEnableVertexAttribArray(shader.tc_loc);
        sglr_set_buffer(tc_buffer);
        glVertexAttribPointer(shader.tc_loc,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(vec3),
                              (void*)0);
        sglr_check_error();
      }

      if(shader.color_loc != -1){
        glEnableVertexAttribArray(shader.color_loc);
        sglr_set_buffer(color_buffer);
        glVertexAttribPointer(shader.color_loc,
                              4,
                              GL_UNSIGNED_BYTE,
                              GL_TRUE,
                              sizeof(uint32_t),
                              (void*)0);
        sglr_check_error();
      }


      //set renderer state
      //...

      //draw
      glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, 0);

      //free
      sglr_free_buffer(position_buffer);
      sglr_free_buffer(tc_buffer);
      sglr_free_buffer(idx_buffer);
      sglr_free_buffer(color_buffer);
      sglr_unset_shader();
    }
  }else{
    //assert
    *(int*)NULL = 0;
  }
}
