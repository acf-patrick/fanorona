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
	void bump(const std::string& flag = "");

	static int diameter;
	static SDL_Rect board_top_left;

private:
	enum { IDLE, MOVING, SELECTED };

	/* relative coordinates */
	int r_x, r_y;

	int state;
	SDL_Surface *shadow, *light;
};

#endif
