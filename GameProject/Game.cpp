#include <algorithm>
#include <iostream>
#include <vector>

#include "Attack_path.h"
#include "Money.h"
#include "Music.h"
#include "SDL.h"
#include "Text.h"
#include "Timer.h"
#include "attackerObject.h"
#include "block.h"
#include "defenderObject.h"

std::vector<int> leftupCorner = {30, 34, 38, 86, 90, 94, 142, 146, 150, 202, 206};
std::vector<int> leftdownCorner = {31, 35, 39, 87, 91, 95, 143, 147, 151, 203, 207};
std::vector<int> rightupCorner = {44, 48, 52, 100, 104, 108, 156, 160, 164, 216, 220};
std::vector<int> rightdownCorner = {45, 49, 53, 101, 105, 109, 157, 161, 165, 217, 221};
std::vector<defenderObject *> defender_list;
std::vector<defenderObject *> defender_option;
std::vector<block *> defenderChoiceRegion;
std::vector<attackerObject *> attacker_list;
attackerObject *student1;
std::vector<block *> map;
AttackPath *path;
Timer *gameTimer;
int gameTimerCount = 1;
Money *attackerMoney;
Money *defenderMoney;
int A_id = 0;  // Attacker id
int D_id = 0;  // Defender id

// Music;
Music *gameMusic;
bool playCompletePathMusic = false;

