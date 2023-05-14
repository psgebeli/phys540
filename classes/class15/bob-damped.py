import sys

# ping pong ball thrown onto water and will submerge/bounce
# M d^2s/dt^2 (Ma) = Mg - rho*g*(pi/3)*s^2(3R-s)
#                    ^                 ^
#                   weight           buoyancy due to submerged portion
# (1/g) d^2s/dt^2  = 1 - (Mw/M)C(s/R)
#                         ^
#                     mass of displaced water

# additional forces ...
# F{damping} = -(coeff)*(cross-sectional area) * ds/dt
#                         ^
#                        0 if s<0 (out of water)
#                        pi R^2 if s > R (atleast half way sub)
#                        pi s(2R-s) if 0 < s < R

# M d^2s/dt^2 = Mg - rho g (pi/3) s^2 (3R-s) - (c0eff) pi s(2R-s) ds/dt
# 1/g d^2s/dt^2 = 1-(Mw/M) C(s/R) - (Md/vd/M) D(s/r) ds/dt


def C(x):
    if x < 0.0: # if ball hasnt hit water
        return 0.0
    elif x > 2.0: # if ball is 2R under surface (full submersion)
        return 1.0
    else:
        return 0.25*x*x*(3-x)


def D(x):
    if x < 0.0:
        return 0.0
    elif x > 1.0:
        return 1.0
    else:
        return x*(2.0-x)


# constants

dt = 0.0005
g = 9.81
R = 0.1
mass_ratio = float(sys.argv[1]) # Mw/M, read it in as cmd line argument
drag = float(sys.argv[2])

# initial conditions

s = 2.0*R # initially, fully submerged
v = 0.0 # at rest

for n in range(10001):
    t = n*dt
    if (n%20 == 0): # only interested in every 20th iteration (n mod 20 = 0)
        print("{:10.3f} {:10.6f} {:10.6}".format(t,s,v))
    s_next = s + v*dt + 0.5*g*dt*dt*(1-mass_ratio*C(s/R) - drag*D(s/R)*v)
    v = v + g*dt*(1-0.5*mass_ratio*(C(s/R)+C(s_next/R))
                    -0.5*drag*(D(s/R) + D(s_next/R)))
    s = s_next