
__autor__="Tojoniaina Patrick"

#-*- coding:Latin-1 -*-

import pygame

SIZE= 500, 300
human=pygame.image.load("data/human.jpg")
computer=pygame.image.load("data/computer.jpg")
deleted_blue=pygame.image.load("data/deleted_blue.png")
deleted_red=pygame.image.load("data/deleted_red.png")
blue=pygame.image.load("data/blue.png")
red=pygame.image.load("data/red.png")
selected_blue=pygame.image.load("data/selected_blue.png")
selected_red=pygame.image.load("data/selected_red.png")
background=pygame.image.load("data/background.jpg")

MIN_NEW=(5, 5)
MAX_NEW=(27, 27)
MIN_SAVE=(40, 5)
MAX_SAVE=(58, 28)
MIN_RESTART=(439, 5)
MAX_RESTART=(462, 30)
MIN_UNDO=(467, 5)
MAX_UNDO=(492, 29)
POS_J1=(109, 5)
POS_J2=(300,5)
POS_Pion1=(31, 274)
POS_Pion2=(106, 274)

INFINI=10000
black=(0,0,0)
carte=[]
for i in range(5):
    carte.append([])
    for j in range(9):
        carte[i].append((35+50*j, 35+50*i))

def opp(t):
    if t=='red':
        return 'blue'
    if t=='blue':
        return 'red'
