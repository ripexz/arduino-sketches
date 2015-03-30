import serial

ser = serial.Serial('/dev/tty.usbmodem1411', 9600);

while True:
	print ser.readline()