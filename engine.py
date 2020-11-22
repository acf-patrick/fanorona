#-*- coding:Latin-1 -*-
from const import*
from menu import*
from pygame.locals import*

class Engine:
    def __init__(self):
        pygame.init()
        self.f=pygame.display.set_mode(background.get_size())
        self.menu=Menu()
        self.p1='human'
        self.p2='human'

    def run(self):
        choix=''
        while choix!='quit':
            choix=self.menu.run(self.f)
            if type(choix)==tuple:
                self.game=Game(choix)
                choix=self.game.start(self.f)
    def stop(self):
        pygame.quit()
