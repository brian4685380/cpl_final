#include "Start.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
using namespace std;

Start::Start() {}
Start::~Start() {}

void Start::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;	// Fullscreen or not
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {  // Init
		std::cout << "Subsystems Initialed!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);	 // Create Window
		if (window) {
			std::cout << "Window created" << std::endl;
		}
		if (!window) {
			printf("Error creating window: %s\n", SDL_GetError());
		}

		// Render window
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}

		// SDL Mixer (Musics and sounds)

		isRunning = true;
	} else {
		isRunning = false;
	}
	objTexture = IMG_LoadTexture(renderer, "assets/backgrounds/cover.png");
	cout << objTexture << endl;
}

void Start::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			Uint32 MouseState = SDL_GetMouseState(&x, &y);
			if (MouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if (showingCover == true) {
					if (x >= 200 && x <= 800 && y >= 320 && y <= 480) {
						isRunning = false;
						SDL_DestroyWindow(window);
						SDL_DestroyRenderer(renderer);
						SDL_Quit();
					} else if (x >= 200 && x <= 800 && y >= 520 && y <= 680) {
						objTexture = IMG_LoadTexture(renderer, "assets/Defender/NTULibrary.png");
						showingCover = false;
					}
				}
				if (showingCover == false) {
					cout << "showingCover = false" << endl;
                    if (x >= 1000 && x <= 1080 && y >= 640 && y <= 720) {
                        objTexture = IMG_LoadTexture(renderer, "assets/backgrounds/cover.png");
                        showingCover = true;
                    }
				}
			}
			break;
	}
}

void Start::update() {
	// Update
	srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
	srcRect.w = destRect.w = 1080;
	srcRect.h = destRect.h = 720;
}

void Start::render() {
	SDL_RenderClear(renderer);
	// Render
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
	SDL_RenderPresent(renderer);
}

bool Start::running() {
	return isRunning;
}