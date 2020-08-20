#include "ia.h"
#include "game.h"
#include "base/func_tool.h"
#include <ctime>

AI::AI(int p_color, int depth) : color(p_color), m_depth(depth), INF(1000)
{}
AI::~AI()
{}

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

void AI::play()
{
	Piece* to_move(NULL);
    int v_max(-INF);
    std::vector<int> dest;
    for (auto piece : pieces)
	{
		int x(piece->get_x()), y(piece->get_y());
        std::vector< std::vector<int> > && available(valid_moves(x, y));
        for (auto coord : available)
		{
            std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
            int value(min(m_depth-1));
            if (value > v_max)
			{
				v_max = value;
				to_move = piece;
				dest = coord;
			}
            std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
		}
	}
	std::cout << v_max << std::endl;
	to_move->move(dest[0], dest[1]);
}

int AI::evaluate(int depth) const
{
	int winner(Game::winner()), ret(0), **board = Piece::board;
	if (winner == 2)
	{
        int ia(0), opp(0), _ia, _opp, i, j;
        /*for (i=0; i<3; ++i)
		{
			_ia = _opp = 0;
            for (j=0; j<3; ++j)
				if (board[i][j] == !color)
					_opp++;
				else
					_ia++;
			ia += _ia%3;
			opp += _opp%3;
		}
        for (j=0; j<3; ++j)
		{
			_ia = _opp = 0;
            for (i=0; i<3; ++i)
				if (board[i][j] == !color)
					_opp++;
				else
					_ia++;
			ia += _ia%3;
			opp += _opp%3;
		}
		_ia = _opp = 0;
		for (i=0; i<3; ++i)
			if (board[i][i] == !color)
				_opp++;
			else
				_ia++;
		ia += 2*_ia%3;
		opp += 2*_opp%3;
		_ia = _opp = 0;
		for (i=0; i<3; ++i)
			if (board[i][2-i] == !color)
				_opp++;
			else
				_ia++;
		ia += 2*_ia%3;
		opp += 2*_opp%3;*/

        for (int i=0; i<3; ++i)
		{
			if (board[i][0] == board[i][1] or board[i][1] == board[i][2])
            {
                if (board[i][1] == color)
                    ia++;
                else if (board[i][1] == !color)
                    opp++;
            }
			if (board[0][i] == board[1][i] or board[1][i] == board[2][i])
            {
                if (board[1][i] == color)
                    ia++;
                else if (board[1][i] == !color)
                    opp++;
            }
		}
        if (board[0][0] == board[1][1] or board[1][1] == board[2][2])
        {
            if (board[1][1] == color)
                ia++;
            else if (board[1][1] == !color)
                opp++;
        }
        if (board[0][2] == board[1][1] or board[1][1] == board[2][0])
        {
            if (board[1][1] == color)
                ia++;
            else if (board[1][1] == !color)
                opp++;
        }
		ret = ia - opp;
		ret += 2*(board[1][1] == !color?-1:1);
	}
	else
	{
		ret = INF - (m_depth - depth);
		if (winner == !color)
			ret = -ret;
	}
	return ret;
}

int AI::min(int depth) const
{
	if (depth == 0 or Game::winner() < 2)
		return evaluate(depth);
    int ret(INF);
	for (int x=0; x<3; ++x)
		for (int y=0; y<3; ++y)
			if (Piece::board[x][y] == !color)
			{
				std::vector< std::vector<int> > && available(valid_moves(x, y));
				for (auto coord : available)
				{
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
					int value(max(depth-1));
					if (value < ret)
						ret = value;
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
				}
			}
	return ret;
}

int AI::max(int depth) const
{
	if (depth == 0 or Game::winner() < 2)
		return evaluate(depth);
    int ret(-INF);
	for (int x=0; x<3; ++x)
		for (int y=0; y<3; ++y)
			if (Piece::board[x][y] == color)
			{
				std::vector< std::vector<int> > && available(valid_moves(x, y));
				for (auto coord : available)
				{
					std::swap(Piece::board[x][y], Piece::board[coord[0]][coord[1]]);
					int value(min(depth-1));
					if (value > ret)
						ret = value;
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
			if (Piece::valid(r_x, r_y, x, y))
				ret.push_back({ x, y });
    return ret;
}
