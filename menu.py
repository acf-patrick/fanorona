#-*-codin:Latin-1 -*-

from const import*
from pygame.locals import*

class Menu:
    def __init__(self):
        self.type1='human'
        self.type2='human'

    def run(self, fenetre):
        while True:
            self.show(fenetre)
            event=pygame.event.wait()
            if event.type==QUIT:
                return 'quit'
            if event.type==MOUSEBUTTONUP:
                choix=self.clic(event.pos)
                if choix!=None:
                    return choix

    def clic(self, pos):
        x, y=pos
        if MIN_NEW[0]<x<MAX_NEW[0] and MIN_NEW[1]<y<MAX_NEW[1]:
            return self.type1, self.type2
        if POS_J1[0]<x<POS_J1[0]+human.get_width() and POS_J1[1]<y<POS_J1[1]+human.get_height():
            self.type1='human' if self.type1=='computer' else 'computer'
        if POS_J2[0]<x<POS_J2[0]+human.get_width() and POS_J2[1]<y<POS_J2[1]+human.get_height():
            self.type2='human' if self.type2=='computer' else 'computer'

    def show(self, fenetre):
        fenetre.blit(background, (0,0))
        fenetre.blit(human if self.type1=='human' else computer, POS_J1)
        fenetre.blit(human if self.type2=='human' else computer, POS_J2)
        pygame.display.flip()
