import odroid_wiringpi as wpi
import time
import urllib
import requests
import sys

wpi.wiringPiSetup()

baseURL = 'https://api.thingspeak.com/update?api_key=XNT3KI57UO56HF47&field1=0'

started_time = time.time()

print_time = time.time()

Uno = wpi.serialOpen('/dev/ttyS1', 115200)

received_data = 0
tmp_received_data = 0

temp_from_uno = ""

while True:
    temp_from_uno = ""
    while wpi.serialDataAvail(Uno):
        try:
            received_byte = wpi.serialGetchar(Uno)
            if 0 <= received_byte <= 0x10FFFF:
                temp_from_uno += chr(received_byte)
                if (temp_from_uno != ""):
                    tmp_received_data = int(temp_from_uno)
                print("receive data: ", temp_from_uno)
            else:
                print(f"Received invalid byte: {received_byte}")

        except ValueError:
            print("Error converting received byte to character.")

    end_print_time = time.time()
    if end_print_time - print_time > 1:
        print_time = time.time()
        if (tmp_received_data//10 < 1):
            tmp_received_data = received_data
        received_data = tmp_received_data
        print(received_data)

    try:
        ended_time = time.time()
        if ended_time - started_time > 15:
            started_time = time.time()
            f = urllib.request.urlopen(baseURL + str(received_data))
            print("sent data to thing thingspeak")
            f.read()
            f.close()
    except Exception as e:
        print(f"An exception occurred: {e}")

wpi.serialClose(Uno)