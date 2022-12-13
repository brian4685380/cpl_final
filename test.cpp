#include "SDL.h"

int main() {
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a window
	SDL_Window* window = SDL_CreateWindow("Mouse Position", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	// Main loop
	while (true) {
		// Get the current position of the mouse
		int x, y;

		// Handle events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			Uint32 mouse_state = SDL_GetMouseState(&x, &y);

			// Print the position of the mouse
			printf("Mouse position: (%d, %d)\n", x, y);
			if (event.type == SDL_QUIT) {
				// Quit the program
				break;
			}
		}
	}

	// Clean up
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
