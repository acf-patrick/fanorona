#include "game.h"
#include "const.h"
#include "background.h"
#include "shadowedText.h"
#include "pawn.h"
#include "base/widget.h"
#include "base/timer.h"
#include <ctime>

Game::Game() : App("Fanorona", 800, 550), turn(black) {
	srand(time(0));
	board = (int**)malloc(3*sizeof (int*));
	for (int i=0; i<3; ++i)
		board[i] = (int*)malloc(3*sizeof (int));

	Piece::board = board;
	Piece::game_turn = &turn;
	other.add({ new Background, new ShadowedText("fanorona", 15, 15, 255, 255, 255) });
	// other.add(new Fps(60, "Ubuntu-B"));
    for (int i=0; i<9; ++i)
	{
		GameObject* piece(new Piece (i/3, i%3, 0));
		piece->update();
		colliders.add(piece);
	}

	init();
}

void Game::init() {
	for (auto obj : pieces.sprites())
		delete obj;

	pieces.clear();

    for (int i=0; i<3; ++i)
		for (int j=0; j<3; ++j)
			board[i][j] = BLANK;
}

void Game::draw() {
	other.draw(screen);
	pieces.draw(screen);
}

void Game::update() {
	other.update();
	pieces.update();

	int w(winner());
	if (w != BLANK and !Piece::moving) {
		std::string message("Les ");
		message += w?"blancs":"noirs";
		message += " ont gagnes\n Faire une autre partie ?";
		if (confirm(message))
			init();
		else
			end();
	}
	SDL_Delay(5);
}

void Game::update_events() {
	App::update_events();

	if (event.type == SDL_MOUSEBUTTONUP) {
		int b_x(event.button.x), b_y(event.button.y);
		if (Piece::ready()) {
			if (Piece::selected) {
				GameObject* collider(colliders.first_sprite_colliding_with(b_x, b_y));
				if (collider)
					Piece::selected->move(collider->get_x(), collider->get_y());
				else
					Piece::selected->bump("unselect");
				Piece::unselect();
			}
			else if (!Piece::moving) {
				GameObject* piece = pieces.first_sprite_colliding_with(b_x, b_y);
				if (piece)
					if (board[piece->get_x()][piece->get_y()] == turn)
						piece->bump();
			}
		} else {
			GameObject* collider(colliders.first_sprite_colliding_with(b_x, b_y));
			if (collider) {
				int i(collider->get_x()), j(collider->get_y());
				if (board[i][j] == BLANK) {
					board[i][j] = turn;
					pieces.add(new Piece(i, j, turn));
					turn = !turn;
				}
			}
		}
	}
}

int Game::winner() {
	int** board(Piece::board);
    for (int k=0; k<3; ++k) {
		if (board[k][0] != BLANK)
			if (board[k][0] == board[k][1] and board[k][0] == board[k][2] and Piece::allMoved(board[k][0]))
				return board[k][0];
		if (board[0][k] != BLANK)
			if (board[0][k] == board[1][k] and board[0][k] == board[2][k] and Piece::allMoved(board[0][k]))
				return board[0][k];
    }
    if (board[0][0] != BLANK)
		if(board[0][0] == board[1][1] and board[0][0] == board[2][2] and Piece::allMoved(board[0][0]))
			return board[0][0];
    if (board[0][2] != BLANK)
		if(board[0][2] == board[1][1] and board[0][2] == board[2][0] and Piece::allMoved(board[0][2]))
			return board[0][2];
    return BLANK;
}

