#include "tests.hpp"

void Test::testCheckmate() {
    cout << "Testing Checkmate...";
    Board b;
    // checkmate scenario
    int board[8][8] = {
        {-4, -2, -3, 0, -5, -3,  -2, -4},
        {-1, -1, -1, -1,  0, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0, -1,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  1, -6},
        { 0,  0,  0,  0,  0,  1,  0,  0},
        { 1,  1,  1,  1,  1,  0,  0,  1},
        { 4,  2,  3,  6,  5,  3,  2,  4}
    };
    b.setBoard(board);
    bool isMate = b.mate(1);
    if (isMate) cout << "PASSED\n";
    else cout << "FAILED\n";
};

void Test::testCheck() {
    cout << "Testing Check...";
    Board b;
    // check scenario
    int board[8][8] = {
        {0, 0,  -4, 0, -5, -3, -2, -4},
        {-1, -1, 0, 0, 0, 1, 0, 0},
        { -2,  0, -1,  -6,  -1,  0,  0,  0},
        { 0,  0,  0,  -1,  2,  0,  0,  -1},
        { 0,  0,  0,  1,  0,  0,  0,  0},
        { 0,  0,  1,  0,  0,  0,  1,  0},
        { 1,  1,  6,  0,  1,  1,  0,  0},
        { 4,  2,  3,  0,  5,  3,  0,  4}
    };
    b.setBoard(board);
    bool isCheck = b.check(-1);
    if (isCheck) cout << "PASSED\n";
    else cout << "FAILED\n";
}

//https://www.geeksforgeeks.org/cpp-return-2d-array-from-function/
void Test::testGettingLegalMovesPawn() {
    cout << "Testing getting a pawns legal moves...";
    Board b;
    int(*board)[8];
    board = b.getBoard();
    Pawn p;
    std::vector<Pair> moves = p.getAllPossibleMoves({ 3, 6 }, board);
    // to store whether or not that move was in the moves
    int move1 = 0;
    int move2 = 0;
    for (auto move : moves) {
        if (move.x == 3 && move.y == 5) {
            move1 = 1;
        }
        if (move.x == 3 && move.y == 4) {
            move2 = 1;
        }
    }
    if (move1 && move2) cout << "PASSED\n";
    else cout << "FAILED\n";
}

void Test::testGettingLegalMovesQueen() {
    cout << "Testing getting a queens legal moves...";
    Board b;
    int(*board)[8];
    board = b.getBoard();
    Queen q;
    // moves should be none
    std::vector<Pair> moves = q.getAllPossibleMoves({ 3, 7 }, board);
    
    if (moves.empty()) cout << "PASSED\n";
    else cout << "FAILED\n";
}

void Test::testGettingLegalMovesRook() {
    cout << "Testing getting a rooks legal moves...";
    Board b;
    int(*board)[8];
    board = b.getBoard();
    Rook r;
    // moves should be none
    std::vector<Pair> moves = r.getAllPossibleMoves({ 7, 7 }, board);

    if (moves.empty()) cout << "PASSED\n";
    else cout << "FAILED\n";
}

Test::Test() {
    testCheck();
    testCheckmate();
    testGettingLegalMovesPawn();
    testGettingLegalMovesQueen();
    testGettingLegalMovesRook();
}