#ifndef AI_H
#define AI_H

#include <vector>
#include "pawn.h"

class AI
{
public:
	AI(int);
	~AI();
	void play();
	Piece* put();

	int color;

private:
	std::vector<Piece*> pieces;
};

#endif
