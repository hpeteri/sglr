#include "sglr_immediate_mode.h"
sglr_ImmediateModeCmd* sglr_immediate_begin(sglr_GraphicsPipeline pipeline){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  sglr_ImmediateModeCmd* cmd = allocator.alloc(sizeof(sglr_ImmediateModeCmd));
  N1_ZERO_MEMORY(cmd);
  
  cmd->graphics_pipeline = pipeline;
  cmd->vert_max_count    = 256;
  cmd->vertices          = allocator.alloc(sizeof(sglr_IMVertex) * cmd->vert_max_count);
  cmd->idx_max_count     = 256;
  cmd->indices           = allocator.alloc(sizeof(uint32_t) * cmd->idx_max_count);

  cmd->current.color = sglr_color_white;
  return cmd;
}

void sglr_immediate_vertex(sglr_ImmediateModeCmd* cmd, vec3 pos){
  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  cmd->current.pos = pos;

  if(cmd->vert_count == cmd->vert_max_count){
    cmd->vert_max_count *= 2;
    cmd->vertices = allocator.realloc(cmd->vertices, sizeof(sglr_IMVertex) * cmd->vert_max_count);
  }

  cmd->vertices[cmd->vert_count++] = cmd->current;
}

void sglr_immediate_tc(sglr_ImmediateModeCmd* cmd, vec3 tc){
  cmd->current.tc = tc;
}

void sglr_immediate_color(sglr_ImmediateModeCmd* cmd, uint32_t color){
  cmd->current.color = color;  
}

void sglr_immediate_normal(sglr_ImmediateModeCmd* cmd, vec3 normal){
  cmd->current.norm = normal;
}

void sglr_immediate_index(sglr_ImmediateModeCmd* cmd, uint32_t idx){

  sglr_Context* context = sglr_current_context();
  n1_Allocator allocator = context->allocator;

  if(cmd->idx_count == cmd->idx_max_count){
    cmd->idx_max_count *= 2;  
    cmd->indices = (uint32_t*)allocator.realloc(cmd->indices,
                                                   sizeof(uint32_t) * cmd->idx_max_count);
  }

  cmd->indices[cmd->idx_count] = idx;
  cmd->idx_count ++;
}

void sglr_immediate_triangle(sglr_ImmediateModeCmd* cmd,
                             vec3 p0, vec3 tc0, uint32_t color0,
                             vec3 p1, vec3 tc1, uint32_t color1,
                             vec3 p2, vec3 tc2, uint32_t color2){
  
  uint32_t idx = cmd->vert_count;
  
  sglr_immediate_tc(cmd, tc0);
  sglr_immediate_color(cmd, color0);
  sglr_immediate_vertex(cmd, p0);
    
  sglr_immediate_tc(cmd, tc1);
  sglr_immediate_color(cmd, color1);
  sglr_immediate_vertex(cmd, p1);
  
  sglr_immediate_tc(cmd, tc2);
  sglr_immediate_color(cmd, color2);
  sglr_immediate_vertex(cmd, p2);

  sglr_immediate_index(cmd, idx);
  sglr_immediate_index(cmd, idx + 1);
  sglr_immediate_index(cmd, idx + 2);
}

void sglr_immediate_quad_min_max(sglr_ImmediateModeCmd* cmd,
                                 vec3 p0, vec3 tc0, uint32_t color0,
                                 vec3 p1, vec3 tc1, uint32_t color1){

  uint32_t idx = cmd->vert_count;
  sglr_immediate_color(cmd, color0);
  sglr_immediate_tc(cmd, tc0);
  sglr_immediate_vertex(cmd, p0);

  sglr_immediate_tc(cmd, vec3_make(tc0.x, tc1.y, tc0.z));
  sglr_immediate_vertex(cmd, vec3_make(p0.x, p1.y, p0.z));

  
  sglr_immediate_color(cmd, color1);
  sglr_immediate_tc(cmd, tc1);
  sglr_immediate_vertex(cmd, p1);

  sglr_immediate_tc(cmd, vec3_make(tc1.x, tc0.y, tc0.z));
  sglr_immediate_vertex(cmd, vec3_make(p1.x, p0.y, p0.z));

                        
  sglr_immediate_index(cmd, idx);

  sglr_immediate_index(cmd, idx + 2);
  sglr_immediate_index(cmd, idx + 1);
  
  sglr_immediate_index(cmd, idx);
  sglr_immediate_index(cmd, idx + 3);
  sglr_immediate_index(cmd, idx + 2);

}

void sglr_immediate_mesh(sglr_ImmediateModeCmd* cmd,
                         sglr_Mesh mesh,
                         mat4 model){

  const uint32_t idx = cmd->vert_count;
  
  for(uint32_t i = 0; i < mesh.vertex_count; i++){

    float* pos = mesh.pos + i * 3;
    float* tc  = mesh.tc + i * 3;
    float* norm = mesh.norm + i * 3;
    
    vec4 p0 = vec4_make(pos[0], pos[1], pos[2], 1);
    p0 = mat4_mulv(model, p0);
    
    vec4 n0 = vec4_make(norm[0], norm[1], norm[2], 1);
    n0 = mat4_mulv(model, n0);
    n0 = vec4_subv(n0, model.col_3);
    
    sglr_immediate_tc(cmd, vec3_make(tc[0], tc[1], tc[2]));
    sglr_immediate_normal(cmd, vec3_make(n0.x, n0.y, n0.z));
    sglr_immediate_vertex(cmd, vec3_make(p0.x, p0.y, p0.z));
  }

  for(uint32_t i = 0; i < mesh.index_count; i++){
    sglr_immediate_index(cmd, idx + mesh.indices[i]);
  }
}

