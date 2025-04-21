#include "Board.hpp"

using namespace sf;

Board::Board() {
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

void Board::RenderBoard(RenderWindow& window) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piecenum = board[i][j];
            if (piecenum != 0) {
                Sprite piece;
                piece.setTexture(piece2Image[piecenum]);
                piece.setPosition(boardCords[i][j].x, boardCords[i][j].y);
                piece.setOrigin(piece.getLocalBounds().width / 2, piece.getLocalBounds().height / 2);
                piece.setScale(1.5, 1.5);
                window.draw(piece);
            }
        }
    }

    for (auto move : possibleMoves) {
        RectangleShape highlight(Vector2f(100.f, 100.f)); // size of the square
        highlight.setFillColor(Color(128, 0, 128, 100));  // purple with transparency
        highlight.setOrigin(highlight.getSize().x / 2, highlight.getSize().y / 2);
        highlight.setPosition(boardCords[move.y][move.x].x, boardCords[move.y][move.x].y);
        window.draw(highlight);
    }
}

void Board::handleClick(int mouseX, int mouseY) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int bx = boardCords[j][i].x;
            int by = boardCords[j][i].y;
            if (abs(bx - mouseX) < 50 && abs(by - mouseY) < 50) {
                if (!pieceSelected && board[j][i] != 0) {
                    selectedX = i;
                    selectedY = j;
                    pieceSelected = true;
                    int type = abs(board[j][i]);
                    Piece* piece = nullptr;
                    switch (type) {
                    case 1: piece = new Pawn(); break;
                    case 2: piece = new Knight(); break;
                    case 3: piece = new Bishop(); break;
                    case 4: piece = new Rook(); break;
                    case 5: piece = new King(); break;
                    case 6: piece = new Queen(); break;
                    }
                    if (piece)
                        possibleMoves = piece->getAllPossibleMoves({ i, j }, board);
                }
                else if (pieceSelected) {
                    for (auto move : possibleMoves) {
                        if (move.x == i && move.y == j) {
                            board[j][i] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = 0;
                            break;
                        }
                    }
                    pieceSelected = false;
                    possibleMoves.clear();
                }
                return;
            }
        }
    }
}
