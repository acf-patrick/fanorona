#ifndef GAME_H
#define GAME_H

#include "base/app.h"
#include "base/group.h"

// Le jeu
class Game : public App {
public:
	Game();

  	static int winner();

private:
	void init();
	void draw();
  	void update();

  	void update_events();

    Group other, pieces, colliders;
    int **board, turn;
    enum { black, white, BLANK };
};

#endif
