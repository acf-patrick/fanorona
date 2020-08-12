#ifndef GAME_H
#define GAME_H

#include "base/app.h"
#include "base/group.h"

class Game : public App
{
public:
	Game();

private:
	void draw();
  	void update();
  	void update_events();

    Group objects;
};

#endif
