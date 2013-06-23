#include "display.hpp"
#include <iostream>

#include <allegro5/allegro.h>

int run_display()
{
	int status = al_init();
  if(!status)
     return -1;

  ALLEGRO_DISPLAY *display = al_create_display(1024, 768);
	if(!display)
     return -1;

  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();
  al_rest(3.0);
  al_destroy_display(display);

  return 0;
}
