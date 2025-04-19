#include "Piece.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

struct Coordinates {
	int x;
	int y;
};

class Board {
public:
	Board();
private:
	std::string board[8][8] = {
		""
	};
	Coordinates boardLocations[8][8];
};