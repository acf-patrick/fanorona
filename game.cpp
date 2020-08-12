#include "game.h"
#include "const.h"
#include "base/text.h"
#include "background.h"
#include "pawn.h"

Game::Game() : App("Fanorona", 800, 550)
{
	objects.add(new Background);
	for (int i=0; i<3; ++i)
		for (int j=0; j<3; ++j)
			objects.add(new Piece(i, j, (i+j)%2));
	objects.add(new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 18, 18, 170, 170, 170, 170));
	objects.add(new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 15, 15, 255, 255, 255));
}

void Game::draw()
{
	objects.draw(screen);
}

void Game::update()
{
	objects.update();
}

void Game::update_events()
{
	App::update_events();
}
