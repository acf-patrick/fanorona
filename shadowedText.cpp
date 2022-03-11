#include "shadowedText.h"
#include "const.h"
#include "base/text.h"

ShadowedText::ShadowedText(const std::string& content, int _x, int _y, int r, int g, int b)
{
	text.add(new Text(content, "Ubuntu-B", NULL, CHAR_SIZE, _x+3, _y+5, 80, 80, 80, 100));
	text.add(new Text(content, "Ubuntu-B", NULL, CHAR_SIZE, _x, _y, r, g, b));
}

void ShadowedText::draw(SDL_Surface* screen)
{
	text.draw(screen);
}