void sglr_immediate_aabb_outline(sglr_ImmediateModeCmd* cmd, vec3 min, vec3 max, uint32_t color, float line_width){
  
  vec3 normal = vec3_make(0, 1, 0);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(min.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, max.y, min.z), color, vec3_make(min.x, max.y, max.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(max.x, min.y, min.z), color, vec3_make(max.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(max.x, max.y, min.z), color, vec3_make(max.x, max.y, max.z), color, line_width);
  

  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(max.x, min.y, min.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, min.y, max.z), color, vec3_make(max.x, min.y, max.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, max.y, min.z), color, vec3_make(max.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, max.y, max.z), color, vec3_make(max.x, max.y, max.z), color, line_width);

  normal = vec3_make(1, 0, 0);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, min.y, min.z), color, vec3_make(min.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(max.x, min.y, min.z), color, vec3_make(max.x, max.y, min.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(min.x, min.y, max.z), color, vec3_make(min.x, max.y, max.z), color, line_width);
  sglr_immediate_line_3d(cmd, normal, vec3_make(max.x, min.y, max.z), color, vec3_make(max.x, max.y, max.z), color, line_width);
}
void sglr_immediate_cube_outline(sglr_ImmediateModeCmd* cmd,
                                 vec3 p0,
                                 vec3 p1,
                                 vec3 p2,
                                 vec3 p3,
                                 vec3 p4,
                                 vec3 p5,
                                 vec3 p6,
                                 vec3 p7,
                                 uint32_t color,
                                 float line_width){

  vec3 normal = vec3_make(0, 1, 0);
  sglr_immediate_line_3d(cmd, normal, p0, color, p1, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p1, color, p2, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p2, color, p3, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p3, color, p0, color, line_width);
  
  sglr_immediate_line_3d(cmd, normal, p4, color, p5, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p5, color, p6, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p6, color, p7, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p7, color, p4, color, line_width);
 
  normal = vec3_make(1, 0, 0);
  sglr_immediate_line_3d(cmd, normal, p0, color, p4, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p1, color, p5, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p2, color, p6, color, line_width);
  sglr_immediate_line_3d(cmd, normal, p3, color, p7, color, line_width);
}
                                       
void sglr_immediate_line_2d(sglr_ImmediateModeCmd* cmd,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float width){

  const vec3 dir = vec3_subv(p0, p1);
  normal = vec3_normalize(vec3_cross(dir, normal));
  normal = vec3_mulv(normal,
                     vec3_make1(width * 0.5f));
  
  vec3 p0_l = vec3_addv(p0, normal);
  vec3 p0_r = vec3_subv(p0, normal);
  
  vec3 p1_l = vec3_addv(p1, normal);
  vec3 p1_r = vec3_subv(p1, normal);

  vec3 zerov = vec3_zero();
  sglr_immediate_triangle(cmd,
                          p0_l, zerov, color0,
                          p1_l, zerov, color1,
                          p0_r, zerov, color0);

  sglr_immediate_triangle(cmd,
                          p0_r, zerov, color0,
                          p1_l, zerov, color1,
                          p1_r, zerov, color1);
  
}
void sglr_immediate_line_3d(sglr_ImmediateModeCmd* cmd,
                            vec3 normal,
                            vec3 p0, uint32_t color0,
                            vec3 p1, uint32_t color1,
                            float width){
  sglr_immediate_line_2d(cmd,
                         normal,
                         p0, color0,
                         p1, color1,
                         width);

  normal = vec3_cross(normal,
                      vec3_subv(p1, p0));

  sglr_immediate_line_2d(cmd,
                         normal,
                         p0, color0,
                         p1, color1,
                         width);
}

vec2 sglr_immediate_text(sglr_ImmediateModeCmd* cmd,
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

  vec2 cursor_curr = vec2_zero();
  vec2 cursor_max = vec2_zero();

  while(*at){
    const char character = *(char*)at;

    if(character == '\n'){

      cursor.y -= size;
      cursor.x = p0.x;

      //calculate text size
      cursor_max.x = max(cursor_max.x, cursor_curr.x);
      cursor_max.y -= size;
      cursor_curr.x = 0;

      at++;
      continue;
    }
    
    uint32_t codepoint = 0;
    { //codepoint
      int len = 0;
      // utf-8 to codepoint
      if((character & 0b11110000) == 0b11110000){
        len = 4;
        codepoint = ((at[0] & 0b11111) << 18) | (at[1] & 0b111111 << 12) | (at[2] & 0b111111 << 6) | (at[3] & 0b111111);
      }else if((character & 0b11100000) == 0b11100000){
        len = 3;
        codepoint = ((at[0] & 0b11111) << 12) | (at[1] & 0b111111 << 6) | (at[2] & 0b111111);
      }else if((character & 0b110000000) == 0b110000000){
        len = 2;
        codepoint = ((at[0] & 0b11111) << 6) | (at[1] & 0b111111);
      }else if((character & 0b000000000) == 0b000000000){
        len = 1;
        codepoint = character;
      }else{
        SGLR_ASSERT(0);
        //should not be possible if valid encoding
      }
      
      for(int i = 0; i < len; i++){
        if(!*at){
          
          SGLR_ASSERT(0);
        }
        at ++;
      }
    }
    
    if(codepoint > 256){
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

    tc_0.y -= 2.0 / 256.0f;
    sglr_immediate_quad_min_max(cmd,
                                vec3_make(cursor.x, cursor.y, cursor.z),
                                tc_0,
                                color,
                                vec3_make(cursor.x + size, cursor.y + size, cursor.z),
                                tc_1,
                                color);
                                
    cursor.x += size;
    cursor_curr.x += size;
  }

  cursor_max.x = max(cursor_max.x, cursor_curr.x);
  cursor_max.y -= size;

  return cursor_max;

}
