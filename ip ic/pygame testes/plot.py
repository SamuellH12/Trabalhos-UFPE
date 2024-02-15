import pygame, random
from pygame.locals import *


WIDTH = 900
HEIGTH = 700
DELTAX = WIDTH / 2
DELTAY = HEIGTH / 2
RED = (200, 0, 0)
GREEN = (0, 200, 0)
BLUE = (0, 0, 200)
PURPLE = (100, 0, 150)
C = 5
idg = 0
giro = [(-1, 1), (-1, -1), (1, -1), (1, 1)]
v = [100, 0]

pygame.init()
tela = pygame.display.set_mode((WIDTH, HEIGTH))
pygame.display.set_caption("Plot by SH12")
clock = pygame.time.Clock()


def DOT(x, y ):
    return ( x*-C + DELTAX, y*C + DELTAY )


def autoVetor(x, y):
    pt = DOT(x, y)
    dt = TL(x, y)
    pygame.draw.line(tela, PURPLE , dt, pt, 4)



# − i*(raiz(31)​+i) / 2
def vortice( x , y ):
   return DOT( 3*x - 7*y,  2*x - 2 * y)


# autovalor {2} autovetor (1, 1)
def Reta( x , y ):
   return DOT(  x + y  ,  x + y )


# autovalores: {2}, autovetores:{ (1, 1) } 
def RetaVordice( x , y ):
   return DOT(  x+y , -x + 3*y )


# autovalores: {4, -3}, autovetores:{ (3, 1), (-1, 2)) } 
def Xis( x , y ):
   return DOT( 1.5*x + 1.5*y , x - y)


# autovalores: {2, 1}, autovetores:{ (2, 0), (0, 1) } 
def Cruz( x , y ):
   return DOT(  2*x , 3*y )


# autovalores {i, -i}, autovetores { (i, 1), (-i, 1) }
def Irreal( x , y ):
   return DOT(  y , -x )


def base( x , y ):
   return DOT( x, y )

def TL( x , y ):
   return Xis(x, y)



while True:


    clock.tick(30)

    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
    

    tela.fill((0, 0, 0))

    
    pygame.draw.line(tela, RED, (WIDTH/2, 0), (WIDTH/2, HEIGTH), 2)
    pygame.draw.line(tela, RED, (0, HEIGTH/2), (WIDTH, HEIGTH/2), 2)


    LIM = 30
    md = 2
    C = 10

    # retas
    for x in range(-LIM, LIM + 1):
        for y in range(-LIM, LIM + 1):
            pt = DOT(x, y)
            dt = TL(x, y)

            if(x % md == 0 and y % md == 0):
                pygame.draw.line(tela, (0, 0, 200, 50), dt, pt, 1)

            pygame.draw.circle(tela, RED, pt, 1)
            pygame.draw.circle(tela, GREEN, dt, 1)

    # for x in range(-LIM, LIM + 1):
    #     for y in range(-LIM, LIM + 1):
    #         pt = DOT(x, y)
    #         dt = TL(x, y)
    #         pygame.draw.circle(tela, RED, pt, 1)

    # for x in range(-LIM, LIM + 1):
    #     for y in range(-LIM, LIM + 1):
    #         pt = DOT(x, y)
    #         dt = TL(x, y)
    #         pygame.draw.circle(tela, GREEN, dt, 1)

    

    for i in range(-100, 100):
        v0 = v
        v1 = [v0[0] * i / 100, v0[1] * i / 100]
        pt1 = DOT(v1[0], v1[1])
        pt0 = DOT(v0[0], v0[1])
        dt1 = TL(v1[0], v1[1])
        dt0 = TL(v0[0], v0[1])

        pygame.draw.line(tela, (0, 150, 100), pt0, pt1, 2)
        pygame.draw.line(tela, (100, 0, 100), dt0, dt1, 3)
        pygame.draw.circle(tela, RED, pt0, 1)
        pygame.draw.circle(tela, GREEN, dt0, 1)

    for i in range(-100, 100):
        v0 = v
        v1 = [v0[0] * i / 100, v0[1] * i / 100]

        pt1 = DOT(v1[0], v1[1])
        pt0 = DOT(v0[0]/100, v0[1]/100)
        
        dt1 = TL(v1[0], v1[1])
        dt0 = TL(v0[0]/100, v0[1]/100)

        pygame.draw.circle(tela, RED, pt0, 3)
        pygame.draw.circle(tela, RED, pt1, 3)
        pygame.draw.circle(tela, GREEN, dt0, 3)
        pygame.draw.circle(tela, GREEN, dt1, 3)


    v[0] += giro[idg][0]
    v[1] += giro[idg][1]

    if v[1] % 100 == 0:
        idg = (idg+1)%4

    pygame.draw.line(tela, RED, (WIDTH/2, 0), (WIDTH/2, HEIGTH), 2)
    pygame.draw.line(tela, RED, (0, HEIGTH/2), (WIDTH, HEIGTH/2), 2)


    pygame.display.update()




'''
Melhor Visualização do Irreal, Vórtice, RetaVortice e Reta
    LIM = 30
    md = 2
    C = 10
'''