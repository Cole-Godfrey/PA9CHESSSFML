

#pragma once

#include "Piece.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>

using namespace sf;

struct Coordinates {
    int x;
    int y;
};

class Board {
public:
    Board();
    void RenderBoard(RenderWindow& window);
    void handleClick(int mouseX, int mouseY); // need to pass reference to our window in source since we aren't creating a new one
    //bool isSquareAttacked(int x, int y, int s);
    bool check(int s);
    bool mate(int s);
    int getTurn() const { return turn; }

private:
    /*
    black = neg, white pos
    0 = empty square
    1 = pawn
    2 = knight
    3 = bishop
    4 = rook
    5 = king
    6 = queen
    */
    int board[8][8] = {
        {-4, -2, -3, -6, -5, -3, -2, -4},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1,  1},
        { 4,  2,  3,  6,  5,  3,  2,  4}
    };

    Coordinates boardCords[8][8] = {
        { {130,130}, {234,132}, {340,130}, {448,130}, {554,128}, {656,127}, {760,127}, {871,128} },
        { {130,230}, {238,234}, {334,233}, {444,231}, {551,232}, {652,236}, {765,231}, {864,235} },
        { {127,338}, {239,335}, {343,338}, {440,339}, {558,341}, {658,336}, {765,337}, {863,334} },
        { {128,439}, {240,439}, {338,440}, {451,440}, {561,441}, {654,441}, {752,440}, {862,444} },
        { {125,545}, {234,547}, {342,547}, {442,545}, {550,548}, {655,547}, {762,548}, {869,548} },
        { {127,653}, {236,653}, {341,656}, {445,653}, {550,652}, {655,653}, {761,654}, {865,655} },
        { {125,759}, {229,758}, {337,763}, {439,760}, {547,757}, {661,761}, {764,763}, {859,760} },
        { {124,865}, {239,866}, {343,867}, {446,867}, {547,867}, {656,865}, {759,868}, {871,869} }
    };

    std::map<int, Texture> piece2Image;

    int selectedX = -1, selectedY = -1;
    bool pieceSelected = false;
    std::vector<Pair> possibleMoves;
    int turn = 1; // white = 1, black = -1
};
