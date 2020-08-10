#include "game.h"
#include "const.h"
#include "base/text.h"

Game::Game() : App("Fanorona", 600, 480)
{
	objects.add(new Text("fanorona", 255, 255, 255, "Ubuntu-B", NULL, CHAR_SIZE, 15, 15));
}

void Game::draw_board()
{
	const int border_x(15), border_y(10);
	SDL_Rect front = { 0, 0, 250, 250 };
	front.x = .5*(screen->w - front.w);
	front.y = .5*(screen->h - front.h);
    SDL_Rect back = { front.x - border_x, front.y - border_y, front.w + 2*border_x, front.h + 2*border_y };
    SDL_FillRect(screen, &back, BOARD_BORDER);
    SDL_FillRect(screen, &front, WHITE);
}

void Game::draw()
{
	SDL_FillRect(screen, NULL, BACKGROUND);
	objects.draw(screen);
	draw_board();
}

void Game::update()
{
}

void Game::update_events()
{
	App::update_events();
}
