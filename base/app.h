#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SDL/SDL.h>

// Classe de base pour l'application
class App {
public:
    static App* instance;

    App(std::string app_title = "App", int w = 480, int h = 360);
    virtual ~App();

// Démarrer l'application
    void run();
// Mettre l'application en pause/play
    void pause();
// Quitter l'application
    void end();
// Obtenir l'objet evenement
    SDL_Event* get_event();
// Obtenir la taille de la fenêtre du programme
    void window_size(int*, int*);

protected:
// Gestion des evenements
    virtual void manage_events();
// Mettre à jour l'état de l'application
    virtual void update();
// Déssiner l'application
    virtual void draw();

// l'application est mise en pause
    bool paused;
// l'application est en marche
    bool running;
// La fenêtre principale
    SDL_Surface* screen;
// Objet evenement
    SDL_Event event;
// Représente le clavier
// true : touche appuyée
// false : touche relâchée
    bool keys[SDLK_LAST];

    virtual void update_events();
};

#endif
