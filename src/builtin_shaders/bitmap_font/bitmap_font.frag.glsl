
#version 460
 
uniform sampler2D texture0;
 
in vec4 frag_color;
in vec3 frag_tc;
 
out vec4 out_color;
 
void main(){
  if(texture(texture0, frag_tc.xy).a == 0) discard;
  out_color = frag_color;
 
}
