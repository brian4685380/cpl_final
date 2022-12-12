#include <iostream>
#include <vector>

#include "SDL.h"
#include "attackerObject.h"
#include "block.h"

// vector<attacker> attacker_list;
// vector<defender> defender_list;
std::vector<attackerObject *> attacker_list;
attackerObject *student1;
std::vector<block *> map;
Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
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

		renderer = SDL_CreateRenderer(window, -1, 0);  // Render window
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		isRunning = true;
	} else {
		isRunning = false;
	}
	student1 = new attackerObject("assets/Attackers/student1.png", renderer, 50, 50);
	attacker_list.push_back(new attackerObject("assets/Attackers/student1.png", renderer, 0, 0));
	attacker_list.push_back(new attackerObject("assets/Attackers/student2.png", renderer, 50, 0));
	attacker_list.push_back(new attackerObject("assets/Attackers/student4.png", renderer, 100, 0));
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			if ((i & 1) * (j & 1))
				map.push_back(new block("assets/Blocks/redclay.png", renderer, std::make_pair(i, j), 40, attackerOnly));
			else
				map.push_back(new block("assets/Blocks/grass.png", renderer, std::make_pair(i, j), 40, attackerOnly));
		}
	}
}

void Game::update() {
	for (auto &i: attacker_list) {
		i->Update();
	}
	for (auto &i: map) {
		i->Update();
	}
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto &i: attacker_list) {
		i->Render();
	}
	for (auto &i: map) {
		i->Render();
	}
	// attacker_list[0]->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
bool Game::running() {
	return isRunning;
}