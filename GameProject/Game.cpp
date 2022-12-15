#include <iostream>
#include <vector>

#include "Attack_path.h"
#include "SDL.h"
#include "attackerObject.h"
#include "block.h"
#include "defenderObject.h"

std::vector<defenderObject *> defender_list;
std::vector<defenderObject *> defender_option;
std::vector<block *> defenderChoiceRegion;
std::vector<attackerObject *> attacker_list;
attackerObject *student1;
std::vector<block *> map;
AttackPath *path;
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

	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 0), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(21, 0), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 1), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(21, 1), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 2), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(21, 2), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 3), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(21, 3), 40, defenderOption));
	defender_option.push_back(new defenderObject("assets/Defender/defender1.png", renderer, 800, 0, 40, 40));
	defender_option.push_back(new defenderObject("assets/Defender/defender2.png", renderer, 840, 0, 40, 40));
	defender_option.push_back(new defenderObject("assets/Defender/truck.png", renderer, 800, 40, 80, 40));
	defender_option.push_back(new defenderObject("assets/Defender/NTULibrary.png", renderer, 800, 80, 80, 80));
	defender_list.push_back(new defenderObject("assets/Defender/BL_building_white.png", renderer, 600, 0, 120, 80));
	createMap();

	map[13]->setType(attackerOnIt);
	map[210]->setOcupied(true);
	map[211]->setOcupied(true);
	map[224]->setOcupied(true);
	map[225]->setOcupied(true);
	map[238]->setOcupied(true);
	map[239]->setOcupied(true);

	path = new AttackPath(14, 18);
	path->getInitialMap(map);
}

void Game::createMap() {
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 14; j++) {
			if (i == 2 || i == 3 || i == 6 || i == 7 || i == 10 || i == 11) {
				if (j == 2 || j == 3 || j == 6 || j == 7 || j == 10 || j == 11)
					map.push_back(new block(renderer, std::make_pair(i, j), 40, defenderOnly));
				else
					map.push_back(new block(renderer, std::make_pair(i, j), 40, attackerOnly));
			} else if (i == 14) {
				if (j == 3 || j == 6 || j == 7 || j == 10 || j == 11)
					map.push_back(new block(renderer, std::make_pair(i, j), 40, defenderOnly));
				else
					map.push_back(new block(renderer, std::make_pair(i, j), 40, attackerOnly));
			} else if (i == 15) {
				if (j == 0 || j == 1 || j == 6 || j == 7 || j == 10 || j == 11)
					map.push_back(new block(renderer, std::make_pair(i, j), 40, defenderOnly));
				else
					map.push_back(new block(renderer, std::make_pair(i, j), 40, attackerOnly));
			} else if (i == 16 || i == 17) {
				if (j == 0 || j == 1)
					map.push_back(new block(renderer, std::make_pair(i, j), 40, defenderOnly));
				else
					map.push_back(new block(renderer, std::make_pair(i, j), 40, attackerOnly));
			} else {
				map.push_back(new block(renderer, std::make_pair(i, j), 40, attackerOnly));
			}
		}
	}
}

