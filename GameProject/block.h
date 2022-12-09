#include <utility>
enum blockType {
	attakerOnly,
	defenderOnly,
	both,
};
class block {
   private:
	std::pair<int, int> pos;  // left top corner
	int length;
    blockType type;
   public:
    block(std::pair<int, int> pos, int length, blockType type);
    ~block();
    std::pair<int, int> getPos();
    int getLength();
    blockType getType();
};