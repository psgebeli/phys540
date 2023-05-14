import sys
import math
import struct

# define parameters

p = 2888799659
q = 3694568831
M = p*q
x0 = 326694129

def blum(x):
    return (x*x) % M

def R():
    global x0                       # to make sure python knows we refer to prev defined x0, not a new x0
    x = x0                          # initialize x to our defined x0
    result = 0.0                    # this will store the result of our loop (aka the number in [0,1))
    for i in range(52):             # loop 52 times, each iteration producing a bit to populate using blum
        x = blum(x)                     # get a new random number
        bit = x & 1                     # extract the least significant bit of x, store this as bit
        result += bit * 2**(-i-1)       # add the bit multipled by its contribution to the generated number
    x0 = x                              # change the seed for each iteration
    return result
 

def RN():

    u1 = R()
    u2 = R()
    z1 = math.sqrt(-2 * math.log(u1)) * math.cos(2 * math.pi * u2)
    return z1 


# testing 

#print("Testing random number generator", file=sys.stderr)
#r=[]
#rr=[]
#for n in range(1000):
    r.append(R())
    rr.append(RN())
#r.sort()
#rr.sort()
#f = open("rng-test.dat","w")
#for n in range(len(r)):
    f.write("{:8.4} {:15.8} {:15.8}\n".format((n+0.5)/len(r),r[n],rr[n]))
#f.close()
#exit()