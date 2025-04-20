#include "Board.hpp"

using namespace sf;

void Board::RenderBoard(RenderWindow& window) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int piecenum = board[i][j];
			if (piecenum != 0) { // empty square so not in map
				Sprite piece;
				piece.setTexture(piece2Image[piecenum]);
				piece.setPosition(boardCords[i][j].x, boardCords[i][j].y);
				// because it sets the origin to 0,0 (which is top left of sprite) it places the top left corner of the texture
				// at the pos we want to place it (so it is putting it in bottom right of squares). So we need to manually adjust
				// origin to middle of texture to have it placed in middle of square
				piece.setOrigin(piece.getLocalBounds().width / 2, piece.getLocalBounds().height / 2);
				piece.setScale(1.5, 1.5);
				window.draw(piece);
			}
		}
	}
}

Board::Board() {
	// create the map keys and values while loading images at the same time
	// also images courtesy of wikipedia
	piece2Image[1].loadFromFile("Chess_plt60.png");
	piece2Image[-1].loadFromFile("Chess_pdt60.png");
	piece2Image[2].loadFromFile("Chess_nlt60.png");
	piece2Image[-2].loadFromFile("Chess_ndt60.png");
	piece2Image[3].loadFromFile("Chess_blt60.png");
	piece2Image[-3].loadFromFile("Chess_bdt60.png");
	piece2Image[4].loadFromFile("Chess_rlt60.png");
	piece2Image[-4].loadFromFile("Chess_rdt60.png");
	piece2Image[5].loadFromFile("Chess_klt60.png");
	piece2Image[-5].loadFromFile("Chess_kdt60.png");
	piece2Image[6].loadFromFile("Chess_qlt60.png");
	piece2Image[-6].loadFromFile("Chess_qdt60.png");

}