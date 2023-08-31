#!/usr/bin/env python3
import pygame as pg
import csv

# Todo Handle the text!
class Shape:
    def __init__(self, name, x, y, sx, sy, color) -> None:
        self.name = name
        self.x = x
        self.y = y
        self.sx = sx
        self.sy = sy
        self.color = color
        

        

class Rect(Shape):
    def __init__(self, name, x, y, sx, sy, color, w, h) -> None:
        super().__init__(name, x, y, sx, sy, color)
        self.w = w
        self.h = h
        self.surface = pg.Surface((self.w, self.h))
        self.rect = self.surface.get_rect(center=(self.x, self.y))
        
    def draw(self, win):
        #self.text_pos = self.text.get_rect(center=(self.x, self.y))
        pg.draw.rect(win, self.color, self.rect)
        #win.blit(self.text, self.text_pos) 
        
    def update(self):
        
        if self.rect.left <= 0 or self.rect.right >= 800:
            self.sx *= -1
        elif self.rect.top <= 0 or self.rect.bottom >= 600:
            self.sy *= -1
        self.rect.x += self.sx
        self.rect.y += self.sy

class Circle(Shape):
    def __init__(self, name, x, y, sx, sy, color, r) -> None:
        super().__init__(name, x, y, sx, sy, color)
        self.r = r
        
    def draw(self, win):
        #self.text_pos = self.text.get_rect(center=(self.x, self.y))
        pg.draw.circle(win, self.color, (self.x, self.y), self.r)
        #win.blit(self.text, self.text_pos)
       
    def update(self):
        if self.x - self.r <= 0 or self.x + self.r >= 800:
            self.sx *= -1
        elif self.y - self.r <= 0 or self.y + self.r >= 600:
            self.sy *= -1
        self.x += self.sx
        self.y += self.sy

class Engine:
    def __init__(self, width, height, title: str | None = "C4003") -> None:
        self.width = width
        self.height= height
        self.window = pg.display.set_mode((self.width, self.height))
        self.isopen = True
        self.shapes = []
        pg.display.set_caption(title)
    
    def run(self):
        while self.isopen:
            self._process_input()
            self._update()
            self._render()
        pg.quit()


    def _process_input(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.isopen = False

    def _update(self):
        for shape in self.shapes:
            shape.update()

    def _render(self):
        self.window.fill((255, 255, 255))
        for shape in self.shapes:
            shape.draw(self.window)
        pg.display.update()

    def set_shapes(self, shapes_list: list):
        self.shapes = shapes_list
   
shapes = []
if __name__ == "__main__":
    pg.init()
    with open("config.csv", "r") as f:
        line = csv.reader(f)
        for l in line:
            command = l[0].lower()
            if command == 'window':
                width, height = int(l[1]), int(l[2])
            elif command == "font":
                print(l[1], l[2], (l[3], l[4], l[5]))
            elif command == "circle":
                shapes.append(Circle(l[1], int(l[2]), int(l[3]), float(l[4]), float(l[5]), (int(l[6]), int(l[7]), int(l[8])), int(l[9])))
            elif command == "rectangle":
                shapes.append(Rect(l[1], int(l[2]), int(l[3]), float(l[4]), float(l[5]), (int(l[6]), int(l[7]), int(l[8])), int( l[9]), int(l[10])))

    
    eng = Engine(width, height)
    eng.set_shapes(shapes)
    eng.run()