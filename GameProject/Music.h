#pragma once

#include "SDL_mixer.h"
#include <iostream>
using namespace std;

class Music{
private:
    //Music
    Mix_Music *M_bgm = nullptr;

    Mix_Chunk *M_A_summon = nullptr;
    Mix_Chunk *M_A_dead = nullptr;//

    Mix_Chunk *M_D_build = nullptr;
    Mix_Chunk *M_D_dead = nullptr;
    Mix_Chunk *M_D_select = nullptr;

    Mix_Chunk *M_noMoney = nullptr;

    Mix_Chunk *M_buildPath = nullptr;
    Mix_Chunk *M_clearPath = nullptr;
    Mix_Chunk *M_completePath = nullptr;

public:
    Music();
    ~Music();

    void MusicLoad();
    void MusicClean();
    void Play_bgm();
    void Play_A_summon();
    void Play_A_dead();
    void Play_D_build();
    void Play_D_dead();
    void Play_D_select();
    void Play_noMoney();
    void Play_buildPath();
    void Play_clearPath();
    void Play_completePath();


};