#ifndef SGLR_GRAPHICS_PIPELINE_H
#define SGLR_GRAPHICS_PIPELINE_H

#include <stdint.h>

#include "sglr_material.h"

enum SGLR_RENDERER_STATE_BITS{
  SGLR_DEPTH_TEST = 0x1,
  SGLR_BLEND      = 0x2,
  SGLR_CULL_FACE  = 0x4,
};
typedef uint32_t sglr_RendererStateFlags;

typedef struct sglr_RendererState{
  sglr_RendererStateFlags flags;
  
} sglr_RendererState;

typedef struct sglr_BlendOps{
  GLenum sfactor;
  GLenum dfactor;

} sglr_BlendOps;

typedef struct sglr_DepthOps{
  GLenum    func;
  GLboolean mask; //write to depth buffer

} sglr_DepthOps;

typedef struct sglr_GraphicsPipeline{

  GLenum             topology;

  sglr_RendererState renderer_state;
  sglr_BlendOps      blend_mode;
  sglr_DepthOps      depth_mode;
  GLenum             cull_mode;
  
  sglr_Material material;
  
} sglr_GraphicsPipeline;

sglr_GraphicsPipeline slgr_make_graphics_pipeline_default(sglr_Material material, GLenum topology);
sglr_GraphicsPipeline sglr_make_graphics_pipeline(sglr_Material material, GLenum topology, sglr_RendererState renderer_state, sglr_BlendOps blend, sglr_DepthOps depth, GLenum cull);

void sglr_set_graphics_pipeline(sglr_GraphicsPipeline pipeline);

#endif
