#pip install paho-mqtt
#python3 -m pip install -U pygame --user
import pygame
from pygame.locals import *
import sys
import time
import paho.mqtt.client as mqtt

SCREENSIZE = (400,400)

pygame.init()
screen = pygame.display.set_mode(SCREENSIZE)

#variabelen definieren
#kleuren
BLACK = (0,0,0)
BLUE  = (0,0,255)
RED = (255,0,0)
WHITE = (255,255,255)
MOUSE = (200,200,125)

points = []
drawpoints = []

delay = 0.25

lastTime = 0

grid = []
def plotGrid(steps):
    for i in range(steps,SCREENSIZE[0],steps*2):
        grid.append((i,-1))
        grid.append((i,SCREENSIZE[1]+1))
        grid.append((i+steps,SCREENSIZE[1]+1))
        grid.append((i+steps,-1))

    grid.append((0,0))
    for i in range(steps,SCREENSIZE[1],steps*2):
        grid.append((-1,i))
        grid.append((SCREENSIZE[0],i))
        grid.append((SCREENSIZE[0],i+steps))
        grid.append((-1,i+steps))

plotGrid(50)

#title
pygame.display.set_caption("LineDancer")

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/light/out")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client(client_id="PC")
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.137.1", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_start()
print("connection success")

def drawMyLines(points,screen,color):
   lineThickness = 2 
   pygame.draw.lines(screen, color, False,
           points, lineThickness)



while True:
    screensize = (0,0,SCREENSIZE[0],SCREENSIZE[1])
    pygame.draw.rect(screen, WHITE,screensize)
    pygame.draw.lines(screen, BLACK, False, grid, 1)
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            client.loop_stop()
            client.disconnect()
            sys.exit()
        elif True == pygame.mouse.get_pressed()[0]:
            if(time.time() > (lastTime + delay)):
                points.append(pygame.mouse.get_pos())
                print(points)
                client.publish("/point/x", payload=points[-1][0], qos=0, retain=False)
                client.publish("/point/y", payload=points[-1][1], qos=0, retain=False)
                client.publish("/point/z", payload=1, qos=0, retain=False)
                lastTime = time.time()
        elif False == pygame.mouse.get_pressed()[0]:
            if(time.time() > (lastTime + delay)):
                #points.append((-1,-1))
                print("Pen is UP")
                #publish("/point/x", payload=points[-1][0], qos=0, retain=False)
                #publish("/point/y", payload=points[-1][1], qos=0, retain=False)
                #publish("/point/z", payload=0, qos=0, retain=False)
                lastTime = time.time()

    if len(points) > 1:
        drawMyLines(points, screen, BLUE)
    pygame.draw.circle(screen, MOUSE,
                       pygame.mouse.get_pos(), 5, 0)
    pygame.display.update()
