//Trivial displayer <NOT THREAD SAFE>
#include <iostream>
#include "display.hpp"
#include <SDL2/SDL.h>

int main(int argc, char **argv){
	int status = init_display();
	if( status != 0 )
	{
		std::cerr << "Failed to init the trivial display." << std::endl;
		return status;
	}

	SDL_Event e;
	bool run = true;
	
	while( status==0 && run )
	{
		status = render_display();
		if( SDL_PollEvent( &e ) == 1)
		{
			switch(e.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
					run = false;
					break;
			}
		}
	}

	status = term_display();
	if( status != 0 )
	{
		std::cerr << "Failed to init the trivial display." << std::endl;
		return status;
	}
}
