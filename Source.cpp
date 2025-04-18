#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 1000), "CHESS 2");
    Texture chessBoard;
    chessBoard.loadFromFile("board.jpg");


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        Sprite board;
        board.setTexture(chessBoard);
        window.draw(board);
        window.display();
    }

    return 0;
}