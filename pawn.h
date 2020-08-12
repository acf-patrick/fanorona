#ifndef PAWN_H
#define PAWN_H

#include <SDL.h>
#include "base/object.h"

class Piece : public GameObject
{
public:
	enum { black, white };
	/**
	 * @param _x, _y : position of the piece in board coordinates
	*/
	Piece(int, int, bool);
	~Piece();

	void draw(SDL_Surface*);
	void update();

	static int diameter;
	static SDL_Rect board_top_left;

private:
	/* relative coordinates */
	int r_x, r_y;
	SDL_Surface* shadow;
};

#endif
