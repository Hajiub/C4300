#!/usr/bin/env python3
import pygame as pg
import sys

# Initialize pygame
pg.init()

# Create the game window
win = pg.display.set_mode((800, 600))

class Font:
    def __init__(self, font_path, size, color) -> None:
        self.color = color
        self.font = pg.font.Font(font_path, size)
        
    def render(self, name):
        return self.font.render(name, True, self.color)
        
class Shape:
    def __init__(self, name, x, y, sx, sy, color, font) -> None:
        self.name = name
        self.x = x
        self.y = y
        self.sx = sx
        self.sy = sy
        self.color = color
        self.font = font.font
        self.text = font.render(name)

        

class Rect(Shape):
    def __init__(self, name, x, y, sx, sy, color, w, h, font) -> None:
        super().__init__(name, x, y, sx, sy, color, font)
        self.w = w
        self.h = h
        self.surface = pg.Surface((self.w, self.h))
        self.rect = self.surface.get_rect(center=(self.x, self.y))
        
    def draw(self, win):
        self.text_pos = self.text.get_rect(center=(self.x, self.y))
        pg.draw.rect(win, self.color, self.rect)
        win.blit(self.text, self.text_pos) 
        
    def update(self):
        
        if self.rect.left <= 0 or self.rect.right >= 800:
            self.sx *= -1
        elif self.rect.top <= 0 or self.rect.bottom >= 600:
            self.sy *= -1
        self.rect.x += self.sx
        self.rect.y += self.sy

class Circle(Shape):
    def __init__(self, name, x, y, sx, sy, color, r, font) -> None:
        super().__init__(name, x, y, sx, sy, color, font)
        self.r = r
        
    def draw(self, win):
        self.text_pos = self.text.get_rect(center=(self.x, self.y))
        pg.draw.circle(win, self.color, (self.x, self.y), self.r)
        win.blit(self.text, self.text_pos)
       
    def update(self):
        if self.x - self.r <= 0 or self.x + self.r >= 800:
            self.sx *= -1
        elif self.y - self.r <= 0 or self.y + self.r >= 600:
            self.sy *= -1
        self.x += self.sx
        self.y += self.sy

rects = []
circles = []

def load_config(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        
        for line in lines:
            data = line.split()
            shape_type = data[0].lower()

            if shape_type == 'font':
                font = Font(data[1], int(data[2]), tuple(map(int, data[3:6])))
            
            elif shape_type == 'circle':
                circles.append(Circle(data[1], int(data[2]), int(data[3]), float(data[4]), float(data[5]),
                                      tuple(map(int, data[6:9])), int(data[9]), font))
                
            elif shape_type == 'rectangle':
                rects.append(Rect(name=data[1], x=int(data[2]), y=int(data[3]), sx=int(data[4]), sy=int(data[5]),
                                  color=tuple(map(int, data[6:9])), w=int(data[9]), h=int(data[10]), font=font))

clock = pg.time.Clock()

def main():
    load_config('config.txt')
    
    running = True
    while running:
        win.fill((255, 255, 255))  # Clear the screen

        for event in pg.event.get():
            if event.type == pg.QUIT:
                running = False

        for rect in rects:
            rect.update()
            rect.draw(win)
        # for circle in circles:
        #     circle.update()
        #     circle.draw(win)
        pg.display.flip()

    pg.quit()

if __name__ == '__main__':
    main()
