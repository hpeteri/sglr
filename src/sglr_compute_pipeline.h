#ifndef SGLR_COMPUTE_PIPELINE_H
#define SGLR_COMPUTE_PIPELINE_H

typedef struct sglr_ComputePipeline{
  sglr_Material material;
  
} sglr_ComputePipeline;

sglr_ComputePipeline sglr_make_compute_pipeline(sglr_Material material);
void sglr_set_compute_pipeline(sglr_ComputePipeline pipeline);

#endif
