#include "game.h"
#include "const.h"
#include "base/text.h"
#include "background.h"
#include "pawn.h"
#include <ctime>

Game::Game() : App("Fanorona", 800, 550), turn(BLACK)
{
	srand(time(0));
	gen();
	other.add({ new Background,
				new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 18, 18, 170, 170, 170, 100),
				new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 15, 15, 255, 255, 255) });
}

void Game::gen()
{
	pieces.clear();
	for (int k = 0; k < 9; ++k)
		board[k/3][k%3] = BLANK;
	for (int i=0; i<2; ++i)
		for (int j=0; j<3; ++j)
		{
			int x, y;
			do {
				x = rand()%3;
				y = rand()%3;
			} while (board[x][y] != BLANK);
			board[x][y] = i;
            pieces.add(new Piece(y, x, i));
		}
}

void Game::draw()
{
	other.draw(screen);
	pieces.draw(screen);
}

void Game::update()
{
	other.update();
	pieces.update();
}

void Game::update_events()
{
	App::update_events();
	if (keys[SDLK_r]) gen();

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		Piece::unselect();
		GameObject* piece = pieces.first_sprite_colliding_with(event.button.x, event.button.y);
		if (piece)
			piece->bump();
	}
}
