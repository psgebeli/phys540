import sys 
import math 


# This script does not have many comments because it is fairly self explanatory,
# I am just defining the functions as they are and then doing the calculations.


def alpha(n):

    if n == 0:
        return math.sqrt(2)
    else:
        a_n_minusone = alpha(n-1)
        return (0.5)*(math.sqrt(a_n_minusone)+(1/math.sqrt(a_n_minusone)))

def beta(n):

    if n == 0:
        return 0
    else:
        b_n_minusone = beta(n-1)
        num = math.sqrt(alpha(n-1))*(1+b_n_minusone)
        denom = alpha(n-1) + b_n_minusone
        return num/denom

def agm_expansion(n):

    if n == 0:
        return 2 + math.sqrt(2)
    else:
        pi_n_minusone = agm_expansion(n-1)
        num = pi_n_minusone * beta(n)*(1+alpha(n))
        denom = 1 + beta(n)
        return num/denom
    

def atan_series(x,N): # 2nd funct in series.py

    x2 = x*x
    val = 0.0 
    y = x2/(1+x2)
    m = 2*N + 3
    for n in range(N-1, 0, -1):
        val = val*y*(m-3)/m + 1
        m -= 2
    result = val*y*(-1/3) + 1
    return result*x

def pi_estimateone(N):

    return 4*atan_series(1/2, N) + 4*atan_series(1/5, N) + 4*atan_series(1/8, N)

def pi_estimatetwo(N):

    return 16*atan_series(1/5, N) - 4*atan_series(1/239, N) 

def pi_estimatethree(N):

    return 24*atan_series(1/8, N) + 8*atan_series(1/57, N) + 4*atan_series(1/239, N)

print("Displays four ways of calculating pi with N-iteration expansions.")

if len(sys.argv) != 1:
    print("Usage: python3 pi.py N\n")
    print("Where 'N' is an integer.")

N = int(sys.argv[1])

print("\nFor N=", N, ", the four calculations of pi are:\n")

for n in range(1, N+1):
    print("{:>6d} {:>12.13f} {:>12.13f} {:>12.13f} {:>12.13f}".format(n, float(agm_expansion(n)), float(pi_estimateone(n)), float(pi_estimatetwo(n)), float(pi_estimatethree(n))))