// Text
Text *attackerMoneyText = nullptr;
Text *defenderMoneyText = nullptr;
Text *timerText = nullptr;
Text *attackerText = nullptr;
Text *defenderText = nullptr;
Text *defender1Data = nullptr;
Text *defender2Data = nullptr;
Text *defender3Data = nullptr;
Text *defender4Data = nullptr;
Text *attacker1Data = nullptr;
Text *attacker2Data = nullptr;
Text *attacker3Data = nullptr;
Text *attacker4Data = nullptr;
Text *BL_heart = nullptr;
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

		// Render window
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}

		// SDL Mixer (Musics and sounds)
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			cout << "SDL_mixer could not initialize!" << endl;
		}

		// SDL ttf
		if (TTF_Init() < 0) {
			cout << "SDL_ttf could not initialize!" << endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(19, 0), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 0), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(19, 1), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 1), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(19, 2), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 2), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(19, 3), 40, defenderOption));
	defenderChoiceRegion.push_back(new block(renderer, std::make_pair(20, 3), 40, defenderOption));
	defender_option.push_back(new defenderObject(renderer, 760, 0, 40, 40, 0, Prof1));
	defender_option.push_back(new defenderObject(renderer, 800, 0, 40, 40, 0, Prof2));
	defender_option.push_back(new defenderObject(renderer, 760, 40, 80, 40, 0, Bike));
	defender_option.push_back(new defenderObject(renderer, 760, 80, 80, 80, 0, Library));
	defender_list.push_back(new defenderObject(renderer, 600, 0, 120, 80, 0, Home));

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

	// Timer
	gameTimer = new Timer(10000000);

	// Money
	attackerMoney = new Money(10000);
	defenderMoney = new Money(10000);

	for (auto &i: defender_option) {
		i->Update(attackerMoney, defenderMoney, gameMusic);
	}

	// Music
	gameMusic = new Music;
	gameMusic->MusicLoad();

	// Start playing music
	gameMusic->Play_bgm();

	// Text
	attackerText = new Text(0, 560, 20);
	defenderText = new Text(320, 560, 20);
	attackerMoneyText = new Text(855, 17, 20);
	defenderMoneyText = new Text(990, 17, 20);
	timerText = new Text(910, 105, 30);
	BL_heart = new Text(960, 210, 30);
	attacker1Data = new Text(770, 330, 15);
	attacker2Data = new Text(850, 330, 15);
	attacker3Data = new Text(930, 330, 15);
	attacker4Data = new Text(1010, 330, 15);
	defender1Data = new Text(770, 490, 15);
	defender2Data = new Text(850, 490, 15);
	defender3Data = new Text(930, 490, 15);
	defender4Data = new Text(1010, 490, 15);

	defenderText->showDefendingHint();
	attackerText->showDrawingHint();
	defender1Data->showDefender1Data();
	defender2Data->showDefender2Data();
	defender3Data->showDefender3Data();
	defender4Data->showDefender4Data();
	attacker1Data->showAttacker1Data();
	attacker2Data->showAttacker2Data();
	attacker3Data->showAttacker3Data();
	attacker4Data->showAttacker4Data();

	moneyTexture = IMG_LoadTexture(renderer, "assets/backgrounds/money.png");
	timeTexture = IMG_LoadTexture(renderer, "assets/backgrounds/clock.png");
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Blocks/redclay.png");
	BL_bloodTexture = IMG_LoadTexture(renderer, "assets/backgrounds/blood.png");
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
	// for (auto &i: map) {
	// 	bool check = false;
	// 	for (auto &j: defender_list) {
	// 		if (i->getDestX() == j->getDestX() && i->getDestY() == j->getDestY()) {
	// 			check = true;
	// 			break;
	// 		}
	// 	}
	// 	if (check == false) {
	// 		i->setOcupied(false);
	// 	}
	// }

	for (auto &i: map) {
		i->setOcupied(false);

		for (auto &j: defender_list) {
			if (i->isOcupied()) {
				break;
			}
			switch (j->D_get_type()) {
				case Prof1:
				case Prof2:
					if (i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get()) {
						i->setOcupied(true);
						break;
					}
					break;
				case Bike:
					if ((i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() + 40 && i->getDestY() == j->D_ypos_get())) {
						i->setOcupied(true);
						break;
					}
					break;
				case Library:
					if ((i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() + 40 && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get() + 40) ||
						(i->getDestX() == j->D_xpos_get() + 40 && i->getDestY() == j->D_ypos_get() + 40)) {
						i->setOcupied(true);
						break;
					}
					break;
				case Home:
					if ((i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() + 40 && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() + 80 && i->getDestY() == j->D_ypos_get()) ||
						(i->getDestX() == j->D_xpos_get() && i->getDestY() == j->D_ypos_get() + 40) ||
						(i->getDestX() == j->D_xpos_get() + 40 && i->getDestY() == j->D_ypos_get() + 40) ||
						(i->getDestX() == j->D_xpos_get() + 80 && i->getDestY() == j->D_ypos_get() + 40)) {
						i->setOcupied(true);
						break;
					}
					break;
				default:
					break;
			}
		}
	}

	for (auto &i: defenderChoiceRegion) {
		i->Update();
	}
	for (auto &i: map) {
		i->Update();
	}
	for (auto &i: attacker_list) {
		i->Update(gameMusic);
	}
	for (auto &i: defender_list) {
		i->Update(attackerMoney, defenderMoney, gameMusic);
	}

	// Attacker attack

	for (auto &i: attacker_list) {
		i->A_Attack(defender_list);
	}

	// Defender attack
	for (auto &i: defender_list) {
		i->D_Attack(attacker_list);
	}

	// // Money
	// *attackerMoney += 1;
	// *defenderMoney += 1;

	// Timer update
	gameTimer->timer_update();
	timerText->showNumber(gameTimer->get_left_s());
	attackerMoneyText->showNumber(attackerMoney->money_get());
	defenderMoneyText->showNumber(defenderMoney->money_get());
	if (gameTimer->get_elapsed_ms() >= 10 * gameTimerCount) {
		gameTimerCount++;
		// cout << "Game Time : " << gameTimer->get_elapsed_s() << endl;

		// Money update
		//*attackerMoney += 1;
		//*defenderMoney += 1;
		// cout << "attacker money : " << attackerMoney->money_get() << endl;
		// cout << "defender money : " << defenderMoney->money_get() << endl;
	}
	if (gameTimer->is_time_up()) {
		winner = defenderPlayer;
	}
	if (defender_list[0]->D_is_dead()) {
		winner = attackerPlayer;
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
		if (x >= 720) {
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
							gameMusic->Play_D_select();
							if (i == 0) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[i]->setType(defenderChosen);
								defenderChoiceRegion[i]->setChosen(true);
								setDefenderChosen(defender1);
								defenderText->showDefender1Data();
							} else if (i == 1) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[i]->setType(defenderChosen);
								defenderChoiceRegion[i]->setChosen(true);
								setDefenderChosen(defender2);
								defenderText->showDefender2Data();
							} else if (i == 2 || i == 3) {
								std::cout << "clicked" << std::endl;
								defenderChoiceRegion[2]->setType(defenderChosen);
								defenderChoiceRegion[2]->setChosen(true);
								defenderChoiceRegion[3]->setType(defenderChosen);
								defenderChoiceRegion[3]->setChosen(true);
								setDefenderChosen(truck);
								defenderText->showDefender3Data();
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
								defenderText->showDefender4Data();
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
								defenderText->showDefender1Data();
								if (defenderMoney->money_get() < defenderObject::D_get_price(Prof1)) {
									gameMusic->Play_noMoney();
									cout << "Defender not have enough money" << endl;
									defenderText->noMoney();
									break;
								}

								gameMusic->Play_D_build();
								*defenderMoney -= defenderObject::D_get_price(Prof1);
								cout << "Defender's money : " << defenderMoney->money_get() << endl;
								defenderMoneyText->showNumber(defenderMoney->money_get());
								D_id++;
								defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY(), 40, 40, D_id, Prof1));
								i->setOcupied(true);
								i->setType(defenderOnIt);
							} else if (chosenDefender == defender2) {
								defenderText->showDefender2Data();
								if (defenderMoney->money_get() < defenderObject::D_get_price(Prof2)) {
									gameMusic->Play_noMoney();
									cout << "Defender not have enough money" << endl;
									defenderText->noMoney();
									break;
								}

								gameMusic->Play_D_build();
								*defenderMoney -= defenderObject::D_get_price(Prof2);
								cout << "Defender's money : " << defenderMoney->money_get() << endl;
								defenderMoneyText->showNumber(defenderMoney->money_get());

								D_id++;
								defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY(), 40, 40, D_id, Prof2));
								i->setOcupied(true);
								i->setType(defenderOnIt);
							} else if (chosenDefender == truck) {
								defenderText->showDefender3Data();
								int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
								corner currentCorner = getCorner(idx);
								std::cout << "idx = " << idx << std::endl;
								std::cout << "current corner: " << currentCorner << std::endl;
								switch (currentCorner) {
									case rightUp:
										if (map[idx - 14]->isOcupied() == true) {
											cout << "can't place" << endl;
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Bike)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Bike);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());
											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX() - 40, i->getDestY(), 80, 40, D_id, Bike));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx - 14]->setOcupied(true);
											map[idx - 14]->setType(defenderOnIt);
										}
										break;
									case leftUp:
										if (map[idx + 14]->isOcupied() == true) {
											cout << "can't place" << endl;

										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Bike)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Bike);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY(), 80, 40, D_id, Bike));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx + 14]->setOcupied(true);
											map[idx + 14]->setType(defenderOnIt);
										}
										break;
									case rightDown:
										if (map[idx - 14]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Bike)) {
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												gameMusic->Play_noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Bike);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX() - 40, i->getDestY(), 80, 40, D_id, Bike));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx - 14]->setOcupied(true);
											map[idx - 14]->setType(defenderOnIt);
										}
										break;
									case leftDown:
										if (map[idx + 14]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Bike)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Bike);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY(), 80, 40, D_id, Bike));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx + 14]->setOcupied(true);
											map[idx + 14]->setType(defenderOnIt);
										}
										break;

									default:
										break;
								}
							} else if (chosenDefender == NTULibrary) {
								defenderText->showDefender4Data();
								int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
								corner currentCorner = getCorner(idx);
								std::cout << "idx = " << idx << std::endl;
								std::cout << "current corner: " << currentCorner << std::endl;
								switch (currentCorner) {
									case rightUp:
										if (map[idx - 14]->isOcupied() == true || map[idx - 13]->isOcupied() == true || map[idx + 1]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Library)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Library);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX() - 40, i->getDestY(), 80, 80, D_id, Library));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx - 14]->setOcupied(true);
											map[idx - 14]->setType(defenderOnIt);
											map[idx - 13]->setOcupied(true);
											map[idx - 13]->setType(defenderOnIt);
											map[idx + 1]->setOcupied(true);
											map[idx + 1]->setType(defenderOnIt);
										}
										break;
									case leftUp:
										if (map[idx + 14]->isOcupied() == true || map[idx + 15]->isOcupied() == true || map[idx + 1]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Library)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Library);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY(), 80, 80, D_id, Library));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx + 14]->setOcupied(true);
											map[idx + 14]->setType(defenderOnIt);
											map[idx + 15]->setOcupied(true);
											map[idx + 15]->setType(defenderOnIt);
											map[idx + 1]->setOcupied(true);
											map[idx + 1]->setType(defenderOnIt);
										}
										break;
									case rightDown:
										if (map[idx - 14]->isOcupied() == true || map[idx - 15]->isOcupied() == true || map[idx - 1]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Library)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Library);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX() - 40, i->getDestY() - 40, 80, 80, D_id, Library));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx - 14]->setOcupied(true);
											map[idx - 14]->setType(defenderOnIt);
											map[idx - 15]->setOcupied(true);
											map[idx - 15]->setType(defenderOnIt);
											map[idx - 1]->setOcupied(true);
											map[idx - 1]->setType(defenderOnIt);
										}
										break;
									case leftDown:
										if (map[idx + 14]->isOcupied() == true || map[idx + 13]->isOcupied() == true || map[idx - 1]->isOcupied() == true) {
											cout << "can't place" << endl;
											defenderText->cannotPlace();
										} else {
											if (defenderMoney->money_get() < defenderObject::D_get_price(Library)) {
												gameMusic->Play_noMoney();
												cout << "Defender not have enough money" << endl;
												defenderText->noMoney();
												break;
											}

											gameMusic->Play_D_build();
											*defenderMoney -= defenderObject::D_get_price(Library);
											cout << "Defender's money : " << defenderMoney->money_get() << endl;
											defenderMoneyText->showNumber(defenderMoney->money_get());

											D_id++;
											defender_list.push_back(new defenderObject(renderer, i->getDestX(), i->getDestY() - 40, 80, 80, D_id, Library));
											i->setOcupied(true);
											i->setType(defenderOnIt);
											map[idx + 14]->setOcupied(true);
											map[idx + 14]->setType(defenderOnIt);
											map[idx + 13]->setOcupied(true);
											map[idx + 13]->setType(defenderOnIt);
											map[idx - 1]->setOcupied(true);
											map[idx - 1]->setType(defenderOnIt);
										}
										break;

									default:
										break;
								}
							}
						}
					}
				}
			}
		}

	} else if (event.type == SDL_MOUSEMOTION) {
		// return the unocuppied block to normal

		int x, y;
		Uint32 MouseState = SDL_GetMouseState(&x, &y);
		map[0]->setMouseState(MouseState);
		map[0]->setMouseX(x);
		map[0]->setMouseY(y);
		for (auto &i: map) {
			if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
				if (i->getType() == defenderOnly) {
					if (chosenDefender == defender1 || chosenDefender == defender2) {
						if (i->isOcupied() == false) {
							cout << chosenDefender << endl;
							i->setType(defenderOnIt);
						}
					} else if (chosenDefender == truck) {
						int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
						corner currentCorner = getCorner(idx);
						std::cout << "idx = " << idx << std::endl;
						std::cout << "current corner: " << currentCorner << std::endl;
						switch (currentCorner) {
							case leftUp:
								if (i->isOcupied() == true || map[idx + 14]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx + 14]->setType(defenderOnIt);
								}
								break;
							case rightUp:
								if (i->isOcupied() == true || map[idx - 14]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx - 14]->setType(defenderOnIt);
								}
								break;
							case rightDown:
								if (i->isOcupied() == true || map[idx - 14]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx - 14]->setType(defenderOnIt);
								}
								break;
							case leftDown:
								if (i->isOcupied() == true || map[idx + 14]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx + 14]->setType(defenderOnIt);
								}
								break;
							default:
								break;
						}
					} else if (chosenDefender == NTULibrary) {
						int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
						corner currentCorner = getCorner(idx);
						std::cout << "idx = " << idx << std::endl;
						std::cout << "current corner: " << currentCorner << std::endl;
						switch (currentCorner) {
							case leftUp:
								if (i->isOcupied() == true || map[idx + 14]->isOcupied() == true || map[idx + 1]->isOcupied() == true || map[idx + 15]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx + 14]->setType(defenderOnIt);
									map[idx + 1]->setType(defenderOnIt);
									map[idx + 15]->setType(defenderOnIt);
								}
								break;
							case rightUp:
								if (i->isOcupied() == true || map[idx - 14]->isOcupied() == true || map[idx + 1]->isOcupied() == true || map[idx - 13]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx - 14]->setType(defenderOnIt);
									map[idx + 1]->setType(defenderOnIt);
									map[idx - 13]->setType(defenderOnIt);
								}
								break;
							case rightDown:
								if (i->isOcupied() == true || map[idx - 14]->isOcupied() == true || map[idx - 1]->isOcupied() == true || map[idx - 15]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx - 14]->setType(defenderOnIt);
									map[idx - 1]->setType(defenderOnIt);
									map[idx - 15]->setType(defenderOnIt);
								}
								break;
							case leftDown:
								if (i->isOcupied() == true || map[idx + 14]->isOcupied() == true || map[idx - 1]->isOcupied() == true || map[idx + 13]->isOcupied() == true) {
									cout << "can't place here" << endl;
									defenderText->cannotPlace();
								} else {
									i->setType(defenderOnIt);
									map[idx + 14]->setType(defenderOnIt);
									map[idx - 1]->setType(defenderOnIt);
									map[idx + 13]->setType(defenderOnIt);
								}
								break;
							default:
								break;
						}
					}
				}
			} else {
				if (chosenDefender == defender1 || chosenDefender == defender2) {
					if (i->getType() == defenderOnIt) {
						i->setType(defenderOnly);
					}
				} else if (chosenDefender == truck) {
					int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
					corner currentCorner = getCorner(idx);
					switch (currentCorner) {
						case leftUp:
							if (block::mouseX - i->getDestX() < 80 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case rightUp:
							if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= -40 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case leftDown:
							if (block::mouseX - i->getDestX() < 80 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case rightDown:
							if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= -40 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						default:
							break;
					}
				} else if (chosenDefender == NTULibrary) {
					int idx = i->getDestX() / 40 * 14 + i->getDestY() / 40;
					corner currentCorner = getCorner(idx);
					switch (currentCorner) {
						case leftUp:
							if (block::mouseX - i->getDestX() < 80 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 80 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case rightUp:
							if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= -40 && block::mouseY - i->getDestY() < 80 && block::mouseY - i->getDestY() >= 0) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case leftDown:
							if (block::mouseX - i->getDestX() < 80 && block::mouseX - i->getDestX() >= 0 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= -40) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
							break;
						case rightDown:
							if (block::mouseX - i->getDestX() < 40 && block::mouseX - i->getDestX() >= -40 && block::mouseY - i->getDestY() < 40 && block::mouseY - i->getDestY() >= -40) {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnIt);
								}
							} else {
								if (i->getType() == defenderOnIt) {
									i->setType(defenderOnly);
								}
							}
						default:
							break;
					}
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
				gameMusic->Play_clearPath();
				playCompletePathMusic = false;
				// std::cout << "c pressed" << std::endl;
				attackerText->showDrawingHint();
				path->restart();
				break;
		}
		if (path->is_path_end()) {
			// std::cout << "path end" << std::endl;
			attackerText->showAttackingHint();
			switch (event.key.keysym.sym) {
				case SDLK_1:
					if (attackerMoney->money_get() < attackerObject::A_get_price(Attacker1)) {
						gameMusic->Play_noMoney();
						cout << "Attacker not having enough money" << endl;
						attackerText->noMoney();
						break;
					}
					*attackerMoney -= attackerObject::A_get_price(Attacker1);
					cout << "Attacker's money : " << attackerMoney->money_get() << endl;
					attackerText->showNumber(attackerMoney->money_get());
					gameMusic->Play_A_summon();
					A_id++;
					// cout << "1 pressed" << endl;
					attackerText->showAttacker1Data();
					attacker_list.push_back(new attackerObject(renderer, 0, 520, A_id, Attacker1));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;

				case SDLK_2:
					if (attackerMoney->money_get() < attackerObject::A_get_price(Attacker2)) {
						gameMusic->Play_noMoney();
						cout << "Attacker not having enough money" << endl;
						attackerText->noMoney();
						break;
					}
					*attackerMoney -= attackerObject::A_get_price(Attacker2);
					cout << "Attacker's money : " << attackerMoney->money_get() << endl;
					attackerText->showNumber(attackerMoney->money_get());

					gameMusic->Play_A_summon();
					A_id++;
					// cout << "2 pressed" << endl;
					attackerText->showAttacker2Data();
					attacker_list.push_back(new attackerObject(renderer, 0, 520, A_id, Attacker2));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;

				case SDLK_3:
					if (attackerMoney->money_get() < attackerObject::A_get_price(Attacker3)) {
						gameMusic->Play_noMoney();
						cout << "Attacker not having enough money" << endl;
						attackerText->noMoney();
						break;
					}
					*attackerMoney -= attackerObject::A_get_price(Attacker3);
					cout << "Attacker's money : " << attackerMoney->money_get() << endl;
					attackerText->showNumber(attackerMoney->money_get());

					gameMusic->Play_A_summon();
					A_id++;
					// cout << "3 pressed" << endl;
					attackerText->showAttacker3Data();
					attacker_list.push_back(new attackerObject(renderer, 0, 520, A_id, Attacker3));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;

				case SDLK_4:
					if (attackerMoney->money_get() < attackerObject::A_get_price(Attacker4)) {
						gameMusic->Play_noMoney();
						cout << "Attacker not having enough money" << endl;
						attackerText->noMoney();
						break;
					}
					*attackerMoney -= attackerObject::A_get_price(Attacker4);
					cout << "Attacker's money : " << attackerMoney->money_get() << endl;
					attackerText->showNumber(attackerMoney->money_get());

					gameMusic->Play_A_summon();
					A_id++;
					// cout << "4 pressed" << endl;
					attackerText->showAttacker4Data();
					attacker_list.push_back(new attackerObject(renderer, 0, 520, A_id, Attacker4));
					attacker_list[attacker_list.size() - 1]->getAttackerPath(path->get_path());
					attacker_list[attacker_list.size() - 1]->getAttackerDir(path->get_dir());
					break;
			}

		} else {
			switch (event.key.keysym.sym) {
				case SDLK_w:
					gameMusic->Play_buildPath();
					std::cout << "w pressed" << std::endl;
					path->draw_path('U');
					if (path->is_path_end() && playCompletePathMusic == false) {
						gameMusic->Play_completePath();
						playCompletePathMusic = true;
					}
					break;
				case SDLK_a:
					gameMusic->Play_buildPath();
					std::cout << "a pressed" << std::endl;
					path->draw_path('L');
					if (path->is_path_end() && playCompletePathMusic == false) {
						gameMusic->Play_completePath();
						playCompletePathMusic = true;
					}
					break;
				case SDLK_s:
					gameMusic->Play_buildPath();
					std::cout << "s pressed" << std::endl;
					path->draw_path('D');
					if (path->is_path_end() && playCompletePathMusic == false) {
						gameMusic->Play_completePath();
						playCompletePathMusic = true;
					}
					break;
				case SDLK_d:
					gameMusic->Play_buildPath();
					std::cout << "d pressed" << std::endl;
					path->draw_path('R');
					if (path->is_path_end() && playCompletePathMusic == false) {
						gameMusic->Play_completePath();
						playCompletePathMusic = true;
					}
					break;
				case SDLK_1:
				case SDLK_2:
				case SDLK_3:
				case SDLK_4:
					gameMusic->Play_noMoney();
					std::cout << "path not end" << std::endl;
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
	moneySrcRect = {0, 0, 240, 80};
	moneyDestRect = {840, 0, 240, 80};
	timeSrcRect = {0, 0, 240, 80};
	timeDestRect = {840, 80, 240, 80};
	backgroundSrcRect = {0, 0, 1080, 720};
	backgroundDestRect = {0, 0, 1080, 720};
	BL_bloodSrcRect = {0, 0, 320, 120};
	BL_bloodDestRect = {760, 160, 320, 120};

	SDL_RenderCopy(renderer, backgroundTexture, &backgroundSrcRect, &backgroundDestRect);
	SDL_RenderCopy(renderer, moneyTexture, &moneySrcRect, &moneyDestRect);
	SDL_RenderCopy(renderer, timeTexture, &timeSrcRect, &timeDestRect);
	SDL_RenderCopy(renderer, BL_bloodTexture, &BL_bloodSrcRect, &BL_bloodDestRect);
	if (winner != unassigned) {
		// render a 1080 * 720 image
		// clear all objects on the screen
		// show the winner
		SDL_RenderClear(renderer);
		defenderText->destroy();
		defenderText->UpdateAndRender(renderer);
		attackerText->destroy();
		attackerText->UpdateAndRender(renderer);
		attackerMoneyText->destroy();
		attackerMoneyText->UpdateAndRender(renderer);
		defenderMoneyText->destroy();
		defenderMoneyText->UpdateAndRender(renderer);
		timerText->destroy();
		timerText->UpdateAndRender(renderer);
		attacker1Data->destroy();
		attacker1Data->UpdateAndRender(renderer);
		attacker2Data->destroy();
		attacker2Data->UpdateAndRender(renderer);
		attacker3Data->destroy();
		attacker3Data->UpdateAndRender(renderer);
		attacker4Data->destroy();
		attacker4Data->UpdateAndRender(renderer);
		defender1Data->destroy();
		defender1Data->UpdateAndRender(renderer);
		defender2Data->destroy();
		defender2Data->UpdateAndRender(renderer);
		defender3Data->destroy();
		defender3Data->UpdateAndRender(renderer);
		defender4Data->destroy();
		defender4Data->UpdateAndRender(renderer);
		BL_heart->destroy();
		BL_heart->UpdateAndRender(renderer);
		
		for (auto &i: map) {
			i->destroy();
		}
		for (auto &i: defender_list) {
			i->destroy();
		}
		for (auto &i: attacker_list) {
			i->destroy();
		}
		for (auto &i: defender_option) {
			i->destroy();
		}
		for (auto &i: defenderChoiceRegion) {
			i->destroy();
		}

		if (winner == defenderPlayer) {
			resultTexture = IMG_LoadTexture(renderer, "assets/backgrounds/Defender Wins.png");
		} else if (winner == attackerPlayer) {
			resultTexture = IMG_LoadTexture(renderer, "assets/backgrounds/Challenger Wins.png");
		}
		SDL_RenderCopy(renderer, resultTexture, NULL, NULL);
	} else {
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
	}

	// Text
	if (gameTimer->get_left_ms() % 10 == 0) {
		defenderText->UpdateAndRender(renderer);
		attackerText->UpdateAndRender(renderer);
		defender1Data->UpdateAndRender(renderer);
		defender2Data->UpdateAndRender(renderer);
		defender3Data->UpdateAndRender(renderer);
		defender4Data->UpdateAndRender(renderer);
		attacker1Data->UpdateAndRender(renderer);
		attacker2Data->UpdateAndRender(renderer);
		attacker3Data->UpdateAndRender(renderer);
		attacker4Data->UpdateAndRender(renderer);
		timerText->UpdateAndRender(renderer);
		attackerMoneyText->UpdateAndRender(renderer);
		defenderMoneyText->UpdateAndRender(renderer);
		BL_heart->showNumber(defender_list[0]->D_heart_get());
		BL_heart->UpdateAndRender(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	gameMusic->MusicClean();

	// Text
	defenderText->TextClean();
	attackerText->TextClean();

	SDL_Quit();
	Mix_Quit();
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

void Game::gameEnd() {
	isRunning = false;
}

corner Game::getCorner(int x) {
	if (binary_search(leftupCorner.begin(), leftupCorner.end(), x))
		return leftUp;
	else if (binary_search(rightupCorner.begin(), rightupCorner.end(), x))
		return rightUp;
	else if (binary_search(leftdownCorner.begin(), leftdownCorner.end(), x))
		return leftDown;
	else if (binary_search(rightdownCorner.begin(), rightdownCorner.end(), x))
		return rightDown;
	else
		return notCorner;
}