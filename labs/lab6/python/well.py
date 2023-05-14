import math
import sys

from blum import RN

m = 1.0 # kg
K = 1.0 # N/m
omega = math.sqrt(K/m) # radians/s
freq = omega/(2.0*math.pi) # Hz
period = (2.0*math.pi)/omega # s
dt = period/200.0
N = 5000 # total number of time steps
runtime = N*dt
gamma = 0.05 # arbitrary/small drag factor
kT = 0.1
xi = RN()

# verlet constants
b = math.exp((-gamma*dt)/(2*m))
beta = math.sqrt(2*gamma*kT*dt)*xi

print("runtime =", runtime, file=sys.stderr) 
print(" period =", period, file=sys.stderr)
print("   freq =", freq, file=sys.stderr)
print("", file=sys.stderr)

traj = []

# quadratic potential energy
def V(x):
    return 0.5*K*x*x

# linear restoring force
def F(x):
    return -K*x

# drag force 
# def Drag(v):
#     return -gamma*v

# total energy
def energy(x,v):
    # return 0.5*m*v*v + V(x) - (Drag(v)*x)
    return 0.5*m*v*v + V(x)

print("Running simulation...", file=sys.stderr)
x = 1.0 # m
v = 0.0 # m/s, released from rest
for n in range(N):
    a = F(x)/m
    x_next = x + b*v*dt + ((b*dt*dt)/(2*m))*F(x) + ((b*dt)/(2*m))*beta
    a_next = F(x_next)/m
    v_next = v + (dt/(2*m))*(F(x)+F(x_next))-(gamma/m)*(x_next-x)+(beta/m)
    x = x_next
    v = v_next
    print("{:10.6f} {:10.6f} {:10.6f} {:10.6f}".format(n*dt,x,v,energy(x,v)))
    traj.append(x)
print("Done.", file=sys.stderr)

print("")
print("")

print("Computing discrete Fourier Transforms...", file=sys.stderr)
cosFT_traj = []
for j in range(N):
    if (j+1)%500 == 0:
        print(j+1,"/",N, file=sys.stderr)
    sum = 0.0
    for k in range(N):
        sum += math.cos(2.0*math.pi*j*k/N)*traj[k]
    cosFT_traj.append(sum)
print("Done cos.", file=sys.stderr)

sinFT_traj = []
for j in range(N):
    if (j+1)%500 == 0:
        print(j+1,"/",N, file=sys.stderr)
    sum = 0.0
    for k in range(N):
        sum += math.sin(2.0*math.pi*j*k/N)*traj[k]
    sinFT_traj.append(sum)
print("Done sin.", file=sys.stderr)


for j in range(N):
    print
    print("{:10.6f} {:10.6f} {:10.6f}".format(j/runtime,cosFT_traj[j],sinFT_traj[j]))


