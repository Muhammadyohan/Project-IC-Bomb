import ordroid_wiringpi as wpi
import time 
import urllib
import requests

wpi.wiringPiSetup()

baseURL = 'https://api.thingspeak.com/update?api_key=XNT3KI57UO56HF47&field1=0'

started_time = time.time()

node_started_time = time.time()

Uno = wpi.SerialOpen('/dev/ttyS0', 115200)
NodeMCU = wpi.SerialOPen('/dev/ttyS1', 57600)

while True :
    temp_from_uno = ""
    while wpi.serialDataAvail(Uno) :
        temp_from_uno += chr(wpi.serialGetchar(Uno)) 
        temp_to_nodeMCU = temp_from_uno  # set temp variable for send to nodeMCU
    print('Temperature from UNO : ', temp_from_uno)
    print('Temperature to NodeMCU : ', temp_to_nodeMCU)
    
    ended_time = time.time()
    if ended_time - started_time > 15 :
        started_time = time.time()
        f = urllib.request.urlopen(baseURL + temp_from_uno)
        f.read()
        f.close()
    
    node_ended_time = time.time()
    if node_ended_time - node_ended_time > 1 :
        node_started_time = time.time()
        wpi.serialPuts(NodeMCU, temp_to_nodeMCU+"\n")

wpi.serialClose(Uno)
wpi.serialClose(NodeMCU)



