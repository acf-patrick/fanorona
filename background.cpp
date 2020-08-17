#include "background.h"
#include "base/app.h"
#include "base/func_tool.h"
#include "const.h"
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "pawn.h"

Background::Background()
{
	int sw, sh;
	App::instance->window_size(&sw, &sh);
	image = SDL_CreateRGBSurface(SDL_HWSURFACE, sw, sh, 32, 0, 0, 0, 0);
	if (!image)
	{
		std::cerr << "Erreur lors de la création de l'image de fond!";
		exit(EXIT_FAILURE);
	}

	SDL_FillRect(image, NULL, BACKGROUND);

	const int border_x(15), border_y(15), padding(25), thickness(3);
	SDL_Rect front = { 0, 0 };
	front.w = front.h = 10*Piece::diameter;
	front.x = .5*(image->w - front.w);
	front.y = .5*(image->h - front.h);
    SDL_Rect back = { Sint16(front.x - border_x), Sint16(front.y - border_y), Uint16(front.w + 2*border_x), Uint16(front.h + 2*border_y) };

    /* counter-clockwise */
    Sint16 vx[] = { Sint16(back.x), Sint16(back.x+image->h-(back.y+back.h)), Sint16(image->w), Sint16(image->w), Sint16(back.x+back.w) },
		   vy[] = { Sint16(back.y+back.h), Sint16(image->h), Sint16(image->h), Sint16(back.y+image->w-(back.x+back.w)), Sint16(back.y) };

	/* shadow */
	filledPolygonColor(image, vx, vy, 5, BOARD_SHADOW);
	/* border */
    // SDL_FillRect(image, &back, BOARD_BORDER);
	boxColor(image, back.x, back.y, back.x+back.w, back.y+back.h, BOARD_BORDER);
	filledPolygonColor(image, vx, vy, 5, BOARD_SHADOW);
    /* background */
    roundedBoxColor(image, front.x, front.y, front.x+front.w, front.y+front.h, 10, 0xffffffff);
    /*SDL_FillRect(image, &front, WHITE);*/
    /* lines */
    int cote = front.w - 2*padding;
    SDL_Rect top_left = { Sint16(front.x + padding), Sint16(front.y + padding) };
    Piece::board_top_left.x = top_left.x;
    Piece::board_top_left.y = top_left.y;
    Piece::board_top_left.w = Piece::board_top_left.h = cote;
    for (int i=0; i<3; ++i)
    {
        thickLineColor(image, top_left.x+i*0.5*cote, top_left.y, top_left.x+0.5*i*cote, top_left.y+cote, thickness, BLACK);
        thickLineColor(image, top_left.x, top_left.y+i*0.5*cote, top_left.x+cote, top_left.y+0.5*i*cote, thickness, BLACK);
	}
    thickLineColor(image, top_left.x, top_left.y, top_left.x+cote, top_left.y+cote, thickness, BLACK);
    thickLineColor(image, top_left.x+cote, top_left.y, top_left.x, top_left.y+cote, thickness, BLACK);
}
