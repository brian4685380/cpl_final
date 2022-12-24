#include "Music.h"
#include <iostream>
using namespace std;

Music::Music(){}
Music::~Music(){}

void Music::MusicLoad(){
    M_bgm = Mix_LoadMUS("assets/SoundEffect/BackgroundMusic/Pixel-Peeker-Polka-faster.mp3");
	
	M_A_summon = Mix_LoadWAV("assets/SoundEffect/AttackerObject/Summon.mp3");
	M_A_dead = Mix_LoadWAV("assets/SoundEffect/AttackerObject/Dead.mp3");

	M_D_build = Mix_LoadWAV("assets/SoundEffect/DefenderObject/Build.mp3");
	M_D_dead = Mix_LoadWAV("assets/SoundEffect/DefenderObject/Dead.mp3");
	M_D_select = Mix_LoadWAV("assets/SoundEffect/DefenderObject/Select.mp3");

	M_noMoney = Mix_LoadWAV("assets/SoundEffect/AttackerObject/noMoney.mp3");

	M_buildPath = Mix_LoadWAV("assets/SoundEffect/AttackerPath/buildPath.mp3");
	M_clearPath = Mix_LoadWAV("assets/SoundEffect/AttackerPath/clearPath.mp3");
	M_completePath = Mix_LoadWAV("assets/SoundEffect/AttackerPath/completePath.mp3");
}

void Music::MusicClean(){

	Mix_FreeMusic(M_bgm);

	Mix_FreeChunk(M_A_summon);
	Mix_FreeChunk(M_A_dead);

	Mix_FreeChunk(M_D_build);
	Mix_FreeChunk(M_D_dead);
	Mix_FreeChunk(M_D_select);

	Mix_FreeChunk(M_noMoney);

	Mix_FreeChunk(M_buildPath);
	Mix_FreeChunk(M_clearPath);
	Mix_FreeChunk(M_completePath);

	M_bgm = nullptr;

	M_A_summon = nullptr;
	M_A_dead = nullptr;

	M_D_build = nullptr;
	M_D_dead = nullptr;
	M_D_select = nullptr;

	M_noMoney = nullptr;

	M_buildPath = nullptr;
	M_clearPath = nullptr;
	M_completePath = nullptr;
}

void Music::Play_bgm(){
    Mix_PlayMusic(M_bgm, -1);	// the second parameter means how many times we want to loop it (-1 means infinity);
	return;
}
void Music::Play_A_summon(){
    Mix_PlayChannel(-1, M_A_summon, 0);
	return;
}

void Music::Play_A_dead(){
	Mix_PlayChannel(-1, M_A_dead, 0);
	return;
}
void Music::Play_D_build(){
	Mix_PlayChannel(-1, M_D_build, 0);
	return;
}
void Music::Play_D_dead(){
	Mix_PlayChannel(-1, M_D_dead, 0);
	return;
}
void Music::Play_D_select(){
	Mix_PlayChannel(-1, M_D_select, 0);
	return;
}
void Music::Play_noMoney(){
	Mix_PlayChannel(-1, M_noMoney, 0);
	return;
}
void Music::Play_buildPath(){
	Mix_PlayChannel(-1, M_buildPath, 0);
	return;
}
void Music::Play_clearPath(){
	Mix_PlayChannel(-1, M_clearPath, 0);
	return;
}
void Music::Play_completePath(){
	Mix_PlayChannel(-1, M_completePath, 0);
	return;
}