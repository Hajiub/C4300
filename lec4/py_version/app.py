#!/usr/bin/env python3
import pygame as pg

class Shape:
    def __init__(self, name, x, y, sx, sy, color):
        self.name = name
        self.x = x
        self.y = y
        self.sx = sx
        self.sy = sy
        self.color = color

class Rect(Shape):
    def __init__(self, name, x, y, sx, sy, color, w, h):
        super().__init__(name, x, y, sx, sy, color)
        self.width = w
        self.height = h
    
    def draw(self, win):
        pg.draw.rect(win, self.color, (self.x, self.y, self.width, self.height))

    def update(self):
        self.x += self.sx
        self.y += self.sy
        # Implement additional update logic if needed

class Circle(Shape):
    def __init__(self, name, x, y, sx, sy, color, r):
        super().__init__(name, x, y, sx, sy, color)
        self.r = r
        
    def draw(self, win):
        pg.draw.circle(win, self.color, (self.x, self.y), self.r)

    def update(self):
        self.x += self.sx
        self.y += self.sy
        # Implement additional update logic if needed

class Engine:
    def __init__(self, width: int, height: int, title: str) -> None:
        self.width = width
        self.height = height
        self.title = title
        self.window = pg.display.set_mode((self.width, self.height))
        pg.display.set_caption(self.title)

        self.shapes = []  # List to hold all shapes in the engine

    def initialize(self):
        pg.init()

    def handle_input(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.quit()

    def update(self, delta_time):
        for shape in self.shapes:
            shape.update()

    def render(self):
        self.window.fill((0, 0, 0))
        for shape in self.shapes:
            shape.draw(self.window)
        pg.display.flip()

    def add_shape(self, shape):
        self.shapes.append(shape)

    def run(self):
        self.initialize()
        clock = pg.time.Clock()
        running = True
        while running:
            delta_time = clock.tick(60) / 1000.0  
            self.handle_input()
            self.update(delta_time)
            self.render()

    def quit(self):
        pg.quit()
        quit()

if __name__ == "__main__":
    engine = Engine(800, 600, "Pygame Engine Example")
    
    # Create and add shapes to the engine
    rect = Rect("Rectangle", 100, 100, 1, 0, (255, 0, 0), 100, 50)
    circle = Circle("Circle", 300, 300, 0, 1, (0, 0, 255), 30)

    engine.add_shape(rect)
    engine.add_shape(circle)

    engine.run()
