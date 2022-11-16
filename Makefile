game:
	g++ main.cpp -o play -I include -L lib -l SDL2-2.0.0 -l SDL_bgi -l SDL2_image
test:
	g++ test.cpp -o try -I include -L lib -l SDL2-2.0.0 -l SDL_bgi -l SDL2_image