#include "Board.hpp"

using namespace sf;

void Board::RenderBoard(RenderWindow& window) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piecenum = board[i][j];
            if (piecenum != 0) {
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

    // puprle guide for possible moves for each piece
    for (auto move : possibleMoves) {
        RectangleShape highlight(Vector2f(100.f, 100.f)); 
        highlight.setFillColor(Color(128, 0, 128, 100));  
        highlight.setOrigin(highlight.getSize().x / 2, highlight.getSize().y / 2);
        highlight.setPosition(boardCords[move.y][move.x].x, boardCords[move.y][move.x].y);
        window.draw(highlight);
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

void Board::handleClick(int mouseX, int mouseY) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            int bx = boardCords[j][i].x;
            int by = boardCords[j][i].y;

           // this checls the coordinates of the mouse cursor if its within a certain square. [0-50] from the origin 
            if (abs(bx - mouseX) < 50 && abs(by - mouseY) < 50) {

                if (!pieceSelected && board[j][i] != 0 && (board[j][i] * turn > 0))  {

                    selectedX = i;
                    selectedY = j;
                    pieceSelected = true;

                    // what piece is in the square?
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

                    if (piece) {
                        possibleMoves = piece->getAllPossibleMoves({ i, j }, board);
                        // go through all moves, if they do not result in check, then it is legal move.
                        std::vector<Pair> actualPossibleMoves;
                        for (auto move : possibleMoves) {
                            // simulating whether a move results in check
                            int temp = board[move.y][move.x];
                            board[move.y][move.x] = board[j][i];
                            board[j][i] = 0;
                            if (!check(turn)) actualPossibleMoves.push_back(move);
                            board[j][i] = board[move.y][move.x];
                            board[move.y][move.x] = temp;
                        }
                        // only allow moves that do not result in check
                        possibleMoves = actualPossibleMoves;
                    }
                }

                // valid move checking. if yes, piece moves to designated quare user wants.
                else if (pieceSelected) {
                    for (auto move : possibleMoves) {
                        if (move.x == i && move.y == j) {

                            board[j][i] = board[selectedY][selectedX];
                            board[selectedY][selectedX] = 0;
                            turn *= -1;
                            if (turn == 1) std::cout << "White turn";
                            else std::cout << "Black Turn";
                            bool isCheck = check(turn);
                            if (isCheck) std::cout << "CHECK";
                            if (mate(turn)) std::cout << "MAATE";
                            break;
                        }
                    }

                    pieceSelected = false; // deselcting or selecting outside possible moves will clear out the possible move guide.
                    possibleMoves.clear();
                }

                return;
            }
        }
    }
}

bool Board::check(int s) {
    Piece* piece = nullptr;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // one of other teams pieces
            if ((s == -1 && board[i][j] > 0) || s == 1 && board[i][j] < 0) {
                switch (abs(board[i][j])) {
                case 1: piece = new Pawn(); break;
                case 2: piece = new Knight(); break;
                case 3: piece = new Bishop(); break;
                case 4: piece = new Rook(); break;
                case 5: piece = new King(); break;
                case 6: piece = new Queen(); break;
                }
                std::vector<Pair> piecemoves = piece->getAllPossibleMoves({j, i}, board);
                for (auto move : piecemoves) {
                    // i just realized that move.x SHOULD go in the second [], but for some reason this works.
                    // so my guess is that in getallpossible moves, the pair returned is (y, x) not (x, y), even though it says x, y
                    if ((s == -1 && board[move.y][move.x] == -5) || (s == 1 && board[move.y][move.x] == 5)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::mate(int s) {
    if (!check(s)) return false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] * s > 0) { // only looking at our pieces (whoever turn it is)
                Piece* piece = nullptr;
                switch (abs(board[i][j])) {
                case 1: piece = new Pawn(); break;
                case 2: piece = new Knight(); break;
                case 3: piece = new Bishop(); break;
                case 4: piece = new Rook(); break;
                case 5: piece = new King(); break;
                case 6: piece = new Queen(); break;
                }
                std::vector<Pair> moves = piece->getAllPossibleMoves({ j,i}, board);
                for (auto move : moves) {
                    // basically gonna simulate every move to see if it will get us out of check
                    int temp = board[move.y][move.x];
                    board[move.y][move.x] = board[i][j];
                    board[i][j] = 0;

                    if (!check(s)) { // got out of check
                        // undo bc it wont hit the other undo block if we return now
                        board[i][j] = board[move.y][move.x];
                        board[move.y][move.x] = temp;
                        return false;
                    }

                    //undo
                    board[i][j] = board[move.y][move.x];
                    board[move.y][move.x] = temp;
                   
                }
            }
        }
    }
    return true;
}
