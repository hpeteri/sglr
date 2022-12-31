#include <stdio.h>

#define N1_ALLOCATOR_IMPLEMENTATION
#include "c_allocator/n1_allocator.h"

#include "n1_platform_main.c"


//renderer
#include "sglr.c"

sglr_Context* renderer;

int main(int argc, const char* argv[]){
  //Create window
  n1_Window* window = platform_create_window("simple window");
  perror("created window");

  if(!platform_create_glcontext(window)){
    perror("failed to create glContext\n");
    return 1;
  }
  perror("created gl context");
  
  renderer = sglr_make_context(default_allocator());
  sglr_set_context(renderer);
  
  if(!renderer){
    perror("failed to create renderer context");
    return 1;
  }

  platform_init_time();
  
  uint64_t ns_start = platform_get_time_ns();

  int ns_fps      = 0;
  int frame_count = 0;
  
  int is_running = 1;

  int mouse_x = 0;
  int mouse_y = 0;

  int window_width = 0;
  int window_height = 0;
  
  while(is_running){
    //handle window events
    platform_window_get_events(window);
    n1_WindowEvent e = platform_window_get_next_event(window);
    while(e.type){
      if(e.type == EVENT_QUIT){
        printf("quit\n");
        is_running = 0;
      }
      else if(e.type == EVENT_MOUSE_MOVE){
        mouse_x = e.mouse.x;
        mouse_y = e.mouse.y;
      }
      else if(e.type == EVENT_SIZE){
        window_width = e.size.width;
        window_height = e.size.height;
      }
      e = platform_window_get_next_event(window);
    }

    ns_fps ++;
    frame_count ++;
    
    sglr_set_clear_color_4f(mouse_x / (float)window_width, mouse_y / (float)window_height, 0, 0);
    sglr_clear_render_target_color();
    
    platform_window_swap_buffers(window);

    uint64_t ns_end = platform_get_time_ns();
        
    if(platform_convert_ns_to_seconds(ns_end - ns_start) >= 1){
      ns_start += second_to_ns;
      printf("fps: %d\n", ns_fps);
      ns_fps = 0;          
    }
  }

  sglr_free_context(sglr_current_context());
  platform_free_glcontext(window);  
  platform_free_window(window);
    
  return 0;
}
