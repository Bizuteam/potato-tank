#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	int run = 1;

	//Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	window = SDL_CreateWindow("Shoot'em L1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}
	else {
		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		//Fill the surface white
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

		//Update the surface
		SDL_UpdateWindowSurface(window);

		while(run) {
			SDL_Event event;
			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) {
					run = 0;
					break;
				}
				if(keys[SDL_SCANCODE_W]) {
					printf("Z\n");
				}
				if(keys[SDL_SCANCODE_A]) {
					printf("Q\n");
				}
				if(keys[SDL_SCANCODE_S]) {
					printf("S\n");
				}
				if(keys[SDL_SCANCODE_D]) {
					printf("D\n");
				}
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return EXIT_SUCCESS;
}
