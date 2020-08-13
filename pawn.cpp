#include "pawn.h"
#include "const.h"
#include "base/func_tool.h"
#include <SDL_gfxPrimitives.h>
#include <cmath>

Piece* Piece::selected(NULL);
SDL_Rect Piece::board_top_left;
int Piece::diameter(32);
int** Piece::board(NULL);

Piece::Piece(int _x, int _y, bool color) : r_x(_x), r_y(_y), state(IDLE)
{
	rect.w = rect.h = diameter;
    image =  createSurface(diameter, diameter);
    shadow = createSurface(diameter, diameter);
    light = createSurface(diameter, diameter);
    if (!(image and shadow and light))
    {
		std::cerr << "Erreur lors de la création d'un pion!";
		exit(EXIT_FAILURE);
    }

    filledCircleColor(shadow, 0.5*diameter, 0.5*diameter, 0.5*diameter, PAWN_SHADOW);
    filledCircleColor(light, 0.5*diameter, 0.5*diameter, 0.5*diameter,0x5a74a946);
    filledCircleColor(image, 0.5*diameter, 0.5*diameter, 0.5*diameter, color?WHITE_PAWN:BLACK_PAWN);
    circleColor(image, 0.5*diameter, 0.5*diameter, 0.5*diameter, 0xeeeeee55);
}

Piece::~Piece()
{
	SDL_FreeSurface(shadow);
	shadow = NULL;
}

void Piece::update()
{
	x = r_y*0.5*board_top_left.w - 0.5*diameter + board_top_left.x;
	y = r_x*0.5*board_top_left.h - 0.5*diameter + board_top_left.y;
}

void Piece::draw(SDL_Surface* screen)
{
    SDL_Rect pos = { Sint16(x+5), Sint16(y+5) };
    SDL_BlitSurface(shadow, NULL, screen, &pos);
    GameObject::draw(screen);
    if (state == SELECTED)
    {
		pos.x = Sint16(x);
		pos.y = Sint16(y);
		SDL_BlitSurface(light, NULL, screen, &pos);
	}
}

void Piece::bump(const std::string& flag)
{
	state = SELECTED;
	selected = this;
}

void Piece::unselect()
{
	selected = NULL;
}

void Piece::move(int xDest, int yDest)
{
	if (valid(xDest, yDest))
	{
		state = MOVING;
		unselect();
		std::swap(board[r_x][r_y], board[xDest][yDest]);
		r_x = d_x = xDest;
		r_y = d_y = yDest;
	}
}

float dist(int x1, int y1, int x2, int y2)
{ return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)); }
bool Piece::valid(int xDest, int yDest)
{
    if (xDest < 0 or yDest < 0 or xDest >= 3 or yDest >= 3)
		return false;
	if (board[xDest][yDest] == black or board[xDest][yDest] == white)
		return false;
	float d(dist(r_x, r_y, xDest, yDest));
    if (1>d or d>std::sqrt(2))
		return false;
	return true;
}

int Piece::get_x() const
{ return r_x; }
int Piece::get_y() const
{ return r_y; }
