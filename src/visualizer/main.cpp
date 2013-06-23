#include <iostream>
#include <allegro5/allegro.h>

#include "display.hpp"

int main(int argc, char **argv){
	int status = run_display();
	if( status != 0 )
	{
		std::cerr << "Failed to run the quick display." << std::endl;
	}
	return status;
}
