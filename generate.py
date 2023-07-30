import os
import sys
import random
import uuid

# scene volume
MIN_X = -10
MAX_X = 10
MIN_Y = -10
MAX_Y = 10
MIN_Z = -20
MAX_Z = 2

# number of objects
LIGHTS = 3
SPHERES = 20
MIN_RADIUS = 0.5
MAX_RADIUS = 3

# material parameters
MIN_F = 1
MAX_F = 10
MIN_A = 0.3
MAX_A = 1
MIN_N = 0.5
MAX_N = 2

def pos():
    return f'{random.uniform(MIN_X, MAX_X)} {random.uniform(MIN_Y, MAX_Y)} {random.uniform(MIN_Z, MAX_Z)}'

def color():
    return f'{random.random()} {random.random()} {random.random()}'

def generate(name):
    print(name)
    
    print('Generating scene...')
    with open(f'{name}.txt', 'w') as f:
        f.write('eye 0 0 0\n')
        f.write('viewdir 0 0 -1\n')
        f.write('updir 0 1 0\n')
        f.write('hfov 90\n')
        f.write('imsize 500 500\n')
        f.write(f'bkgcolor {color()}\n')

        for i in range(LIGHTS):
            f.write(f'pointlight {pos()} {color()}\n')
        
        for i in range(SPHERES):
            f.write(f'material {color()} {color()} {color()} {random.uniform(MIN_F, MAX_F)} {random.uniform(MIN_A, MAX_A)} {random.uniform(MIN_N, MAX_N)}\n')
            f.write(f'sphere {pos()} {random.uniform(MIN_RADIUS, MAX_RADIUS)}\n')

    os.system(f'./render {name}.txt')
    os.remove(f'{name}.txt')

random.seed()

if not os.path.exists('./render'):
    print('Building project...')
    os.system('make')

# python generate.py [NUM_IMAGES]
for i in range(int(sys.argv[1])):
    generate(uuid.uuid4())
