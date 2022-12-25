#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;

class Text {
   private:
	vector<string> text = {"DefaultText1", "DefaultText2"};
	TTF_Font *font = TTF_OpenFont("assets/Font/Cubic_11/fonts/ttf/Cubic_11_1.010_R.ttf", 24);
	// TTF_Font *font = TTF_OpenFont("assets/Font/dogica/TTF/dogica.ttf", 24);
	int fontHeight = TTF_FontHeight(font);
	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Surface *textSurface;
	SDL_Texture *textTexture;  // = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = {0, 0, 0, 0};

   public:
	Text(int, int, int);
	~Text(){};

	// void TextInit(SDL_Renderer *);
	// void TextUpdate(SDL_Renderer *);
	void UpdateAndRender(SDL_Renderer *);
	void TextClean();

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
	void showAttacker1Data();
    void showAttacker2Data();
    void showAttacker3Data();
    void showAttacker4Data();
    void noMoney();
    void cannotPlace();
    void showNumber(int);

    void destroy();
};