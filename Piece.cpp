#include "Piece.hpp"
#include <cmath>

bool isInBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

std::vector<Pair> Piece::getAllPossibleMoves(Pair, int[8][8]) {
    // this is just a test comment to see if i can upload to github repo
    return {};
}

std::vector<Pair> Pawn::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int direction;

    if (board[curPos.y][curPos.x] > 0)
        direction = -1; 
    else
        direction = 1;  

    if (isInBounds(curPos.x, curPos.y + direction) && board[curPos.y + direction][curPos.x] == 0)
        moves.push_back({ curPos.x, curPos.y + direction });

    // first move of pawn that they can hop in twice
    if (((direction == -1 && curPos.y == 6) || (direction == 1 && curPos.y == 1)) &&
        board[curPos.y + direction][curPos.x] == 0 &&
        board[curPos.y + 2 * direction][curPos.x] == 0)
        moves.push_back({ curPos.x, curPos.y + 2 * direction });

    // Eating diagonally only
    for (int dx = -1; dx <= 1; dx += 2) {
        int nx = curPos.x + dx;
        int ny = curPos.y + direction;
        if (isInBounds(nx, ny) && board[ny][nx] != 0) {
            bool isCurrentWhite = board[curPos.y][curPos.x] > 0;
            bool isTargetWhite = board[ny][nx] > 0;
            if (isCurrentWhite != isTargetWhite)
                moves.push_back({ nx, ny });
        }
    }

    return moves;
}

std::vector<Pair> Knight::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int side;

    if (board[curPos.y][curPos.x] > 0)
        side = 1;
    else
        side = -1;

    for (int i = 0; i < 8; ++i) {
        int nx = curPos.x + dx[i];
        int ny = curPos.y + dy[i];
        if (isInBounds(nx, ny)) {
            if (board[ny][nx] == 0)
                moves.push_back({ nx, ny });
            else {
                bool isCurrentWhite = side > 0;
                bool isTargetWhite = board[ny][nx] > 0;
                if (isCurrentWhite != isTargetWhite)
                    moves.push_back({ nx, ny });
            }
        }
    }

    return moves;
}

std::vector<Pair> Bishop::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side;

    if (board[curPos.y][curPos.x] > 0)
        side = 1;
    else
        side = -1;

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            for (int i = 1; i < 8; ++i) {

                int nx = curPos.x + i * dx;
                int ny = curPos.y + i * dy;

                if (!isInBounds(nx, ny))
                    break;
                int val = board[ny][nx];

                if (val == 0)
                    moves.push_back({ nx, ny });

                else {
                    bool isCurrentWhite = side > 0;
                    bool isTargetWhite = val > 0;
                    if (isCurrentWhite != isTargetWhite)
                        moves.push_back({ nx, ny });
                    break;
                }
            }
        }
    }

    return moves;
}

std::vector<Pair> Rook::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side;

    if (board[curPos.y][curPos.x] > 0)
        side = 1;
    else
        side = -1;

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int i = 1; i < 8; ++i) {
            int nx = curPos.x + i * dx;
            if (!isInBounds(nx, curPos.y))
                break;
            int val = board[curPos.y][nx];
            if (val == 0)
                moves.push_back({ nx, curPos.y });
            else {
                bool isCurrentWhite = side > 0;
                bool isTargetWhite = val > 0;
                if (isCurrentWhite != isTargetWhite)
                    moves.push_back({ nx, curPos.y });
                break;
            }
        }
    }

    for (int dy = -1; dy <= 1; dy += 2) {
        for (int i = 1; i < 8; ++i) {
            int ny = curPos.y + i * dy;
            if (!isInBounds(curPos.x, ny))
                break;
            int val = board[ny][curPos.x];
            if (val == 0)
                moves.push_back({ curPos.x, ny });
            else {
                bool isCurrentWhite = side > 0;
                bool isTargetWhite = val > 0;
                if (isCurrentWhite != isTargetWhite)
                    moves.push_back({ curPos.x, ny });
                break;
            }
        }
    }

    return moves;
}

std::vector<Pair> Queen::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    //  same sht as rook and bish but combined
    Bishop b;
    Rook r;
    std::vector<Pair> moves = b.getAllPossibleMoves(curPos, board);
    std::vector<Pair> rookMoves = r.getAllPossibleMoves(curPos, board);
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    return moves;
}

std::vector<Pair> King::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side;

    if (board[curPos.y][curPos.x] > 0)
        side = 1;
    else
        side = -1;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;
            int nx = curPos.x + dx;
            int ny = curPos.y + dy;
            if (isInBounds(nx, ny)) {
                int val = board[ny][nx];
                if (val == 0)
                    moves.push_back({ nx, ny });
                else {
                    bool isCurrentWhite = side > 0;
                    bool isTargetWhite = val > 0;
                    if (isCurrentWhite != isTargetWhite)
                        moves.push_back({ nx, ny });
                }
            }
        }
    }

    return moves;
}
