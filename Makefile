game:
	g++ --std=c++14 main.cpp -o play -I include -L lib -l SDL2-2.0.0 -l SDL_bgi -l SDL2_image -l SDL2_ttf -l SDL2_mixer
test:
	g++ --std=c++14 test.cpp -o try -I include -L lib -l SDL2-2.0.0 -l SDL_bgi -l SDL2_image -l SDL2_ttf -l SDL2_mixer
