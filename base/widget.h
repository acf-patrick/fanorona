/**
 * @file widget.h
 * @author acf-patrick (miharisoap@gmail.com)
 * @brief Quelques widgets implémentés avec SDL 1.2
 * 
 */

#pragma once

#include "object.h"
#include "text.h"
#include "app.h"

#include <SDL/SDL.h>
#include <string>

const std::string TEXT_FONT = "Ubuntu-B";

/**
 * @brief Classe de base
 * les fonctionnalités d'un boutton sont encapsulés dans cette classe
 * 
 */
class __button__: public GameObject {
public:
    virtual ~__button__();
    void set_position(int, int);
    void set_size(float);
    void set_text(const std::string&);
    void draw(SDL_Surface*);
    void update();

protected:
    enum { HOVER, CLICKED, IDLE };
    int state;
    SDL_Surface* background[3];
    Text* innerText;

    void define_bg(SDL_Surface* hover = NULL, SDL_Surface* clicked = NULL, SDL_Surface* idle = NULL);
    virtual void action() = 0;
};

class Button: public __button__ {
public:
    Button(const std::string&);
protected:
    virtual void action();
};

bool confirm(const std::string&);

class Confirm: public GameObject {
public:
    Confirm(const std::string&);
    ~Confirm();
    void draw(SDL_Surface*);
    void update();
    int result;
private:

// OK button
    class Ok: public Button {
    public :
        Ok(Confirm* c): Button("Annuler"), parent(c) {
            set_text("OK");
        }
    protected:
        void action() {
            parent->result = true;
            parent->kill();
        }
        Confirm* parent;
    };

// Cancel button
    class Cancel: public Button {
    public:
        Cancel(Confirm* c): Button("Annuler"), parent(c) {}
    protected:
        void action() {
            parent->result = false;
            parent->kill();
        }
        Confirm *parent;
    };
    SDL_Surface* shadow;
    Text *message;
    Button *ok, *cancel;
};
