import pygame, random
from pygame.locals import *


HEIGHT = 600
WIDTH = 600

pygame.init()
tela = pygame.display.set_mode((HEIGHT, WIDTH))
pygame.display.set_caption("Snake Game by SH12")

snake = [(300, 300), (310, 300), (310, 310)]

skin_color = (100, 200, 50)
skin = pygame.Surface((10, 10))
skin.fill(skin_color)

appos = (330, 330)
apple = pygame.Surface((10, 10))
apple.fill((200, 50, 65))

clock = pygame.time.Clock()

UP = 0
DOWN= 1
LEFT = 2
RIGHT = 3

def moveDir(tup, dir):
    if dir == UP:
        return (tup[0], (tup[1] - 10)%WIDTH)
    if dir == DOWN:
        return (tup[0], (tup[1] + 10)%WIDTH)
    if dir == RIGHT:
        return ((tup[0] + 10)%HEIGHT, tup[1])
    if dir == LEFT:
        return ((tup[0] - 10)%HEIGHT, tup[1])


direction = 0
gaming = True

while True:

    clock.tick(10)

    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
        
        if event.type == KEYDOWN:
            if event.key == K_UP and direction != DOWN:
                direction = UP
            if event.key == K_DOWN and direction != UP:
                direction = DOWN
            if event.key == K_LEFT and direction != RIGHT:
                direction = LEFT
            if event.key == K_RIGHT and direction != LEFT:
                direction = RIGHT

    tela.fill((0, 0, 0))
    tela.blit(apple, appos)

    if(snake[0] == appos):
        snake.append(snake[-1])
        appos = (random.randint(0, HEIGHT/10 - 1)*10, random.randint(0, WIDTH/10 - 1)*10)
    
    if gaming:
        snake.insert(0, moveDir(snake[0], direction) )
        snake.pop()

    color = skin_color
    
    for i in range(0, len(snake)):
        pos = snake[i]
        skin.fill(color)
        tela.blit(skin, pos)

        if gaming:
            color = (color[0], (color[1] - 10) % 256, (color[2] + 5) % 255)
        else:
            color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))

        if( i > 0 and snake[0] == pos):
            gaming = False
        



    pygame.display.update()