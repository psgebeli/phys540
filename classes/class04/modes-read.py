import math

nu = 50 # Hz
omega = 2*math.pi # radians
t0 = 1.25 # 2

dt = 0.001 # Hz

with open ("A-coeffs.txt", "r") as myfile:
    A = myfile.read().splitlines()
A = [float(a) for a in A] # convert text from read to floats

def x(t):
    val = 0.0
    for n in range(len(A)):
        val += A[n]*math.cos(n*omega*t)
    val *= math.exp(-t/t0)
    return val

for i in range(5000): # does not give 5000, only up to 4999
    t = i*dt
    print("{:10.4f} {:10.4f}".format(t,x(t)))
