#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;

class Text {
   private:
	// Text
	SDL_Rect textRect = {0, 0, 0, 0};
	SDL_Surface *textSurface;
	SDL_Texture *textTexture;
	SDL_Color textColor = {0, 0, 0, 255};
	vector<string> text;
	TTF_Font *font = TTF_OpenFont("./GameProject/assets/Font/Cubic_11/fonts/ttf/Cubic_11_1.010_R.ttf", 24);
    

   public:
	SDL_Renderer *renderer = nullptr;
	Text(int, int);
	~Text();
	void Render(SDL_Renderer *renderer);
	void Update();
	void showDrawingHint();
	void overBorderHint();
	void formRoundHint();
	void nextPosInvalidHint();
	void showAttackingHint();
	void showDefendingHint();
	void showDefender1Data();
	void showDefender2Data();
	void showDefender3Data();
	void showDefender4Data();
	void showAttackerData();

	void showSystemData(int, int, int);
};