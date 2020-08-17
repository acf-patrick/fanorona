#ifndef PAWN_H
#define PAWN_H

#include <SDL.h>
#include <vector>
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
	void move(int, int);
	void update();
	void bump(const std::string& flag = "");
	int get_x() const;
	int get_y() const;

	static bool allMoved(int);
	static void unselect();
	static bool ready();

	static Piece *selected, *moving;
	static int diameter, *game_turn, **board;
	static SDL_Rect board_top_left;

private:
	enum { IDLE, MOVING, SELECTED };

	/* relative coordinates */
	int r_x, r_y, d_x, d_y;

	int state;
	SDL_Surface *shadow, *light, *zoom;

	float x_vel, y_vel, acceleration;

	bool moved;

	static int instance;
	static int move_cnt[2];

	SDL_Rect get_SDL_coord(int, int);
	bool valid(int, int);
};

#endif
