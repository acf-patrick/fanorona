#include "ia.h"
#include "game.h"
#include <ctime>

AI::AI(int p_color, int depth) : color(p_color), m_depth(depth)
{}
AI::~AI()
{
	for (int i=0; i<3; ++i)
		delete pieces[i];
}

void AI::play()
{
	Piece* to_move(NULL);
	bool first(true);
    int v_max;
    std::vector<int> dest;
    for (auto piece : pieces)
	{
		int x(piece->get_x()), y(piece->get_y());
        std::vector< std::vector<int> >&& available(valid_moves(x, y));
        for (auto coord : available)
		{
            std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
            int value(min(m_depth-1));
            if (first or value > v_max)
			{
				first = false;
				v_max = value;
				to_move = piece;
				dest = coord;
			}
            std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
		}
	}
	to_move->move(dest[0], dest[1]);
}

Piece* AI::put()
{
    int i, j;
    do {
        i = rand()%3;
        j = rand()%3;
    } while(Piece::board[i][j] != 2);
    pieces.push_back(new Piece(i, j, color));
    Piece::board[i][j] = color;
    return pieces.back();
}

int AI::evaluate() const
{
    return rand();
}

int AI::min(int depth) const
{
	if (depth == 0 or Game::winner() < 2)
		return depth+evaluate();
    bool first(true);
    int ret;
	for (int x=0; x<3; ++x)
		for (int y=0; y<3; ++y)
			if (Piece::board[x][y] == !color)
			{
				std::vector< std::vector<int> > && available(valid_moves(x, y));
				for (auto coord : available)
				{
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
					int value(max(depth-1));
					if (first or value < ret)
					{
						first = false;
						ret = value;
					}
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
				}
			}
	return ret;
}

int AI::max(int depth) const
{
	if (depth == 0 or Game::winner() < 2)
		return depth+evaluate();
    bool first(true);
    int ret;
	for (int x=0; x<3; ++x)
		for (int y=0; y<3; ++y)
			if (Piece::board[x][y] == color)
			{
				std::vector< std::vector<int> > && available(valid_moves(x, y));
				for (auto coord : available)
				{
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
					int value(min(depth-1));
					if (first or value > ret)
					{
						first = false;
						ret = value;
					}
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
				}
			}
	return ret;
}

std::vector< std::vector<int> > AI::valid_moves(int r_x, int r_y) const
{
    std::vector< std::vector<int> > ret;
    for (int x=r_x-1; x<=r_x+1; ++x)
		for (int y=r_y-1; y<=r_y+1; ++y)
		{
            if (x == r_x and r_y == y)
				continue;
            if (x >= 0 and y >= 0 and x < 3 and y < 3)
				if (Piece::board[x][y] == 2)
					ret.push_back({ x, y });
		}

    return ret;
}
