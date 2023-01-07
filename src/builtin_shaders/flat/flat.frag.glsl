#version 460
   
uniform sampler2D texture0;
   
in vec4 frag_color;
in vec3 frag_tc;
in vec3 frag_norm;
   
out vec4 out_color;
   
void main(){
  out_color = texture(texture0, frag_tc.xy) * frag_color;
   
  float gamma = 2.2;
  out_color.rgb = pow(out_color.rgb, vec3(1.0 / gamma));
}
