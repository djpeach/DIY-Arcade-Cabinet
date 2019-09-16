#dirt.py
import pygame, sys

class Dirt(pygame.sprite.Sprite):
    def __init__(self, player, x, y, width, height):
        pygame.sprite.Sprite.__init__(self)
        self.dirting = False
        self.currentSprite = 0
        self.player = player
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.dirt_0 = pygame.image.load("assets/dirt_0.png")
        self.dirt_1_left = pygame.image.load("assets/dirt_1_left.png")
        self.dirt_2_left = pygame.image.load("assets/dirt_2_left.png")
        self.dirt_1_right = pygame.image.load("assets/dirt_1_right.png")
        self.dirt_2_right = pygame.image.load("assets/dirt_2_right.png")
        self.image = self.dirt_0
        self.rect = self.image.get_rect()
        self.dirt_0 = pygame.transform.scale(self.dirt_0, (self.rect.width*4, self.rect.height*4))
        self.dirt_1_left = pygame.transform.scale(self.dirt_1_left, (self.rect.width*4, self.rect.height*4))
        self.dirt_2_left = pygame.transform.scale(self.dirt_2_left, (self.rect.width*4, self.rect.height*4))
        self.dirt_1_right = pygame.transform.scale(self.dirt_1_right, (self.rect.width*4, self.rect.height*4))
        self.dirt_2_right = pygame.transform.scale(self.dirt_2_right, (self.rect.width*4, self.rect.height*4))
        self.image = self.dirt_0
        self.rect = self.image.get_rect()
        self.rect.y = self.player.rect.y

    def update(self):
        if(self.player.currentSprite < 3 or self.player.currentSprite > 4):
            self.dirt()
            self.rect.x = self.player.rect.x + 5 * (4 - self.player.currentSprite)
            if(self.player.currentSprite < 3):
                if(self.currentSprite == 0):
                    self.image = self.dirt_1_left
                else:
                    self.image = self.dirt_2_left
            else:
                if(self.currentSprite == 0):
                    self.image = self.dirt_1_right
                else:
                    self.image = self.dirt_2_right
        else:
            self.image = self.dirt_0
    def dirt(self):
        if(self.currentSprite == 0):
            self.currentSprite = 1
        else:
            self.currentSprite = 0