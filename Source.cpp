#include "SFML/Graphics.hpp"
#include "Board.hpp"

using namespace sf;

int main() {

    RenderWindow window(VideoMode(1000, 1000), "CHESS 2");
    Texture chessBoard;
    chessBoard.loadFromFile("board.png");
    Sprite boardImage;
    boardImage.setTexture(chessBoard);
    Board actualBoard;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                actualBoard.handleClick(mousePos.x, mousePos.y);
            }
        }

        window.clear();
        window.draw(boardImage);
        actualBoard.RenderBoard(window);
        window.display();
    }

    return 0;
}
