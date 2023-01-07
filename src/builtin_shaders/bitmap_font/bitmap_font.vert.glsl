#version 460
 
uniform mat4 cam_proj;
 
layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec3 vert_tc;
layout(location = 2) in vec4 vert_color;
 
out vec4 frag_color;
out vec3 frag_tc;
 
void main(){
  gl_Position = cam_proj * vec4(vert_pos, 1);
  frag_color = vert_color;
  frag_tc = vert_tc;
}
