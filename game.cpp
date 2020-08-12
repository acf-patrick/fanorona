#include "game.h"
#include "const.h"
#include "base/text.h"
#include "background.h"

Game::Game() : App("Fanorona", 800, 550)
{
	objects.add(new Background);
	objects.add(new Text("fanorona", 255, 255, 255, "Ubuntu-B", NULL, CHAR_SIZE, 15, 15));
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
