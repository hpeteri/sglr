// === flat ===
extern const char flat_vert[];
extern const char flat_frag[];

// ===  bitmap font ===

extern const char bitmap_font_vert[];
extern const char bitmap_font_frag[];

// ======================================== 
// SOURCES
// ========================================

// === flat ===
const char flat_vert[] =
  "\n" "#version 420                                           "
  "\n" "uniform mat4 cam_proj;                                 "
  "\n" "                                                       "
  "\n" "layout(location = 0) in vec3 vert_pos;                 "
  "\n" "layout(location = 1) in vec3 vert_tc;                  "
  "\n" "layout(location = 2) in vec4 vert_color;               "
  "\n" "layout(location = 3) in vec3 vert_norm;                "
  "\n" "                                                       "
  "\n" "layout(location = 10) in mat4 model;                   "
  "\n" "                                                       "
  "\n" "out vec4 frag_color;                                   "
  "\n" "out vec3 frag_tc;                                      "
  "\n" "out vec3 frag_norm;                                    "
  "\n" "                                                       "
  "\n" "void main(){                                           "
  "\n" "  gl_Position = cam_proj * model * vec4(vert_pos, 1);  "
  "\n" "  frag_color = vert_color;                             "
  "\n" "  frag_tc = vert_tc;                                   "
  "\n" "  frag_norm = vert_norm;                               "
  "\n" "}                                                      "
  "\n" ""
  "\n" "";

const char flat_frag[] =
  "\n" "#version 420                                              "
  "\n" "                                                          "
  "\n" "uniform sampler2D texture0;                               "
  "\n" "                                                          "
  "\n" "in vec4 frag_color;                                       "
  "\n" "in vec3 frag_tc;                                          "
  "\n" "in vec3 frag_norm;                                        "
  "\n" "                                                          "
  "\n" "out vec4 out_color;                                       "
  "\n" "                                                          "
  "\n" "void main(){                                              "
  "\n" "  out_color = texture(texture0, frag_tc.xy) * frag_color; "
  "\n" "                                                          "
  "\n" "  float gamma = 2.2;                                      "
  "\n" "  out_color.rgb = pow(out_color.rgb, vec3(1.0 / gamma));  "
  "\n" "}                                                         "
  "\n" "";


// ===  bitmap font ===

const char bitmap_font_vert[] =
  "\n" "#version 420                                   "
  "\n" "                                               "
  "\n" "uniform mat4 cam_proj;                         "
  "\n" "                                               "
  "\n" "layout(location = 0) in vec3 vert_pos;         "
  "\n" "layout(location = 1) in vec3 vert_tc;          "
  "\n" "layout(location = 2) in vec4 vert_color;       "
  "\n" "                                               "
  "\n" "out vec4 frag_color;                           "
  "\n" "out vec3 frag_tc;                              "
  "\n" "                                               "
  "\n" "void main(){                                   "
  "\n" "  gl_Position = cam_proj * vec4(vert_pos, 1);  "
  "\n" "  frag_color = vert_color;                     "
  "\n" "  frag_tc = vert_tc;                           "
  "\n" "}                                              "
  "\n" "";

const char bitmap_font_frag[] =
  "\n" "#version 420                                        "
  "\n" "                                                    "
  "\n" "uniform sampler2D texture0;                         "
  "\n" "                                                    "
  "\n" "in vec4 frag_color;                                 "
  "\n" "in vec3 frag_tc;                                    "
  "\n" "                                                    "
  "\n" "out vec4 out_color;                                 "
  "\n" "                                                    "
  "\n" "void main(){                                        "
  "\n" "  if(texture(texture0, frag_tc.xy).a == 0) discard; "
  "\n" "  out_color = frag_color;                           "
  "\n" "                                                    "
  "\n" "}                                                   "
  "\n" "";

