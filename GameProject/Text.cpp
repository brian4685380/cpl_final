#pragma once

#include "Text.h"
using namespace std;

Text::Text(int x, int y, int size) {
	textRect.x = x;
	textRect.y = y;
	font = TTF_OpenFont("assets/Font/Cubic_11/fonts/ttf/Cubic_11_1.010_R.ttf", size);
	fontHeight = TTF_FontHeight(font);
}

// void Text::TextInit(SDL_Renderer *renderer){         // Redundant (equivalent to TextUpdate)

//     textSurface = TTF_RenderUTF8_Solid(font, text[0].c_str(), textColor);
//     textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

//     //todo textsurface = TTF_RenderUTF8_Solid(font, i.c_str(), textColor);
//     //textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     //SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
// 	SDL_FreeSurface(textSurface);
// 	textSurface = nullptr;

// }

// void Text::TextUpdate(SDL_Renderer *renderer){
//     for (auto &i: text) {
// 		textSurface = TTF_RenderUTF8_Solid(font, i.c_str(), textColor);
// 		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
// 		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
// 		// SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
// 		// textRect.y += fontHeight;
// 	}
//     // textRect.y -= fontHeight * text.size();

//     // for (auto &i: text) {
// 	// 	cout << i << endl;
// 	// }
//     return;
// }

void Text::UpdateAndRender(SDL_Renderer *renderer) {
	for (auto &i: text) {
		textSurface = TTF_RenderUTF8_Solid(font, i.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		textRect.y += fontHeight;
	}
	textRect.y -= fontHeight * text.size();
	// SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	return;
}

void Text::TextClean() {
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
}

void Text::showDrawingHint() {
	text.clear();
	text.push_back("按下WASD可繪製路徑");
	text.push_back("按下C鍵可清除路徑");
	text.push_back("WASD鍵亦可收回路徑");
}
void Text::overBorderHint() {
	text.clear();
	text.push_back("已超出邊界");
}
void Text::formRoundHint() {
	text.clear();
	text.push_back("不允許形成環");
}
void Text::nextPosInvalidHint() {
	text.clear();
	text.push_back("下一格是防守方的地盤");
}
void Text::showAttackingHint() {
	text.clear();
	text.push_back("按下數字1234可召喚新學生");
	text.push_back("");
}
void Text::showDefendingHint() {
	text.clear();
	text.push_back("用滑鼠選擇防守者");
}
void Text::showDefender1Data() {
	text.clear();
	text.push_back("防守者1");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("生產: 1");
	text.push_back("範圍: 1");
}
void Text::showDefender2Data() {
	text.clear();
	text.push_back("防守者2");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("生產: 1");
	text.push_back("範圍: 1");
}
void Text::showDefender3Data() {
	text.clear();
	text.push_back("防守者3");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("生產: 1");
	text.push_back("範圍: 1");
}
void Text::showDefender4Data() {
	text.clear();
	text.push_back("防守者4");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("生產: 1");
	text.push_back("範圍: 1");
}
void Text::showAttacker1Data() {
	text.clear();
	text.push_back("攻擊者1");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("速度: 1");
	text.push_back("範圍: 1");
}
void Text::showAttacker2Data() {
	text.clear();
	text.push_back("攻擊者2");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("速度: 1");
	text.push_back("範圍: 1");
}
void Text::showAttacker3Data() {
	text.clear();
	text.push_back("攻擊者3");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("速度: 1");
	text.push_back("範圍: 1");
}
void Text::showAttacker4Data() {
	text.clear();
	text.push_back("攻擊者4");
	text.push_back("生命: 100");
	text.push_back("攻擊: 10");
	text.push_back("速度: 1");
	text.push_back("範圍: 1");
}
void Text::noMoney() {
	text.clear();
	text.push_back("金錢不足");
}
void Text::showNumber(int num) {
	text.clear();
	text.push_back(to_string(num));
}
void Text::cannotPlace() {
	text.clear();
	text.push_back("此格已被佔用");
}

void Text::destroy() {
	// Destroy the texture
	textRect.x = -200;
	SDL_DestroyTexture(textTexture);
	// Destroy the texture
}