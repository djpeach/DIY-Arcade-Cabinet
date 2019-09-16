#car.py
import pygame, sys
from background import Background

class Car(pygame.sprite.Sprite):
    def __init__(self, player, x, y, width, height, roadRatio):
        pygame.sprite.Sprite.__init__(self)
        self.player = player #1 or 2
        #fixing it to not move but rather just change values for a centered camera
        self.x = x
        self.y = y
        self.position = 0
        self.speed = 0
        self.speedX = 0
        self.minSpeed = 0
        self.maxSpeed = 0.2
        self.minSpeedX = -15
        self.maxSpeedX = 15
        self.width = width
        self.height = height
        self.rightBound = self.width
        self.grassLength = 150
        self.inGrass = False
        self.turnProgress = 0
        self.turning = False
        self.isLeft = False
        self.isRight = False
        self.hasWon = False
        self.currentSprite = 0
        self.load_images()
        self.roadRatio = roadRatio
        self.background = Background(self.width, self.height, roadRatio)
        
        self.engineChannel = pygame.mixer.Channel(0)
        self.engine = pygame.mixer.Sound('assets/engine.wav')
        self.engine.set_volume(1)

    def load_images(self):

        if(self.player == 1):
            self.image = pygame.image.load("assets/car.png")
            self.car_left_3 = pygame.image.load("assets/car_left_3.png")
            self.car_left_2 = pygame.image.load("assets/car_left_2.png")
            self.car_left_1 = pygame.image.load("assets/car_left_1.png")
            self.car_right_1 = pygame.image.load("assets/car_right_1.png")
            self.car_right_2 = pygame.image.load("assets/car_right_2.png")
            self.car_right_3 = pygame.image.load("assets/car_right_3.png")
        else:
            self.image = pygame.image.load("assets/car2.png")
            self.car_left_3 = pygame.image.load("assets/car2_left_3.png")
            self.car_left_2 = pygame.image.load("assets/car2_left_2.png")
            self.car_left_1 = pygame.image.load("assets/car2_left_1.png")
            self.car_right_1 = pygame.image.load("assets/car2_right_1.png")
            self.car_right_2 = pygame.image.load("assets/car2_right_2.png")
            self.car_right_3 = pygame.image.load("assets/car2_right_3.png")

        self.rect = self.image.get_rect()
        self.image = pygame.transform.scale(self.image, (self.rect.width*4, self.rect.height*4))
        self.car_left_3 = pygame.transform.scale(self.car_left_3, (self.rect.width*4, self.rect.height*4))
        self.car_left_2 = pygame.transform.scale(self.car_left_2, (self.rect.width*4, self.rect.height*4))
        self.car_left_1 = pygame.transform.scale(self.car_left_1, (self.rect.width*4, self.rect.height*4))
        self.car_right_1 = pygame.transform.scale(self.car_right_1, (self.rect.width*4, self.rect.height*4))
        self.car_right_2 = pygame.transform.scale(self.car_right_2, (self.rect.width*4, self.rect.height*4))
        self.car_right_3 = pygame.transform.scale(self.car_right_3, (self.rect.width*4, self.rect.height*4))
        self.rect = self.image.get_rect()
        self.rect.center = (self.x, self.y)
        self.car_images = [self.car_left_3, self.car_left_2, self.car_left_1,
                            self.image, self.car_right_1, self.car_right_2,
                            self.car_right_3]
        self.currentSprite = len(self.car_images)//2

    def getCurrentImage(self):
        return self.image

    def quiet(self):
        print("STOPPING")
        self.engineChannel.stop()

    
    def straighten(self):
        center = len(self.car_images)//2
        if self.currentSprite < center:
            self.currentSprite += 1
            self.image = self.car_images[self.currentSprite]
            self.rect = self.image.get_rect()
            self.rect.center = (self.x, self.y)
        elif self.currentSprite > center:
            self.currentSprite -= 1
            self.image = self.car_images[self.currentSprite]
            self.rect = self.image.get_rect()
            self.rect.center = (self.x, self.y)

    def check_bounds(self):
        #screen bounds
        if self.rect.centerx > self.rightBound:
            self.rect.centerx = self.rightBound
            self.speedX = 0
        elif self.rect.centerx < 0:
            self.rect.centerx = 0
            self.speedX = 0

        #grass bounds
        if self.rect.centerx > self.rightBound- self.grassLength:
            self.inGrass = True
        elif self.rect.centerx < self.grassLength:
            self.inGrass = True
        else:
            self.inGrass = False

        

    def apply_drag(self):
        if(self.inGrass):
            self.speed *= .8
            if(self.speedX > 0.6):
                self.speedX -= 0.6
            elif(self.speedX <-0.6 ):
                self.speedX += 0.6
            else:
                self.speedX = 0
        else:
            self.speed *= .97
            if(self.speed > 0.001):
                self.speed -= 0.001
            elif(self.speed < -0.001):
                self.speed += 0.001
            else:
                self.speedX = 0
            if(self.speedX > 0.1):
                self.speedX -= 0.1
            elif(self.speedX < -0.1 ):
                self.speedX += 0.1
            else:
                self.speedX = 0

        self.speedX *= .98
    
    def physics(self):
        self.x += self.speedX

        self.rect.center = (self.x, self.y)
        self.position += self.speed
        
        #if self.x > self.screenWidth:
        #    self.x = self.screenWidth
        #if self.x < 0:
        #    self.x = 0

    def accelerate(self):
        if(not self.engineChannel.get_busy()):
            self.engineChannel.play(self.engine, -1)
        self.speed += .006
        if self.speed > self.maxSpeed:
            self.speed = self.maxSpeed
    
    def decelerate(self):
        self.speed -= .006
        if self.speed < self.minSpeed:
            self.speed = self.minSpeed

    def left(self):
        if(self.speed > 0.002):
            self.speed -= 0.002
            self.currentSprite -= 1
            if(self.currentSprite < 0):
                self.currentSprite = 0
            self.image = self.car_images[self.currentSprite]
            self.rect = self.image.get_rect()
            self.rect.center = (self.x, self.y)

            self.speedX -= 1
            if(self.speedX > self.maxSpeedX):
                self.speedX = self.maxSpeedX
    
    def right(self):
        if(self.speed > 0.002):
            self.speed -= 0.002
            self.currentSprite += 1
            if((self.currentSprite == len(self.car_images))):
                self.currentSprite = len(self.car_images) - 1
            self.image = self.car_images[self.currentSprite]
            self.rect = self.image.get_rect()
            self.rect.center = (self.x, self.y)

            self.speedX += 1
            if(self.speedX < self.minSpeedX):
                self.speedX = self.minSpeedX

    def drift(self, intensity):
        self.speedX += (8*self.speed*self.turnProgress*intensity)

    def update(self):
        self.physics()
        self.apply_drag()
        self.check_bounds()

    def getX(self):
        return self.x

    def getSpeed(self):
        return self.speed

    def getPosition(self):
        return self.position

    def getPlayerNumber(self):
        return self.player

    def calculateTurnProgress(self):
        if(self.turnProgress < 0):
            self.turnProgress = 0


    def getTurnProgress(self):
        self.calculateTurnProgress()
        return self.turnProgress

    def incrementTurnProgress(self, target):
        if(self.getTurnProgress() < target + 0.1):
            self.turnProgress += 0.1
        self.calculateTurnProgress()

    def setTurnLeft(self, left):
        self.isLeft = left
    
    def setTurnRight(self, right):
        self.isRight = right

    def decrementTurnProgress(self, target):
        if(self.getTurnProgress() > target - 0.1):
            self.turnProgress -= 0.1
        self.calculateTurnProgress()

    def isTurning(self):
        return self.turning

    def getBackground(self):
        return self.background