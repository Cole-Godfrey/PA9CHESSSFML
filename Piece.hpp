#include <vector>

using namespace std;

struct Pair {
	int x;
	int y;
};

class Piece {
public:
	virtual vector<Pair> getAllPossibleMoves(Pair curPos);
private:
	int side; // black or white
	Pair pos;
};

class Pawn : public Piece {
public:
	vector<Pair> getAllPossibleMoves(Pair curPos);
};

class Knight : public Piece {
public:
	 vector<Pair> getAllPossibleMoves(Pair curPos);
};

class Bishop : public Piece {
public:
	 vector<Pair> getAllPossibleMoves(Pair curPos);
};

class Rook : public Piece {
public:
	vector<Pair> getAllPossibleMoves(Pair curPos);
};

class King : public Piece {
public:
	vector<Pair> getAllPossibleMoves(Pair curPos);
};

class Queen : public Piece {
public:
	vector<Pair> getAllPossibleMoves(Pair curPos);
};