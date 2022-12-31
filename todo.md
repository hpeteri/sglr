* Bugs
  - sglr_copy_buffer doesn't seem to work
  - platform doesn't return compatability context
  - platform doesn't check errors correctly when creating window
  - Handle immediate_text large codepoints, now we abort
  
* Features
  - lights
  - shadows
  - frustrum culling
  - mesh ids for draw mesh.
  - gltf parsing and loading for meshes
  - obj parsing and loading for meshes
    
  - GraphicsPipeline:
    - vao ? binding one vao might be faster than changing global vao state all the time

  - hdr backbuffer
    > bloom / post process
  
  - Blending
    - default graphics pipeline doesn't set sfactors or dfactors

  - Track context state to minimize state change in the driver
  - scissor in command buffer