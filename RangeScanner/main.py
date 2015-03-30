import serial
import numpy as np
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
samples = 180

x = []
y = []

while samples > 0:
	line = ser.readline()
	ln = line.split()
	if len(ln) == 2:
		x.append(ln[0])
		y.append(ln[1])
		samples -= 1
		print samples, "samples left to collect"

print "Generating graph"
fig = plt.figure()
plt.title("Angle vs Distance")
plt.xlabel("Angle (deg)")
plt.xlim(-20, 200)
plt.ylabel("Distance (cm)")
plt.ylim(0, 200)
plt.scatter(x, y, color = 'green')
plt.show()