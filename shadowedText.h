#ifndef TEXT
#define TEXT

#include <string>
#include <SDL/SDL.h>
#include "base/group.h"
#include "base/object.h"

class ShadowedText : public GameObject
{
public:
	ShadowedText(const std::string&, int, int, int, int, int);
	void draw(SDL_Surface*);

private:
	Group text;
};

#endif
