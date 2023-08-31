import pygame
import sys
import csv

# Initialize Pygame
pygame.init()

# Load window size from config.txt
with open("config.csv", "r") as f:
    line = csv.reader(f)
    for l in line:
        if l[0] == 'window':
            width, height = int(l[1]), int(l[2])

# Create the Pygame window
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Pygame Window with Configured Size")

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Clear the screen
    screen.fill((255, 255, 255))

    # Add your drawing or game logic here

    # Update the display
    pygame.display.flip()

# Quit Pygame
pygame.quit()
sys.exit()
