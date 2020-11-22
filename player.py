#-*- coding:Latin:1 -*-

from stone import*

class Player:
    def __init__(self, t):
        self.type=t
        self.pionsPrises=0
        self.pionsCaptures=0
        self.pions=list()
        if t=='blue':
            for i in range(3):
                self.pions.append([])
                for j in range(9):
                    if i<2:
                        self.pions[i].append(Pion('blue', i, j))
                    else:
                        if j<4:
                            if j%2==0:
                                self.pions[i].append(Pion('blue', i, j))
                        elif j>4:
                            if j%2:
                                self.pions[i].append(Pion('blue', i, j))
        if t=='red':
            for i in range(2, 5):
                self.pions.append([])
                for j in range(9):
                    if i==2:
                        if j<4:
                            if j%2:
                                self.pions[i].append(Pion('red', i, j))
                        elif j>4:
                            if j%2==0:
                                self.pions[i].append(Pion('red', i, j))
                    else:
                        self.pions[i].append(Pion('red', i, j))

    def
