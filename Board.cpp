

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
                            // Check Pawn Promotion
                            if (abs(board[j][i]) == 1 && ((board[j][i] == 1 && j == 0) || (board[j][i] == -1 && j == 7))) {
                                int promoted = showPromotionMenu(board[j][i] > 0);
                                board[j][i] = (board[j][i] > 0) ? promoted : -promoted;
                            }
                            turn *= -1;
                            if (turn == 1) std::cout << "White turn\n";
                            else std::cout << "Black Turn\n";
                            bool isCheck = check(turn);
                            if (isCheck) std::cout << "CHECK\n";
                            if (mate(turn)) std::cout << "MAATE\n";
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

// same exact thing as handleclick but we are also sending packet of move to port
bool Board::handleNetworkClick(int mouseX, int mouseY, TcpSocket& socket) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            int bx = boardCords[j][i].x;
            int by = boardCords[j][i].y;

            // this checls the coordinates of the mouse cursor if its within a certain square. [0-50] from the origin 
            if (abs(bx - mouseX) < 50 && abs(by - mouseY) < 50) {

                if (!pieceSelected && board[j][i] != 0 && (board[j][i] * turn > 0)) {

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
                            // send to server
                            Packet p;
                            p << selectedX << selectedY << i << j;
                            socket.send(p);
                            turn *= -1;
                            if (turn == 1) std::cout << "White turn\n";
                            else std::cout << "Black Turn\n";
                            bool isCheck = check(turn);
                            if (isCheck) std::cout << "CHECK\n";
                            if (mate(turn)) std::cout << "MAATE\n";
                            pieceSelected = false; // deselcting or selecting outside possible moves will clear out the possible move guide.
                            possibleMoves.clear();
                            return true; // did move
                        }
                    }

                    pieceSelected = false; // deselcting or selecting outside possible moves will clear out the possible move guide.
                    possibleMoves.clear();
                }

                return false;
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
                    // for every move, if it can capture the king it is check
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

int Board::showPromotionMenu(bool isWhite) {

    sf::RenderWindow promoWindow(sf::VideoMode(1000, 1000), "Pawn Promotion");

    sf::Font font;
    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Failed to load font.\n";
        return 6;
    }

    sf::Text prompt("Choose a piece to promote to:", font, 36);
    prompt.setFillColor(sf::Color::Black);
    prompt.setPosition(300.f, 100.f);

    std::vector<int> types = { 6, 4, 3, 2 };  // Queen, Rook, Bishop, Knight
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Sprite> pieceSprites;

    float squareSize = 180.f;
    float spacing = 60.f;
    float startX = (1000 - (2 * squareSize + spacing)) / 2.f;
    float startY = (1000 - (2 * squareSize + spacing)) / 2.f;

    for (int i = 0; i < 4; ++i) {
        int pieceID = isWhite ? types[i] : -types[i];
        if (!piece2Image.count(pieceID)) {
            std::cerr << "Missing texture for piece ID: " << pieceID << std::endl;
            continue;
        }

        sf::RectangleShape button(sf::Vector2f(squareSize, squareSize));
        float x = startX + (i % 2) * (squareSize + spacing);
        float y = startY + (i / 2) * (squareSize + spacing);
        button.setPosition(x, y);
        button.setFillColor(sf::Color(50, 50, 50));
        buttons.push_back(button);

        sf::Sprite piece;
        piece.setTexture(piece2Image[pieceID]);
        piece.setScale(3.0f, 3.0f);
        sf::FloatRect bounds = piece.getLocalBounds();
        piece.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        piece.setPosition(x + squareSize / 2.f, y + squareSize / 2.f);
        pieceSprites.push_back(piece);
    }

    while (promoWindow.isOpen()) {
        sf::Event event;
        while (promoWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                promoWindow.close();
                return 6;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = promoWindow.mapPixelToCoords(sf::Mouse::getPosition(promoWindow));
                for (int i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos)) {
                        std::cout << "PROMOTING TO: " << types[i] << std::endl;
                        promoWindow.close();
                        return types[i];
                    }
                }
            }
        }

        promoWindow.clear(sf::Color(240, 230, 200));
        promoWindow.draw(prompt);
        for (int i = 0; i < buttons.size(); ++i) {
            promoWindow.draw(buttons[i]);
            promoWindow.draw(pieceSprites[i]);
        }
        promoWindow.display();
    }

    return 6;
}