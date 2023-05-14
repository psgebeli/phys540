# This script is a simulation of the first four planets in the solar system orbiting around the sun. 

# Preamble 
import pygame as pg
import math 
import numpy as np

# Pygame Initialization
pg.init()
width, height = 800, 800 # 800 Pixel x 800 Pixel Window
win = pg.display.set_mode((width, height))
pg.display.set_caption("Solar System Simulation")
font = pg.font.SysFont("comicsans", 16)

# Defining Colors
black = (0, 0, 0)
white = (255, 255, 255)
yellow = (255, 255, 0)
red = (255, 0, 0)
blue = (0, 0, 255)
orange = (255, 102, 0)

# Class that stores the sun and each of the four planets as an object with a mass, a radius, a position, a velocity, and a color.
# NOTES
# 1. The radius is not the real radius of the body in space, but rather, an arbitrary number so that I could make the planets
# look the appropriate size on the window. They are relatively scaled, but otherwise arbitrary. 
# 2. The position and velocity parameters are 2D vectors using numpy.
# 3. The position parameter was defined to be x = perihelion distance (distance of closest approach) and y = 0, using NASA data. 
# 4. The velocity parameter was defined with vx = 0 and vy = some speed that is sufficient to start an elliptical orbit. These values were
# taken from https://fiftyexamples.readthedocs.io/en/latest/gravity.html
class CelestialObject:
    au = 1.495978707e11 # astronomical units (m), makes defining distances easier
    scale = 250 / au # 250 pixels per au
    G = 6.67428e-11 # gravitational constant 
    dt = 3600*24 # timestep (seconds in one day)

    def __init__(self, mass, radius, position, velocity, color):
        self.mass = mass 
        self.radius = radius 
        self.position = np.array(position)
        self.velocity = np.array(velocity)
        self.color = color

        self.orbit = [] # will store positions travelled through so that we can draw a line through the planets path
        self.isSun = False # boolean that is true only for the sun
        self.distance_to_sun = 0 # we want to print out the distance to the sun for each planet so we will update
        # this value accordingly

    def draw(self, win): # function to draw an object and its line of travel in the pygame window
        position = (self.position * self.scale) + np.array([width / 2, height / 2]) # second term is to offset to center of window
        if len(self.orbit) > 2: # i.e if the object is travelling
            updated_points = []
            for point in self.orbit:
                position = point
                position = position * self.scale + np.array([width / 2, height / 2])
                updated_points.append(position) # scaled/offset version of self.orbit[]
            pg.draw.lines(win, self.color, False, updated_points, 2) # draw the path
        pg.draw.circle(win, self.color, position, self.radius) # draw the circle
        if not self.isSun: # if its a planet and not the sun, print the distance to the sun (updated later)
            distance_text = font.render(f"{round(self.distance_to_sun/1000, 1)}km", 1, white)
            win.blit(distance_text, (position[0] - distance_text.get_width()/2, position[1] - distance_text.get_height()/2))

    def get_accel(self, other): # function to get the acceleration due to gravity of an object due to another object
                
                r = other.position - self.position
                rmag = np.linalg.norm(r)
                rhat = r / rmag 

                if other.isSun:
                    self.distance_to_sun = rmag

                # F = Gm1m2rhat/rmag**2 and F = m1a 
                # ==> a = Gm2rhat/rmag**2
                a = (self.G * other.mass * rhat) / rmag**2
                return a
    
    def update(self, celestialobjects): # function to move the object based on its acceleration and using Verlet-Velocity method

        total_a = np.array([0,0], dtype=np.float64)
        next_a = np.array([0,0], dtype=np.float64)
        for obj in celestialobjects: # get_accel gives us the acceleration due to some other object. we want the total
            # acceleration due to the influence of every other objects gravity.
            if self == obj:
                continue # dont calculate the gravity on itself
            a = self.get_accel(obj) 
            total_a += a # the total_a is the a with respect to each object in the celestial_objects array, which
            # is defined in main()
            
        next_pos = self.position + (self.velocity * self.dt) + (0.5 * total_a * self.dt**2)
        self.position = next_pos # update position using Verlet-Velocity method

        for obj in celestialobjects:
            if self == obj:
                continue
            a = self.get_accel(obj)
            next_a += a # find the total acceleration of the object at its new position

        next_v = self.velocity + (0.5 * (total_a + next_a) * self.dt) # find the next velocity using Verlet-Velocity

        self.velocity = next_v # update velocity

        self.orbit.append(self.position) # add the position to the orbit array
        
    
def main():
    run = True 
    clock = pg.time.Clock() # sets up a clock to allow for FPS caps 
    
    # Defining the sun and each of the four planets as a celestial object
    sun = CelestialObject(1.9885e30, 30, [0, 0], [0, 0], yellow)
    sun.isSun = True

    mercury = CelestialObject(3.3010e23, 8, [0.31*CelestialObject.au, 0], [0, 47.4e3], white)
    venus = CelestialObject(4.87e24, 14, [0.718*CelestialObject.au, 0], [0, 35.02e3], red)
    earth = CelestialObject(5.9722e24, 16, [0.98*CelestialObject.au, 0], [0, 29.783e3], blue)
    mars = CelestialObject(6.4169e23, 12, [1.38*CelestialObject.au, 0], [0, 24.077e3], orange)

    celestialobjects = [sun, mercury, venus, earth, mars]

    while run:
        clock.tick(60) # 60 fps cap
        win.fill(black) # provide a blank black canvas
        for evt in pg.event.get():
            if evt.type == pg.QUIT:
                run = False # if the user hits the x button, quit the program
        for object in celestialobjects:
            object.update(celestialobjects) # for each body, update its position and draw it on the window
            object.draw(win)
        pg.display.update() # update the pygame display
    pg.quit() # quit pygame
main() # execute main