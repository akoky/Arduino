import serial
import pydirectinput

arduino = serial.Serial('COM8', 9600, timeout = 1)

pydirectinput.PAUSE = 0

keysDown = {}

def keyDown(key):
    keysDown[key] = True
    pydirectinput.keyDown(key)

def keyUp(key):
    if key in keysDown:
        del (keysDown[key])
        pydirectinput.keyUp(key)

def handleJoyStickAsArrowKeys(y, x, z, a, b, c, d):
    if x == 2:
        keyDown('up')
        keyUp('down')

    elif x == 0:
        keyDown('down')
        keyUp('up')
    else:
        keyUp('up')
        keyUp('down')

    if y == 0:
        keyDown('right')
        keyUp('left')
    elif y == 2:
        keyDown('left')
        keyUp('right')
    else:
        keyUp('left')
        keyUp('right')

    if z == 1:
        keyDown('esc')
    else:
        keyUp('esc')

    if a == 1:
        keyDown('w')
    else:
        keyUp('w')

    if b == 1:
        keyDown('a')
    else:
        keyUp('a')

    if c == 1:
        keyDown('space')
    else:
        keyUp('space')

    if d == 1:
        keyDown('d')
    else:
        keyUp('d')

while True:
    rawdata = arduino.readline()
    data = str(rawdata.decode('utf-8'))
    if data.startswith("S"):
        dx = int(data[1])
        dy = int(data[3])
        Bz = int(data[5])
        Ba = int(data[7])
        Bb = int(data[9])
        Bc = int(data[11])
        Bd = int(data[13])
        handleJoyStickAsArrowKeys(dx,dy,Bz,Ba,Bb,Bc,Bd)
    
