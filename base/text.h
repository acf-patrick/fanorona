#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "object.h"

// Text dans le jeu
class Text: public GameObject {
public:
    Text(const std::string& content, const std::string& font_name,
         SDL_Rect* _viewport, int char_size, int _x, int _y, int r, int g, int b, int a = 255);
    virtual ~Text();

    void draw(SDL_Surface*);
    void set(SDL_Color, const std::string& content = "");
    void setFont(const std::string& font_name, int textSize = 0);
    void setSize(float);

protected:

// Bounding box
    SDL_Rect* viewport;
// Contenu
    std::string text;
// Nom de la police de caractères
    std::string fontName;
// Couleur du texte
    SDL_Color color;
// Police utilisé
    TTF_Font* font;

    Uint8 alpha;
};

#endif
