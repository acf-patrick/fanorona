#-*- coding:Latin-1 -*-
from const import*
from stone import*
import pygame as pg
from pygame.locals import*

class Board:
    def __init__(self):
        self.matrix=[]
        self.history=[]
        self.populate()

    def get(self, x, y):
        return self.matrix[x][y]
    def set(self, i, j, new):
        tmp=self.get(i, j)
        tmp=new
    def populate(self):
        """Met tous les pions en place"""
        for i in range(5):
            self.matrix.append([])
            for j in range(9):
                if i<2:
                    self.matrix[i].append(Pion('blue', i, j))
                elif i==2:
                    if j<4:
                        if j%2==0:
                            self.matrix[i].append(Pion('blue', i, j))
                        else:
                            self.matrix[i].append(Pion('red', i, j))
                    elif j==4:
                        self.matrix[i].append(Pion('vide', i, j))
                    else:
                        if j%2==1:
                            self.matrix[i].append(Pion('blue', i, j))
                        else:
                            self.matrix[i].append(Pion('red', i, j))
                else:
                    self.matrix[i].append(Pion('red', i, j))
    def gagnant(self):
        """Retourne le type du joueur gagnant sinon 'vide' """
        cnt_rouge=0
        cnt_bleu=0
        for ligne in self.matrix:
            for elt in ligne:
                if elt.type=='blue':
                    cnt_blue+=1
                elif elt.type=='red':
                    cnt_rouge+=1
        if cnt_rouge==0:
            return 'blue'
        elif cnt_bleu==0:
            return 'red'
        return 'vide'
    def aff(self, f):
        for ligne in self.matrix:
            for elt in ligne:
                elt.aff(f)
        pg.display.flip()
    def search_target(self, t):
        """cherche  si un pion de type t peut manger,
            et retourne une liste de leurs coordonnées, et
            le mouvement  que doit faire le pion sous forme de
            tuple sinon []"""
        l=[]
        for i, ligne in enumerate(self.matrix):
            for j, elt in enumerate(ligne):
                if elt.type==t:
                    ###Recherche d'un coup par aspiration
                    ##HAUT
                    if i-1>=0:#pour ne pas avoir un IndexError
                        if self.get(i-1, j).type==opp(t):#être sûr que c'est bien un pion adverse qui est en haut
                            if i+1<5:#pour eviter un débordement d'indice
                                if self.get(i+1, j)==vide:#être sûr qu'il n'y a rien en bas pour éffectuer le mvt
                                    l.append(((i, j), 'south'))#on mémorise ces coordonnées et ce mvt
                    ##BAS
                    if i+1<5:
                        if self.get(i+1, j).type==opp(t):
                            if i-1>=0:
                                if self.get(i-1, j)==vide:
                                    l.append(((i, j), 'north'))
                    ##GAUCHE
                    if j-1>=0:
                        if self.get(i, j-1).type==opp(t):
                            if j+1<9:
                                if self.get(i, j+1)==vide:
                                    l.append(((i, j), 'east'))
                    ##DROITE
                    if j+1<9:
                        if self.get(i, j+1).type==opp(t):
                            if j-1>=0:
                                if self.get(i, j-1)==vide:
                                    l.append(((i, j), 'west'))
                    ##DIAGONALES
                    if (i+j)%2==0:#ne peut être éffectuer que si le pion se trouve sur un noeud pair
                        #HAUT-GAUCHE
                        if i-1>=0 and j-1>=0:
                            if self.get(i-1, j-1).type==opp(t):
                                if i+1<5 and j+1<9:
                                    if self.get(i+1, j+1)==vide:
                                        l.append(((i, j), 'se'))
                        #HAUT-DROITE
                        if i-1>=0 and j+1<9:
                            if self.get(i-1, j+1).type==opp(t):
                                if i+1<5 and j-1>=0:
                                    if self.get(i+1, j-1)==vide:
                                        l.append(((i, j), 'sw'))
                        #BAS-GAUCHE
                        if i+1<5 and j-1>=0:
                            if self.get(i+1, j-1).type==opp(t):
                                if i-1>=0 and j+1<9:
                                    if self.get(i-1, j+1)==vide:
                                        l.append(((i, j), 'ne'))
                        #BAS-DROITE
                        if i+1<5 and j+1<9:
                            if self.get(i+1, j+1).type==opp(t):
                                if i-1>=0 and j-1>=0:
                                    if self.get(i-1, j-1)==vide:
                                        l.append(((i, j), 'nw'))
                    ###Recherche d'un coup par repulsion
                    ##HAUT
                    if i-2>=0:
                        if self.get(i-2, j).type==opp(t):
                            if self.get(i-1, j)==vide:
                                l.append(((i, j), 'north'))
                    ##DROITE
                    if j+2<9:
                        if self.get(i, j+2).type==opp(t):
                            if self.get(i, j+1)==vide:
                                l.append(((i, j), 'east'))
                    ##BAS
                    if i+2<5:
                        if self.get(i+2, j).type==opp(t):
                            if self.get(i+1, j)==vide:
                                l.append(((i, j), 'south'))
                    ##GAUCHE
                    if j-2>=0:
                        if self.get(i, j-2).type==opp(t):
                            if self.get(i, j-1)==vide:
                                l.append(((i, j), 'west'))
                    ##DIAGONALES
                    if (i+j)%2==0:
                        #HAUT-DROITE
                        if i-2>=0 and j+2<9:
                            if self.get(i-2, j+2).type==opp(t):
                                if self.get(i-1, j+1)==vide:
                                    l.append(((i, j), 'ne'))
                        #BAS-DROITE
                        if i+2<5 and j+2<9:
                            if self.get(i+2, j+2).type==opp(t):
                                if self.get(i+1, j+1)==vide:
                                    l.append(((i, j), 'se'))
                        #BAS-DROITE
                        if i+2<5 and j-2>=0:
                            if self.get(i+2, j-2).type==opp(t):
                                if self.get(i+1, j-1)==vide:
                                    l.append(((i, j), 'sw'))
                        #HAUT-GAUCHE
                        if i-2>=0 and j-2>=0:
                            if self.get(i-2, j-2).type==opp(t):
                                if self.get(i-1, j-1)==vide:
                                    l.append(((i, j), 'nw'))
        return l
    def gen_move_list(self, t):
        ##Le joueur doit tjr prendre si un tel coup est possible
        if self.search_target(t)!=[]:#Si le joueur de type 't' peut prendre
            return self.search_target(t)
        ##Sinon il pourra déplacer n'importe quel pion de son choix
        liste=[]
        for i, ligne in enumerate(self.matrix):
            for j, elt in enumerate(ligne):
                if elt.type==t:
                    ##NORTH
                    if i-1>=0:
                        if self.get((i-1, j))==vide:
                            liste.append(((i, j), 'north'))
                    ##SOUTH
                    if i+1<5:
                        if self.get((i+1, j))==vide:
                            liste.append(((i, j), 'south'))
                    ##EAST
                    if j+1<9:
                        if self.get((i, j+1))==vide:
                            liste.append(((i, j), 'east'))
                    ##WEST
                    if j-1>=0:
                        if self.get((i, j-1))==vide:
                            liste.append(((i, j), 'west'))
                    if (i+j)%2==0:
                        ##NE
                        if i-1>=0 and j+1<9:
                            if self.get((i-1, j+1))==vide:
                                liste.append(((i, j), 'ne'))
                        ##NW
                        if i-1>=0 and j-1>=0:
                            if self.get((i-1, j-1))==vide:
                                liste.append(((i, j), 'nw'))
                        ##SE
                        if i+1<5 and j+1<9:
                            if self.get((i+1, j+1))==vide:
                                liste.append(((i, j), 'se'))
                        ##SW

                        if i+1<5 and j-1>=0:
                            if self.get((i+1, j-1))==vide:
                                liste.append(((i, j), 'sw'))
        return liste
    def do_move(self, depart, direction):
        if (depart, direction) in self.gen_move_list(self.get(depart[0], depart[1]).type):
            self.set(depart[0], depart[1], self.get(depart[0], depart[1]))
            self.get(depart[0], depart[1]).move_to(direction)
            self.set(depart[0], depart[1], vide)
            return True
        print("Requested move can't be done: ", depart, ' to ', direction)
        return False
    def __str__(self):
        s=''
        for ligne in self.matrix:
            for elt in ligne:
                if elt.type=='blue':
                    s+='1\t'
                elif elt.type=='red':
                    s+='2\t'
                else:
                    s+='0\t'
            s+='\n\n'
        return s
