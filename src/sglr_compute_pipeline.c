#include "sglr_compute_pipeline.h"

sglr_ComputePipeline sglr_make_compute_pipeline(sglr_Material material){
  sglr_ComputePipeline pipeline;
  N1_ZERO_MEMORY(&pipeline);

  pipeline.material = material;
  return pipeline;
}

void sglr_set_compute_pipeline(sglr_ComputePipeline pipeline){
  sglr_set_material_2(pipeline.material, 1);
}
