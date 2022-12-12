#include <Game.h>

#include <utility>
enum blockType {
	attakerOnly,
	defenderOnly,
	both,
};
class block {
   public:
	block(const char *textureSheet, SDL_Renderer *ren, std::pair<int, int> pos, int length, blockType type);
	~block();
	std::pair<int, int> getPos();
	int getLength();
	blockType getType();

   private:
	std::pair<int, int> pos;  // left top corner
	int length;
	blockType type;
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer *renderer;
};