#-*-coding:Latin-1 -*-
from const import*
from stone import*
from board import*
from player import*

class Game:
    """Classe où le déroulement du jeu est geré"""
    def __init__(self, joueur):
        if joueur[0]=='human':
            self.p1=Player('blue')
        else:
            self.p1=IA('blue')
        if joueur[1]=='human':
            self.p2=Player('red')
        else:
            self.p2=IA('red')
        self.akalana=Board()
        self.winner='vide'
        self.trait='blue'

    def is_human(self):
        """Retourne un booléen 'le joueur courant est humain'"""
        if self.trait=='blue':
            return type(self.p1)==Player
        else:
            return type(self.p2)==Player

    def start(self, fenetre):
        self.akalana.populate()
        self.akalana.aff(fenetre)
        while self.akalana.gagnant()=='vide':

