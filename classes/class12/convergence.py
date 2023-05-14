import math
import sys

def trapezoidIntegrator(f,a,b, N):
    width = b-a
    h = width/N
    sum = 0.5*(f(a)+f(b))
    for n in range(1,N):
        xn = a + n*h
        sum += f(xn)
    return sum*h

def negxpowlogx(n):
    def tmp(x):
        xn = math.pow(x,n)
        return -xn*math.log(x)
    return tmp

#I = trapezoidIntegrator(negxpowlogx(1), 0.0, 1.0, 100)
#print("int_0^1 dx -x ln(x) =", I) fails, ofc, since log(0) = inf and comp doesnt know what to do

p = float(sys.argv[1])

for k in [10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000]:
    I = trapezoidIntegrator(negxpowlogx(p), 1.0/k/k, 1.0, k)
    print(k, I)

