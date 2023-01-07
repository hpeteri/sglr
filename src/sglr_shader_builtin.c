// === flat ===
extern const char flat_vert[];
extern const char flat_frag[];

asm(".section .text");

asm("flat_vert: ");
asm(".incbin \"builtin_shaders/flat/flat.vert.glsl\"");
asm(".byte 0");

asm("flat_frag: ");
asm(".incbin \"builtin_shaders/flat/flat.frag.glsl\"");
asm(".byte 0");

asm(".previous");

// ===  bitmap font ===

extern const char bitmap_font_vert[];
extern const char bitmap_font_frag[];

asm(".section .text");

asm("bitmap_font_vert: ");
asm(".incbin \"builtin_shaders/bitmap_font/bitmap_font.vert.glsl\"");
asm(".byte 0");

asm("bitmap_font_frag: ");
asm(".incbin \"builtin_shaders/bitmap_font/bitmap_font.frag.glsl\"");
asm(".byte 0");

asm(".previous");

// === PBR ===

extern const char pbr_vert[];
extern const char pbr_frag[];

asm(".section .text");

asm("pbr_vert: ");
asm(".incbin \"builtin_shaders/pbr/pbr.vert.glsl\"");
asm(".byte 0");

asm("pbr_frag: ");
asm(".incbin \"builtin_shaders/pbr/pbr.frag.glsl\"");
asm(".byte 0");

asm(".previous");

// === depth_only ===
extern const char depth_only_vert[];
extern const char depth_only_frag[];
extern const char depth_only_geom[];

asm(".section .text");

asm("depth_only_vert: ");
asm(".incbin \"builtin_shaders/depth_only/depth_only.vert.glsl\"");
asm(".byte 0");

asm("depth_only_frag: ");
asm(".incbin \"builtin_shaders/depth_only/depth_only.frag.glsl\"");
asm(".byte 0");

asm("depth_only_geom: ");
asm(".incbin \"builtin_shaders/depth_only/depth_only.geom.glsl\"");
asm(".byte 0");

asm(".previous");

// === z prepass
extern const char z_prepass_vert[];
extern const char z_prepass_frag[];

asm(".section .text");

asm("z_prepass_vert: ");
asm(".incbin \"builtin_shaders/z_prepass/z_prepass.vert.glsl\"");
asm(".byte 0");

asm("z_prepass_frag: ");
asm(".incbin \"builtin_shaders/z_prepass/z_prepass.frag.glsl\"");
asm(".byte 0");

asm(".previous");
