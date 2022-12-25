#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

using namespace std;

int main(int argc, char *argv[]) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Create a window
	SDL_Window *window = SDL_CreateWindow("Chinese Text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Initialize SDL_ttf and load the font
	if (TTF_Init() < 0) {
		printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	TTF_Font *font = TTF_OpenFont("./GameProject/assets/Font/Cubic_11/fonts/ttf/Cubic_11_1.010_R.ttf", 24);
	if (!font) {
		printf("Error loading font: %s\n", TTF_GetError());
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Set up the text color and rectangle
	SDL_Color textColor = {0, 0, 0, 255};

	// Main loop
	SDL_Event event;
	int running = 1;
	string systemText[3] = {"第一行", "第二行", "第三行"};
	while (running) {
		// Handle events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_0) {
					systemText[0] = "第一行改";
				}
			}
		}

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		// Render the text
		int fontHeight = TTF_FontHeight(font);
		SDL_Rect systemTextRect = {0, 0, 0, 0};
		SDL_Surface *systemTextSurface;
		SDL_Texture *systemTextTexture;

		// Render the text

		for (int i = 0; i < 3; i++) {
			systemTextSurface = TTF_RenderUTF8_Solid(font, systemText[i].c_str(), textColor);
			systemTextTexture = SDL_CreateTextureFromSurface(renderer, systemTextSurface);
			SDL_QueryTexture(systemTextTexture, NULL, NULL, &systemTextRect.w, &systemTextRect.h);
			SDL_RenderCopy(renderer, systemTextTexture, NULL, &systemTextRect);
			systemTextRect.y += fontHeight;
		}
		// Update the screen
		SDL_RenderPresent(renderer);

		// Clean up
		SDL_FreeSurface(systemTextSurface);
		SDL_DestroyTexture(systemTextTexture);
	}

	// Clean up
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
