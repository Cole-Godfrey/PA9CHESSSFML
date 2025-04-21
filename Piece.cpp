#include "Piece.hpp"
#include <cmath>

bool isInBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

std::vector<Pair> Piece::getAllPossibleMoves(Pair, int[8][8]) {
    return {};
}

std::vector<Pair> Pawn::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int dir = (board[curPos.y][curPos.x] > 0) ? -1 : 1;

    if (isInBounds(curPos.x, curPos.y + dir) && board[curPos.y + dir][curPos.x] == 0)
        moves.push_back({ curPos.x, curPos.y + dir });

    if (((dir == -1 && curPos.y == 6) || (dir == 1 && curPos.y == 1)) &&
        board[curPos.y + dir][curPos.x] == 0 &&
        board[curPos.y + 2 * dir][curPos.x] == 0)
        moves.push_back({ curPos.x, curPos.y + 2 * dir });

    for (int dx = -1; dx <= 1; dx += 2) {
        int nx = curPos.x + dx, ny = curPos.y + dir;
        if (isInBounds(nx, ny) && board[ny][nx] != 0 &&
            (board[ny][nx] > 0) != (board[curPos.y][curPos.x] > 0))
            moves.push_back({ nx, ny });
    }

    return moves;
}

std::vector<Pair> Knight::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int side = (board[curPos.y][curPos.x] > 0) ? 1 : -1;

    for (int i = 0; i < 8; ++i) {
        int nx = curPos.x + dx[i], ny = curPos.y + dy[i];
        if (isInBounds(nx, ny) && (board[ny][nx] == 0 || (board[ny][nx] > 0) != (side > 0)))
            moves.push_back({ nx, ny });
    }

    return moves;
}

std::vector<Pair> Bishop::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side = (board[curPos.y][curPos.x] > 0) ? 1 : -1;

    for (int dx = -1; dx <= 1; dx += 2)
        for (int dy = -1; dy <= 1; dy += 2)
            for (int i = 1; i < 8; ++i) {
                int nx = curPos.x + i * dx, ny = curPos.y + i * dy;
                if (!isInBounds(nx, ny)) break;
                int val = board[ny][nx];
                if (val == 0) moves.push_back({ nx, ny });
                else {
                    if ((val > 0) != (side > 0)) moves.push_back({ nx, ny });
                    break;
                }
            }

    return moves;
}

std::vector<Pair> Rook::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side = (board[curPos.y][curPos.x] > 0) ? 1 : -1;

    for (int dx = -1; dx <= 1; dx += 2)
        for (int i = 1; i < 8; ++i) {
            int nx = curPos.x + i * dx;
            if (!isInBounds(nx, curPos.y)) break;
            int val = board[curPos.y][nx];
            if (val == 0) moves.push_back({ nx, curPos.y });
            else {
                if ((val > 0) != (side > 0)) moves.push_back({ nx, curPos.y });
                break;
            }
        }

    for (int dy = -1; dy <= 1; dy += 2)
        for (int i = 1; i < 8; ++i) {
            int ny = curPos.y + i * dy;
            if (!isInBounds(curPos.x, ny)) break;
            int val = board[ny][curPos.x];
            if (val == 0) moves.push_back({ curPos.x, ny });
            else {
                if ((val > 0) != (side > 0)) moves.push_back({ curPos.x, ny });
                break;
            }
        }

    return moves;
}

std::vector<Pair> Queen::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    Bishop b;
    Rook r;
    auto moves = b.getAllPossibleMoves(curPos, board);
    auto r_moves = r.getAllPossibleMoves(curPos, board);
    moves.insert(moves.end(), r_moves.begin(), r_moves.end());
    return moves;
}

std::vector<Pair> King::getAllPossibleMoves(Pair curPos, int board[8][8]) {
    std::vector<Pair> moves;
    int side = (board[curPos.y][curPos.x] > 0) ? 1 : -1;

    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = curPos.x + dx, ny = curPos.y + dy;
            if (isInBounds(nx, ny) &&
                (board[ny][nx] == 0 || (board[ny][nx] > 0) != (side > 0)))
                moves.push_back({ nx, ny });
        }

    return moves;
}
