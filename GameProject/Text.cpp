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
	text.push_back("H教授");
	text.push_back("價格: 150");
	text.push_back("生命: 300");
	text.push_back("攻擊: 10");
	text.push_back("單體: 2");
	text.push_back("經濟: 2");
}
void Text::showDefender2Data() {
	text.clear();
	text.push_back("Y教授");
	text.push_back("價格:250");
	text.push_back("生命:400");
	text.push_back("攻擊:12");
	text.push_back("範圍:2");
	text.push_back("經濟:2");
}
void Text::showDefender3Data() {
	text.clear();
	text.push_back("水源阿杯");
	text.push_back("價格:550");
	text.push_back("生命:600");
	text.push_back("攻擊:20");
	text.push_back("單體:3");
	text.push_back("經濟:4");
}
void Text::showDefender4Data() {
	text.clear();
	text.push_back("總圖");
	text.push_back("價格:1000");
	text.push_back("生命:1200");
	text.push_back("攻擊:18");
	text.push_back("範圍:1");
	text.push_back("經濟:6");
}
void Text::showAttacker1Data() {
	text.clear();
	text.push_back("大一鮮肝");
	text.push_back("價格:75");
	text.push_back("生命:120");
	text.push_back("攻擊:10");
	text.push_back("單體:2");
	text.push_back("速度:1");
}
void Text::showAttacker2Data() {
	text.clear();
	text.push_back("大二猴");
	text.push_back("價格:150");
	text.push_back("生命:180");
	text.push_back("攻擊:12");
	text.push_back("範圍:2");
	text.push_back("速度:2");
}
void Text::showAttacker3Data() {
	text.clear();
	text.push_back("大三老人");
	text.push_back("價格:400");
	text.push_back("生命:600");
	text.push_back("攻擊:15");
	text.push_back("單體:1");
	text.push_back("速度:4");
}
void Text::showAttacker4Data() {
	text.clear();
	text.push_back("大四已去");
	text.push_back("價格:700");
	text.push_back("生命:1000");
	text.push_back("攻擊:20");
	text.push_back("範圍:1");
	text.push_back("速度:1");
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
	textRect.x = -500;
	SDL_DestroyTexture(textTexture);
	// Destroy the texture
}