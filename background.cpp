#include "background.h"
#include "base/app.h"
#include "const.h"
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

Background::Background()
{
	int sw, sh;
	App::instance->window_size(&sw, &sh);
	App::instance->window_size(&sw, &sh);
	image = SDL_CreateRGBSurface(SDL_HWSURFACE, sw, sh, 32, 0, 0, 0, 0);
	if (!image)
	{
		std::cerr << "Erreur lors de la création de l'image de fond!";
		exit(EXIT_FAILURE);
	}

	SDL_FillRect(image, NULL, BACKGROUND);

	const int border_x(15), border_y(10), padding(25), thickness(2);
	SDL_Rect front = { 0, 0 };
	front.w = front.h = 270;
	front.x = .5*(image->w - front.w);
	front.y = .5*(image->h - front.h);
    SDL_Rect back = { Sint16(front.x - border_x), Sint16(front.y - border_y), Uint16(front.w + 2*border_x), Uint16(front.h + 2*border_y) };

    /* counter-clockwise */
    Sint16 vx[] = { back.x, back.x+image->h-(back.y+back.h), image->w, image->w, back.x+back.w },
		   vy[] = { back.y+back.h, image->h, image->h, back.y+image->w-(back.x+back.w), back.y };

	/* shadow */
	filledPolygonColor(image, vx, vy, 5, BOARD_SHADOW);
	/* border */
    SDL_FillRect(image, &back, BOARD_BORDER);
    /* background */
    SDL_FillRect(image, &front, WHITE);
    /* lines */
    int cote = front.w - 2*padding;
    SDL_Rect top_left = { Sint16(front.x + padding), Sint16(front.y + padding) };
    for (int i=0; i<3; ++i)
    {
        thickLineColor(image, top_left.x+i*0.5*cote, top_left.y, top_left.x+0.5*i*cote, top_left.y+cote, thickness, BLACK);
        thickLineColor(image, top_left.x, top_left.y+i*0.5*cote, top_left.x+cote, top_left.y+0.5*i*cote, thickness, BLACK);
	}
    thickLineColor(image, top_left.x, top_left.y, top_left.x+cote, top_left.y+cote, thickness, BLACK);
    thickLineColor(image, top_left.x+cote, top_left.y, top_left.x, top_left.y+cote, thickness, BLACK);
}
