""" 
    Points.py

    Code written by Alice Kjar

    Generates a sample set of points of a given size and type and saves them 
    in the proper format.
"""

import random as rand
import math

PI = math.pi

CIRCLE = 0
HULL = 1
RAND = 2
BOUND = 10 # bound for points

# Change for different tests
SIZE = 100
TEST = HULL

""" Generate a list of points in a circle
    Input: n (number of points), points (original list of points)
    Output: list of points with new points added
"""
def circle(n, points):
    rand.seed("C100")
    i = 0

    while(i < n):
        angle = rand.uniform(-PI, PI)
        # convert polar to cartesian
        x = math.cos(angle)
        y = math.sin(angle)
        if (x,y) not in points:
            # no repeating points
            points.append((x,y))
            i += 1
    return points


""" Generate a list of points in a simple hull (rectangle)
    Input: n (number of points), points (original list of points)
    Output: list of points with new points added
"""
def random_in_hull(n, points):
    rand.seed("H100")

    # generate corners
    x_len = rand.uniform(0, BOUND)
    y_len = rand.uniform(0, BOUND)
    points.append((x_len,y_len))
    points.append((-x_len,y_len))
    points.append((x_len,-y_len))
    points.append((-x_len,-y_len))

    i = 4
    while(i < n):
        # add points within rectangle hull
        x = rand.uniform(-x_len, x_len)
        y = rand.uniform(-y_len, y_len)
        if (x,y) not in points:
            # no repeating points
            points.append((x,y))
            i += 1
    return points


""" Generate a list of points in a pseudo-random arrangement
    Input: n (number of points), points (original list of points)
    Output: list of points with new points added
"""
def random(n, points):
    rand.seed("R100")
    # Generate a random point in the plane
    x = rand.uniform(-BOUND, BOUND)
    y = rand.uniform(-BOUND, BOUND)
    points.append((x, y))

    i = 1
    while(i < n):
        # Generate a random vector from the previous point
        angle = rand.uniform(-PI, PI)
        dist = rand.uniform(0, BOUND)
        x = points[-1][0] + dist * math.cos(angle)
        y = points[-1][1] + dist * math.sin(angle)
        if (x,y) not in points:
            # no repeating points
            points.append((x,y))
            i += 1
    return points
    


outfile = open("h100.txt", "w")
points = []

# generate appropriate points
if (TEST == CIRCLE):
    points = circle(SIZE, points)
elif (TEST == HULL):
    points = random_in_hull(SIZE, points)
elif (TEST == RAND):
    points = random(SIZE, points)

# add size to file
outfile.write(str(SIZE))
outfile.write('\n')

# add each point in the correct format
for item in points:
    pointx = str(item[0])
    pointy = str(item[1])
    outfile.write(pointx)
    outfile.write(' ')
    outfile.write(pointy)
    outfile.write('\n')
    
outfile.close()
