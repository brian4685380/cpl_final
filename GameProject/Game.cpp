#include <iostream>
#include <vector>

#include "GameObject.h"
#include "SDL.h"

vector<attacker> attacker_list;
vector<defender> defender_list;
GameObject *player;
GameObject *enemy;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;	// Fullscreen or not
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {	//Init
		std::cout << "Subsystems Initialed!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);	//Create Window
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);	//Render window
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		isRunning = true;
	} 
	else {
		isRunning = false;
	}

	player = new GameObject("assets/player.png", renderer, 0, 0);
	enemy = new GameObject("assets/enemy.png", renderer, 50, 50);
}

void Game::update() {
	player->Update();
	enemy->Update();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
	
}

void Game::render() {
	SDL_RenderClear(renderer);
	player->Render();
	enemy->Render();
	std::cout << "rendering..." << std::endl;
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