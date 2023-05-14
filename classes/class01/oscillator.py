import math

nu = 50 # Hz
omega = 2*math.pi # radians
t0 = 1.25 # 2

dt = 0.001 # Hz

A = 10 # cm
B = 2 # cm

for i in range(5000): # does not give 5000, only up to 4999
    t = i*dt
    x = (A*math.cos(omega*t) + B*math.cos(2*omega*t))*math.exp(-t/t0)
    print("{:10.4f} {:10.4f}".format(t,x))
