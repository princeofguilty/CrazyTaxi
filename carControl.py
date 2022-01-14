import time
import serial

serialComm = serial.Serial("COM3", 9600, timeout=1)
time.sleep(2)

while True:
    msg = input("enter msg:").strip()
    serialComm.write(msg.encode())
    time.sleep(0.1)
    print(serialComm.readline().decode('ascii'))
    if msg == "end":
        break


serialComm.close()
