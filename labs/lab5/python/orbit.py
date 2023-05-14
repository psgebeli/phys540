import math # for sin funct

R = 6378.1 # km (radius of the earth)
r2 = R + 3000.0 # km (apogee)
r1 = R + 500.0 # km (perogee)
a = 0.5*(r1 + r2) # semi-major axis
e = (r2-r1)/(2.0*a) # eccentricity
mu = 398600.4418 # km^3/s^2
P = 2*math.pi*math.sqrt(a*a*a/mu)/3600. # period in hrs
dt = P/5075

def eccentric_anomaly(M, E0):

    E = E0
    epsilon = 1e-6 # to detect convergence
    N = 100 # number of iterations

    for n in range(N):
        deltaE = -(E-M-(e*math.sin(E)))/(1-(e*math.cos(E)))
        E += deltaE # negative already accounted for 
        if abs(deltaE) < epsilon:
            return E
    raise ValueError("Failed to converge.") # divergence exception

    return E

print("Eccentricity e = {}".format(e))
print("Period P = {}".format(P))

for n in range(1,50000):
    t = n*dt
    M = 2.0*math.pi*t/P
    E = eccentric_anomaly(M, 0) # E0 = 0
    theta = 2*math.atan(math.sqrt((1+e)/(1-e))*math.tan(E/2))
    r = a*(1-e*math.cos(E))
    print("{:.6f} {:.6f} {:.6f}".format(t,r,theta))
