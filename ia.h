#ifndef AI_H
#define AI_H

#include <vector>
#include "pawn.h"

class AI
{
public:
	AI(int, int depth = 5);
	~AI();
	void play();
	Piece* put();

	int color;

private:
	std::vector<Piece*> pieces;

	int m_depth;
	const int INF;
	std::vector< std::vector<int> > valid_moves(int, int) const;

	int evaluate(int) const;
	int min(int) const;
	int max(int) const;
};

#endif
