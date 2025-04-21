
#pragma once
#include <vector>

struct Pair {
    int x;
    int y;
};

class Piece {
public:
    virtual std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]);
};

class Pawn : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};

class Knight : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};

class Bishop : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};

class Rook : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};

class King : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};

class Queen : public Piece {
public:
    std::vector<Pair> getAllPossibleMoves(Pair curPos, int board[8][8]) override;
};
