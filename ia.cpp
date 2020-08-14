#include "ia.h"
#include <ctime>

AI::AI(int p_color) : color(p_color)
{}
AI::~AI()
{}

void AI::play()
{

}

Piece* AI::put()
{
    int i, j;
    do {
        i = rand()%3;
        j = rand()%3;
    } while(Piece::board[i][j] != 2);
    pieces.push_back(new Piece(i, j, color));
    return pieces.back();
}
