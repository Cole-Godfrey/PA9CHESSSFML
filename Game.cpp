
#include "Game.hpp"
#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

void playGameOnSameDesktop() {

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "CHESS 2");

    sf::Texture chessBoard;
    if (!chessBoard.loadFromFile("board.png")) {
        std::cerr << "Failed to load board.png\n";
        return;
    }
    sf::Sprite boardImage;
    boardImage.setTexture(chessBoard);

    Board actualBoard;

    sf::Font font;
    font.loadFromFile("Roboto.ttf");

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(30);
    turnText.setFillColor(sf::Color::Black);
    turnText.setPosition(20.f, 20.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                actualBoard.handleClick(mousePos.x, mousePos.y);
            }
        }

        if (actualBoard.mate(1)) turnText.setString("Checkmate! Black Wins!");
        else if (actualBoard.mate(-1)) turnText.setString("Checkmate! White Wins!");
        else turnText.setString(actualBoard.getTurn() == 1 ? "White's Turn" : "Black's Turn");

        window.clear();
        window.draw(boardImage);
        actualBoard.RenderBoard(window);
        window.draw(turnText);
        window.display();

        if (actualBoard.mate(1) || actualBoard.mate(-1)) {
            sf::sleep(sf::seconds(3));
            window.close();  
        }
    }
}

void runMainMenu() {

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Main Menu");

    sf::Font font;
    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text title("SFML Chess", font, 48);
    title.setFillColor(sf::Color::Black);
    title.setPosition(250.f, 40.f);

    sf::Text textPlay, textRules, textExit;
    textPlay.setFont(font); textRules.setFont(font); textExit.setFont(font);
    textPlay.setString("Play 1v1 on same desktop");
    textRules.setString("View Rules of the Game");
    textExit.setString("Exit");

    sf::Text* options[] = { &textPlay, &textRules, &textExit };
    const int numOptions = 3;

    sf::RectangleShape buttons[numOptions];
    for (int i = 0; i < numOptions; ++i) {
        buttons[i].setSize(sf::Vector2f(400, 50));
        buttons[i].setFillColor(sf::Color(50, 50, 50)); 
        buttons[i].setPosition(200.f, 150.f + i * 100);
        buttons[i].setOrigin(0.f, 0.f);

        options[i]->setCharacterSize(20);
        options[i]->setFillColor(sf::Color::White);
        options[i]->setPosition(210.f, 160.f + i * 100);
    }

    while (window.isOpen()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < numOptions; ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos)) {
                        switch (i) {
                        case 0:
                            window.close();
                            playGameOnSameDesktop();
                            runMainMenu();
                            break;
                        case 1:
                            showRulesWindow();
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                    }
                }
            }
        }

        // Hover effect
        for (int i = 0; i < numOptions; ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos))
                buttons[i].setFillColor(sf::Color(80, 80, 80));
            else
                buttons[i].setFillColor(sf::Color(50, 50, 50));
        }

        window.clear(sf::Color(210, 180, 140)); 
        window.draw(title);
        for (int i = 0; i < numOptions; ++i) {
            window.draw(buttons[i]);
            window.draw(*options[i]);
        }
        window.display();
    }
}



void showRulesWindow() {

    sf::RenderWindow rulesWindow(sf::VideoMode(1000, 1000), "Chess Rules");

    sf::Font font;
    font.loadFromFile("Roboto.ttf");

    sf::Text title("Chess Rules", font, 36);
    title.setFillColor(sf::Color::Black);
    title.setPosition(220.f, 20.f);

    std::vector<std::string> ruleLines = {
        "[1] Each player starts with 16 pieces.",
        "[2] White moves first.",
        "[3] The goal is to checkmate the enemy king.",
        "[4] Pawns move forward, but capture diagonally.",
        "[5] Rooks move straight (horizontal and vertical).",
        "[6] Bishops move diagonally.",
        "[7] The Queen combines rook and bishop movement.",
        "[8] Knights move in 'L' shapes (2+1 or 1+2).",
        "[9] The King moves one square in any direction.",
        "[10] You cannot make a move that leaves your king in check.",
        "[11] Checkmate ends the game immediately.",
    };

    std::vector<sf::Text> ruleTexts;
    for (size_t i = 0; i < ruleLines.size(); ++i) {
        sf::Text rule(ruleLines[i], font, 20);
        rule.setFillColor(sf::Color::Black);
        rule.setPosition(50.f, 80.f + static_cast<float>(i * 40));
        ruleTexts.push_back(rule);
    }

    while (rulesWindow.isOpen()) {
        sf::Event event;
        while (rulesWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed) {
                rulesWindow.close();
            }
        }

        rulesWindow.clear(sf::Color(245, 235, 200)); 
        rulesWindow.draw(title);
        for (auto& rule : ruleTexts) {
            rulesWindow.draw(rule);
        }
        rulesWindow.display();
    }
}
