#include "game.h"
#include "const.h"
#include "base/text.h"
#include "background.h"
#include "pawn.h"
#include <ctime>

Game::Game() : App("Fanorona", 800, 550), turn(BLACK)
{
	srand(time(0));
	board = (int**)malloc(3*sizeof (*board));
	for (int i=0; i<3; ++i)
		board[i] = (int*)malloc(3*sizeof (**board));
	gen();
	Piece::board = board;
	other.add({ new Background,
				new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 18, 20, 87, 87, 87, 100),
				new Text("fanorona", "Ubuntu-B", NULL, CHAR_SIZE, 15, 15, 255, 255, 255) });
    for (int i=0; i<9; ++i)
	{
		GameObject* piece(new Piece (i/3, i%3, 0));
		piece->update();
		colliders.add(piece);
	}
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
            pieces.add(new Piece(x, y, i));
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
	if (keys[SDLK_b])
	{
        for (int i=0; i<3; ++i)
		{
			for (int j=0; j<3; ++j)
				std::cout << board[i][j] << '\t';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		int b_x(event.button.x), b_y(event.button.y);
		if (Piece::selected)
		{
			GameObject* collider(colliders.first_sprite_colliding_with(b_x, b_y));
			if (collider)
				Piece::selected->move(collider->get_x(), collider->get_y());
			else
				Piece::selected->bump("unselect");
			Piece::unselect();
		}
		else if (!Piece::moving)
		{
			GameObject* piece = pieces.first_sprite_colliding_with(b_x, b_y);
			if (piece)
				piece->bump();
		}
	}
}
