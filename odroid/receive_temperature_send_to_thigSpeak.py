import odroid_wiringpi as wpi
import time
import urllib

wpi.wiringPiSetup()

baseURL = 'https://api.thingspeak.com/update?api_key=XNT3KI57UO56HF47&field1=0'

started_time = time.time()

Uno = wpi.serialOpen('/dev/ttyS1', 115200)

while True:
    temp_from_uno = ''
    while wpi.serialDataAvail(Uno):
        try:
            received_byte = wpi.serialGetchar(Uno)
            if 0 <= received_byte <= 0x10FFFF:
                temp_from_uno += chr(received_byte)
            else:
                print(f"Received invalid byte: {received_byte}")
        except ValueError:
            print("Error converting received byte to character.")
    print('Temperature from UNO : ', temp_from_uno)

    ended_time = time.time()
    if ended_time - started_time > 15:
        started_time = time.time()
        f = urllib.request.urlopen(baseURL + str(received_data))
        print("sent data to thing thingspeak")
        f.read()
        f.close()

wpi.serialClose(Uno)