void Game::update() {
	for (auto &i: defenderChoiceRegion) {
		i->Update();
	}
	for (auto &i: map) {
		i->Update();
	}
	for (auto &i: defender_option) {
		i->Update();
	}
	for (auto &i: attacker_list) {
		i->Update();
	}
	for (auto &i: defender_list) {
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
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		Uint32 MouseState = SDL_GetMouseState(&x, &y);
		if (x >= 800) {
			// click on defender option
			defenderChoiceRegion[0]->setMouseState(MouseState);
			defenderChoiceRegion[0]->setMouseX(x);
			defenderChoiceRegion[0]->setMouseY(y);
			for (int i = 0; i < defenderChoiceRegion.size(); i++) {
				if (block::mouseX - defenderChoiceRegion[i]->getDestX() < 40 && block::mouseX - defenderChoiceRegion[i]->getDestX() >= 0 && block::mouseY - defenderChoiceRegion[i]->getDestY() < 40 && block::mouseY - defenderChoiceRegion[i]->getDestY() >= 0) {
					if (defenderChoiceRegion[i]->getType() == defenderOption) {
						for (auto &j: defenderChoiceRegion) {
							j->setChosen(false);
							j->setType(defenderOption);
							setDefenderChosen(none);
						}
						if (block::mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
							if (i == 0) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[i]->setType(defenderChosen);
								defenderChoiceRegion[i]->setChosen(true);
								setDefenderChosen(defender1);
							} else if (i == 1) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[i]->setType(defenderChosen);
								defenderChoiceRegion[i]->setChosen(true);
								setDefenderChosen(defender2);
							} else if (i == 2 || i == 3) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[2]->setType(defenderChosen);
								defenderChoiceRegion[2]->setChosen(true);
								defenderChoiceRegion[3]->setType(defenderChosen);
								defenderChoiceRegion[3]->setChosen(true);
								setDefenderChosen(truck);
							} else if (i == 4 || i == 5 || i == 6 || i == 7) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[4]->setType(defenderChosen);
								defenderChoiceRegion[4]->setChosen(true);
								defenderChoiceRegion[5]->setType(defenderChosen);
								defenderChoiceRegion[5]->setChosen(true);
								defenderChoiceRegion[6]->setType(defenderChosen);
								defenderChoiceRegion[6]->setChosen(true);
								defenderChoiceRegion[7]->setType(defenderChosen);
								defenderChoiceRegion[7]->setChosen(true);
								setDefenderChosen(NTULibrary);
							}
						}
					}
				}
			}
		} else {
			int x, y;
			Uint32 MouseState = SDL_GetMouseState(&x, &y);
			map[0]->setMouseState(MouseState);
			map[0]->setMouseX(x);
			map[0]->setMouseY(y);
			for (auto &i: map) {
				if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
					cout << "mouse clicked" << endl;
					cout << i->getType() << endl;
					if (i->getType() == defenderOnIt) {
						if (i->isOcupied() == false) {
							if (chosenDefender == defender1) {
								defender_list.push_back(new defenderObject("assets/Defender/defender1.png", renderer, i->getDestX(), i->getDestY(), 40, 40));
								i->setOcupied(true);
								i->setType(defenderOnIt);
							} else if (chosenDefender == defender2) {
								defender_list.push_back(new defenderObject("assets/Defender/defender2.png", renderer, i->getDestX(), i->getDestY(), 40, 40));
								i->setOcupied(true);
								i->setType(defenderOnIt);
							}
						}
					}
				}
			}
		}

	} else if (event.type == SDL_MOUSEMOTION) {
		int x, y;
		Uint32 MouseState = SDL_GetMouseState(&x, &y);
		map[0]->setMouseState(MouseState);
		map[0]->setMouseX(x);
		map[0]->setMouseY(y);
		for (auto &i: map) {
			if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
				if (i->getType() == defenderOnly) {
					if (i->isOcupied() == false) {
						cout << chosenDefender << endl;
						i->setType(defenderOnIt);
					}
				}
			} else {
				if (i->getType() == defenderOnIt) {
					i->setType(defenderOnly);
				}
			}
		}
		// if (getDefenderChosen() != none) {
		// 	for (int i = 0; i < defenderChoiceRegion.size(); i++) {
		// 		if (block::mouseX - defenderChoiceRegion[i]->getDestX() < 40 && block::mouseX - defenderChoiceRegion[i]->getDestX() >= 0 && block::mouseY - defenderChoiceRegion[i]->getDestY() < 40 && block::mouseY - defenderChoiceRegion[i]->getDestY() >= 0) {
		// 			if (i == 0) {
		// 				defenderChoiceRegion[i]->setType(defenderChosen);
		// 			} else if (i == 1) {
		// 				defenderChoiceRegion[i]->setType(defenderChosen);
		// 			} else if (i == 2 || i == 3) {
		// 				defenderChoiceRegion[2]->setType(defenderChosen);
		// 				defenderChoiceRegion[3]->setType(defenderChosen);

		// 			} else if (i == 4 || i == 5 || i == 6 || i == 7) {
		// 				defenderChoiceRegion[4]->setType(defenderChosen);
		// 				defenderChoiceRegion[5]->setType(defenderChosen);
		// 				defenderChoiceRegion[6]->setType(defenderChosen);
		// 				defenderChoiceRegion[7]->setType(defenderChosen);
		// 			}
		// 		} else {
		// 			if (defenderChoiceRegion[i]->getType() == defenderChosen) {
		// 				defenderChoiceRegion[i]->setType(defenderOption);
		// 			}
		// 		}
		// 	}
		// }

	} else if (event.type == SDL_KEYDOWN) {
		// cout << "key pressed" << endl;
		switch (event.key.keysym.sym) {
			case SDLK_c:
				std::cout << "c pressed" << std::endl;
				path->restart();
				break;
		}
		if (path->is_path_end()) {
			for (auto &i: attacker_list) {
				if (i->isDead()) {
					i->setDestRectX(-100);
				}
			}
			// std::cout << "path end" << std::endl;
			switch (event.key.keysym.sym) {
				case SDLK_1:
					attacker_list.push_back(new attackerObject("assets/Attackers/student1.png", renderer, 0, 520));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;
				case SDLK_2:
					attacker_list.push_back(new attackerObject("assets/Attackers/student2.png", renderer, 0, 520));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;
				case SDLK_3:
					attacker_list.push_back(new attackerObject("assets/Attackers/student3.png", renderer, 0, 520));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;
				case SDLK_4:
					attacker_list.push_back(new attackerObject("assets/Attackers/student4.png", renderer, 0, 520));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;
			}

		} else {
			std::cout << "path not end" << std::endl;
			switch (event.key.keysym.sym) {
				case SDLK_w:
					std::cout << "w pressed" << std::endl;
					path->draw_path('U');
					break;
				case SDLK_a:
					std::cout << "a pressed" << std::endl;
					path->draw_path('L');
					break;
				case SDLK_s:
					std::cout << "s pressed" << std::endl;
					path->draw_path('D');
					break;
				case SDLK_d:
					std::cout << "d pressed" << std::endl;
					path->draw_path('R');
					break;
				default:
					break;
			}
			for (auto &i: map) {
				if (i->getType() == attackerOnIt || i->getType() == attackerOnly)
					i->setType(attackerOnly);
			}
			vector<pair<int, int>> path_list(path->get_path());
			for (auto &i: path_list) {
				for (auto &j: map) {
					if (j->getPos().first == i.second && j->getPos().second == i.first) {
						j->setType(attackerOnIt);
					}
				}
			}
			path_list.clear();
		}
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	for (auto &i: defenderChoiceRegion) {
		i->Render();
	}
	for (auto &i: map) {
		i->Render();
	}
	for (auto &i: defender_option) {
		i->Render();
	}
	for (auto &i: attacker_list) {
		i->Render();
	}
	for (auto &i: defender_list) {
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

defenderType Game::getDefenderChosen() {
	return chosenDefender;
}
void Game::setDefenderChosen(defenderType i) {
	chosenDefender = i;
}