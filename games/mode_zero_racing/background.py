#background.py
import pygame, sys
from pygame.locals import *

class Background(pygame.sprite.Sprite):
    def __init__(self, width, height, roadRatio):
        pygame.sprite.Sprite.__init__(self)
        self.imageLeft = pygame.image.load("assets/background.png")
        self.imageRight = pygame.image.load("assets/background.png")
        self.rectLeft = self.imageLeft.get_rect()
        self.rectRight = self.imageRight.get_rect()
        self.height = int(height * (1-roadRatio))
        self.width = int(self.height* (self.rectLeft.width/self.rectLeft.height))
        self.imageLeft = pygame.transform.scale(self.imageLeft, (self.width, self.height))
        self.imageRight = pygame.transform.scale(self.imageRight, (self.width, self.height))
        self.offset = 0

    def offsetBackground(self, offset):
        self.offset += offset
        if(self.offset > self.width):
            self.offset -= self.width
        elif(self.offset < 0):
            self.offset += self.width
        self.rectRight.x = self.offset
        self.rectLeft.x = self.offset - self.width

    def getLeftImage(self):
        return self.imageLeft

    def getLeftRect(self):
        return self.rectLeft

    def getRightImage(self):
        return self.imageRight

    def getRightRect(self):
        return self.rectRight

    
    
