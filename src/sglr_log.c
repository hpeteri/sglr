#include <stdio.h>

#include "sglr_gl.h"
#include "sglr_log.h"

static void  sglr_debug_log_callback(GLenum src, GLenum type, unsigned int id, GLenum severity, 
                                     GLsizei length, const char *message, const void *userParam);

int sglr_make_debug_logger(){
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

  if(!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)){
    printf("sglr: no debug context\n");
    return 0;
  }
  
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 

  glDebugMessageCallback(sglr_debug_log_callback, NULL);
  
  //enable all callbacks
  glDebugMessageControl(GL_DONT_CARE,
                        GL_DONT_CARE,
                        GL_DONT_CARE,
                        0,
                        NULL,
                        GL_TRUE);

  sglr_check_error();
  return 1;  
}

void sglr_free_debug_logger(){
  glDisable(GL_DEBUG_OUTPUT);
}

static void sglr_debug_log_callback(GLenum src, GLenum type, unsigned int id, GLenum severity, 
                                    GLsizei length, const char *message, const void *userParam){
  
  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 
  
  printf("----------------------------------------\n");
  printf("OpenGL: %d\n", id);
  printf("'%s'\n", message);

  switch(src){
  case GL_DEBUG_SOURCE_API:             printf("Source: API\n"); break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Source: Window System\n"); break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Source: Shader Compiler\n"); break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Source: Third Party\n"); break;
  case GL_DEBUG_SOURCE_APPLICATION:     printf("Source: Application\n"); break;
  case GL_DEBUG_SOURCE_OTHER:           printf("Source: Other\n"); break;
  }

  switch(type){
  case GL_DEBUG_TYPE_ERROR:               printf("Type: Error\n"); break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Type: Deprecated Behaviour\n"); break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Type: Undefined Behaviour\n"); break; 
  case GL_DEBUG_TYPE_PORTABILITY:         printf("Type: Portability\n"); break;
  case GL_DEBUG_TYPE_PERFORMANCE:         printf("Type: Performance\n"); break;
  case GL_DEBUG_TYPE_MARKER:              printf("Type: Marker\n"); break;
  case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Type: Push Group\n"); break;
  case GL_DEBUG_TYPE_POP_GROUP:           printf("Type: Pop Group\n"); break;
  case GL_DEBUG_TYPE_OTHER:               printf("Type: Other\n"); break;
  }
    
  switch(severity){
  case GL_DEBUG_SEVERITY_HIGH:         printf("Severity: high\n"); break;
  case GL_DEBUG_SEVERITY_MEDIUM:       printf("Severity: medium\n"); break;
  case GL_DEBUG_SEVERITY_LOW:          printf("Severity: low\n"); break;
  case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Severity: notification\n"); break;
  }
  printf("\n");
}


int sglr_check_error(){
  int err = glGetError();

  if(err){
    printf("%s(): '%d' \n", __func__, err);
    *(int*)NULL = 0;

  }  

  return err;  
}
