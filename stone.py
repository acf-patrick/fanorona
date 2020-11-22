__autor__="Tojoniaina Patrick"

#-*- coding:Latin-1 -*-

import pygame
from const import*

class Pion:
    def __init__(self, t='vide', x=-1, y=-1):
        self.type=t
        if t=='red':
            self.image=red
        elif t=='blue':
            self.image=blue
        self.pos=list()
        self.status='disabled'     #permet de savoir dans quel etat est le pion
        self.history=[] #cette liste va nous permettre de restreindre les mvt pour que
        if t!='vide':       #le pion en quéstion ne revienne sur ses anciennes positions
            self.position=carte[x][y]#position en pixel du pion
            self.pos=[x,y]
    def __eq__(self, pion):
        return pion.type==self.type

    def set_status(self, status):
        self.status=status
        if status=='disabled':
            if self.type=='blue':
                self.image=blue
            elif self.type=='red':
                self.image=red
        if status=='selected':
            if self.type=='blue':
                self.image=selected_blue
            elif self.type=='red':
                self.image=selected_red
        elif status=='deleted':
            if self.type=='blue':
                self.image=deleted_blue
            elif self.type=='red':
                self.image=deleted_red

    def move_to(self, direction):
        if direction=='north':
            self.pos[0]-=1
        if direction=='east':
            self.pos[1]+=1
        if direction=='south':
            self.pos[0]+=1
        if direction=='west':
            self.pos[1]-=1
        if (self.pos[0]+self.pos[1])%2==0:
            if direction=='ne':
                self.pos[0]-=1
                self.pos[1]+=1
            if direction=='se':
                self.pos[0]+=1
                self.pos[1]+=1
            if direction=='sw':
                self.pos[0]+=1
                self.pos[1]-=1
            if direction=='nw':
                self.pos[0]-=1
                self.pos[1]-=1

    def aff(self, screen):
        if  self.type!='vide':
            screen.blit(self.image, self.position)

vide=Pion()
