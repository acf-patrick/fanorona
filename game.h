#ifndef GAME_H
#define GAME_H

#include "base/app.h"
#include "base/group.h"
#include "ia.h"

class Game : public App
{
public:
	Game();
	~Game();

  	static int winner();
private:
	void draw();
  	void update();
  	void update_events();
  	void manage_events();

  	AI *player[2];

    Group other, pieces, colliders;
    int **board, turn;
    enum { black, white, BLANK };
};

#endif
