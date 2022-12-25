#pragma once

#include "Text.h"
using namespace std;

Text::Text(int x, int y){
    textRect.x = x;
    textRect.y = y;
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

void Text::UpdateAndRender(SDL_Renderer *renderer){
    for (auto &i: text) {
		textSurface = TTF_RenderUTF8_Solid(font, i.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		textRect.y += fontHeight; 
	}
    textRect.y -= fontHeight * text.size();
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    return;
}

void Text::TextClean(){
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
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("生產力: 1塊/秒");
}
void Text::showDefender2Data() {
	text.clear();
	text.push_back("防守者2");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("生產力: 1塊/秒");
}
void Text::showDefender3Data() {
	text.clear();
	text.push_back("防守者3");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("生產力: 1塊/秒");
}
void Text::showDefender4Data() {
	text.clear();
	text.push_back("防守者4");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("生產力: 1塊/秒");
}
void Text::showAttackerData() {
	text.clear();
	text.push_back("攻擊者1");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("移動速度: 1");
	text.push_back("攻擊範圍: 1");
	text.push_back("攻擊者2");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("移動速度: 1");
	text.push_back("攻擊範圍: 1");
	text.push_back("攻擊者3");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("移動速度: 1");
	text.push_back("攻擊範圍: 1");
	text.push_back("攻擊者4");
	text.push_back("生命值: 100");
	text.push_back("攻擊力: 10");
	text.push_back("移動速度: 1");
	text.push_back("攻擊範圍: 1");
}

void Text::showSystemData(int attackerMoney, int defenderMoney, int remainTime) {
	text.clear();
	text.push_back("攻擊方金錢: " + std::to_string(attackerMoney));
	text.push_back("防守方金錢: " + std::to_string(defenderMoney));
	text.push_back("剩餘時間: " + std::to_string(remainTime));
}