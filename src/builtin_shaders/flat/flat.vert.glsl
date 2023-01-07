#version 460
   
uniform mat4 cam_proj;
   
layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec3 vert_tc;
layout(location = 2) in vec4 vert_color;
layout(location = 3) in vec3 vert_norm;
   
layout(location = 10) in mat4 model;
   
out vec4 frag_color;
out vec3 frag_tc;
out vec3 frag_norm;
   
void main(){
  gl_Position = cam_proj * model * vec4(vert_pos, 1);
  frag_color = vert_color;
  frag_tc = vert_tc;
  frag_norm = vert_norm;
}
  
