* Bugs
  - platform:
    - platform doesn't return compatability context
    - platform doesn't check errors correctly when creating window
 
  
* Todo
  - lights
  - shadows
  - frustrum culling
  
  - mesh
    - mesh_id
    - submeshes
    - obj loading
    - gltf loading
    - surface and vertex normals
    - topology ?
    - aabb render bounds
  
  - GraphicsPipeline:
    - vao ? binding one vao might be faster than changing global vao state all the time

  - hdr backbuffer
    > bloom / post process
  
  - Track context state to minimize state change in the driver
  - scissor in command buffer

<<<<<<< HEAD
  - batch rendering
=======
  - batch rendering
  - memory usage from meminfo. performancecounters seem so confusing, but i quess we could query drawcount from there ?

  - vsync control, need platfrom implementation
>>>>>>> dev
