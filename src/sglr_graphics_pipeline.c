#include "sglr_graphics_pipeline.h"

sglr_GraphicsPipeline sglr_make_graphics_pipeline_default(sglr_Material material, GLenum topology){
  sglr_GraphicsPipeline pipeline;
  N1_ZERO_MEMORY(&pipeline);
  
  pipeline.material       = material;
  pipeline.topology       = topology;

  pipeline.renderer_state.flags |=  SGLR_CULL_FACE | SGLR_DEPTH_TEST;
  
  // === cull ===
  pipeline.cull_mode       = GL_BACK;

  // === depth ===
  pipeline.depth_mode.func = GL_LESS;
  pipeline.depth_mode.mask = 1;

  // === blend ===
  pipeline.blend_mode.sfactor = GL_SRC_ALPHA;
  pipeline.blend_mode.dfactor = GL_ONE_MINUS_SRC_ALPHA;
  
  return pipeline;  
}

sglr_GraphicsPipeline sglr_make_graphics_pipeline(sglr_Material material, GLenum topology, sglr_RendererState renderer_state, sglr_BlendOps blend, sglr_DepthOps depth, GLenum cull){
  
  sglr_GraphicsPipeline pipeline;
  N1_ZERO_MEMORY(&pipeline);
  
  pipeline.material       = material;
  pipeline.topology       = topology;
  pipeline.renderer_state = renderer_state;
  pipeline.blend_mode     = blend;
  pipeline.depth_mode     = depth;
  pipeline.cull_mode      = cull;
  
  return pipeline;  
}

void sglr_set_graphics_pipeline(sglr_GraphicsPipeline pipeline){
  {
    //maybe track these in the context so we can minimize state changes
    sglr_RendererStateFlags flags = pipeline.renderer_state.flags;
    flags & SGLR_DEPTH_TEST ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    flags & SGLR_BLEND      ? glEnable(GL_BLEND)      : glDisable(GL_BLEND);
    flags & SGLR_CULL_FACE  ? glEnable(GL_CULL_FACE)  : glDisable(GL_CULL_FACE);
    sglr_check_error();
  }

  const sglr_RendererStateFlags flags = pipeline.renderer_state.flags;
  
  // === cull ===
  if(flags & SGLR_CULL_FACE){
    glCullFace(pipeline.cull_mode);
    sglr_check_error();
  }
  
  // === blend ===
  if(flags & SGLR_BLEND){
    glBlendFunc(pipeline.blend_mode.sfactor, pipeline.blend_mode.dfactor);
    sglr_check_error();
  }
  
  // === depth ===
  if(flags & SGLR_DEPTH_TEST){
    glDepthFunc(pipeline.depth_mode.func);
    glDepthMask(pipeline.depth_mode.mask);
    sglr_check_error();
  }
  
  // === ===
  //set shader and bind uniforms
  sglr_set_material(pipeline.material);
}
