# decided to do everything in python because why not

import sys
import math

def nearly_equal(x: float, y: float) -> bool:
    separation = abs(x-y) # can handle floats
    eps = 1E-14
    return separation < abs(x)*eps and separation < abs(y)*eps

def bad():
    print("Returns the rational power a^(p/q) and compares to the")
    print("value computed with pow() in the math library")
    print("Usage: python3 ratpow.py a p q")
    print("       a = non-negative floating-point number")
    print("     p, q = non-zero integers")
    sys.exit(1)

def main(argv):
    if len(argv) != 4:
        bad()
    
    # try/except block tries to execute each command, 
    # and if exception is raised, give control
    # to except

    try:
        a = float(argv[1])
        p = int(argv[2])
        q = int(argv[3])
    except ValueError:
        bad()

    if a <= 0.0 or p == 0 or q == 0: 
        bad()
    
    x = 1.0
    x_prev = 0

    # recursive loop
    # 1 : calculate next term via recursion formula for current term
    # 2 : set prev term = current term, and then set current term = next term calculated in step 1
    # ^___________________________________________________________________________________________^
    #                                   sets up next iteration
    # 3 : start next iteration with the newly defined x_prev, x_n
    # terminate loop when x is nearly equal to x_n+1 (convergence)
    
    while not nearly_equal(x_prev, x):
        x_new = (1-1/q)*x + (1/q)*a**p*x**(1-q)
        x_prev = x 
        x = x_new

    print("    Newton's method value:", x)
    print("Python Math library value:", math.pow(a, float(p)/q))
    #                                               ^____^
    #                                           ensure power is a float, no rounding 
    return 0

if __name__ == '__main__':
    main(sys.argv)