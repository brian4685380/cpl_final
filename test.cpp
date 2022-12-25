#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

int main(int argc, char *argv[]) {
	// Initialize SDL
	// Create a window
	SDL_Window *window = SDL_CreateWindow("Chinese Text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	// Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Initialize SDL_ttf and load the font

	TTF_Font *font = TTF_OpenFont("./GameProject/assets/Font/Cubic_11/fonts/ttf/Cubic_11_1.010_R.ttf", 24);


	// Set up the text color and rectangle
	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Rect textRect = {10, 10, 0, 0};

	// Main loop
	SDL_Event event;
	int running = 1;
	while (running) {
		// Handle events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		char *s = "測試";
		// Render the text
		SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, s, textColor);
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		// Update the screen
		SDL_RenderPresent(renderer);

		// Clean up
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}

	// Clean up
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
