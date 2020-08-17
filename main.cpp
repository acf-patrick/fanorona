#include <iostream>
#include "game.h"

int main(int argc, char** argv)
{
	Game* fanorona = new Game();
	fanorona->run();
	delete fanorona;
    return 0;
}
