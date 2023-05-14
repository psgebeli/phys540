import math

def trapezoidIntegrator(f,a,b, N):
    width = b-a
    h = width/N
    sum = 0.5*(f(a)+f(b))
    for n in range(1,N):
        xn = a + n*h
        sum += f(xn)
    return sum*h

I = trapezoidIntegrator(math.cos, 0.0, math.pi, 100)
print("int_0^pi dx cos(x) =", I)

#trapezoidIntegrator(cos*sin+3, 0.0, math.pi, 100)

def cs3(x):
    return math.cos(x)*math.sin(x) + 3.0

print("-----------_")
I = trapezoidIntegrator(cs3, 0.0, math.pi, 100)
print("int_0^pi dx [cos(x)sin(x) + 3] =", I)


def cospow_unpassable(x,n):
    c1 = math.cos(x)
    cn = 1.0
    for k in range(n):
        cn *= c1
    return cn

# so how do we pass this to the integrator if it has two arguments?

# use a closure
def cospow(n):
    def tmp(x):
        c1 = math.cos(x)
        cn = 1.0
        for k in range(n):
            cn *= c1
        return cn
    return tmp

print("--------------")

for k in range(9):
    I= trapezoidIntegrator(cospow(k), 0.0, math.pi, 100)
    print("int_0^pi dx cos^{}(x) = {:.6f} ({:.16e})".format(k,I,I))
