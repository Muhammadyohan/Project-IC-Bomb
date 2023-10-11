import odroid_wiringpi as wpi
import time 
import urllib
import requests

wpi.wiringPiSetup()

baseURL = 'https://api.thingspeak.com/update?api_key=XNT3KI57UO56HF47&field1=0'

started_time = time.time()

Uno = wpi.serialOpen('/dev/ttyS0', 115200)

while True :
    temp_from_uno = ''
    while wpi.serialDataAvail(Uno) :
        temp_from_uno += chr(wpi.serialGetchar(Uno)) 
    print('Temperature from UNO : ', temp_from_uno)
    
    ended_time = time.time()
    if ended_time - started_time > 15 :
        started_time = time.time()
        f = urllib.request.urlopen(baseURL + temp_from_uno)
        f.read()
        f.close()

wpi.serialClose(Uno)




