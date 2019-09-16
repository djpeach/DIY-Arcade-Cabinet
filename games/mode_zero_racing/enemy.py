#enemy.py
import pygame, sys

class Enemy(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, roadRatio, enemyCar):
        pygame.sprite.Sprite.__init__(self)
        self.enemyCar = enemyCar
        self.value = 1
        self.turnProgress = 0
        self.x = self.enemyCar.x - (self.enemyCar.width/2)*self.value*.5
        self.y = y
        self.left = False
        self.right = False
        self.width = width
        self.height = height
        self.image = self.enemyCar.getCurrentImage()
        self.rect = self.image.get_rect()
        self.originalRect = self.rect
        self.roadRatio = roadRatio
        self.rect.center = (self.x, self.y)

    def getCar(self):
        return self.enemyCar

    def update(self):
        self.rect = self.image.get_rect()
        self.x = self.enemyCar.width/2 - (self.enemyCar.width/2 - self.enemyCar.x)*self.value
        #TODO: adjust for turning
        if(self.left):
            i = self.height - self.y
            turnPos = (i/(self.height*self.roadRatio))*self.turnProgress
            self.x -= i*turnPos
        else: 
            i = self.height - self.y
            turnPos = (i/(self.height*self.roadRatio))*self.turnProgress
            self.x += i*turnPos


        self.rect.center = (self.x, self.y)

    def scale(self, value, turnProgress):
        self.value = value
        self.turnProgress = turnProgress
        self.left = self.enemyCar.isLeft
        self.right = self.enemyCar.isRight
        self.rect.center = (self.x, self.y)
        self.image = pygame.transform.smoothscale(self.enemyCar.getCurrentImage(), (int(self.originalRect.width*value), int(self.originalRect.height*value)))
        self.rect = self.image.get_rect()

    