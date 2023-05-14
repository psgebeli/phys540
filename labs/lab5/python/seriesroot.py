import numpy as np
import sys

def expansion(a, b, N):
    """
    Compute the N-term series expansion of sqrt(a^2 + b).
    
    Output will be columnar with N versus the series expansion for sqrt(a^2+b) truncated at N.
    """
    
    eps = 1e-6 # define a cutoff 
    
    # hard code the two small cases

    if N == 1:
        return a
    elif N == 2:
        return a + b/(2*a)
    
    term = -b / ((2*a)**2)
    total = term # initialize variables
    
    for n in range(1, N-2): # non-inclusive, so the loop does N-3 iterations (cause we handled base cases)
        num = -b * (2*n + 2) * (2*n + 1)
        denom = 4 * a**2 * (n+1) * (n+2)
        ratio = num / denom # define the ratio of subsequent terms
        term *= ratio # get next term by multiplying current term by ratio formula
        total += term # add term to sum
        
        if abs(term) < eps:
            break # if a term is super tiny, its not worth adding to the sum so just truncate
    
    return a + ((b / (2*a)) * (1 + total)) # return the overall result for the expansion

if len(sys.argv) < 4:
    print("Usage: python3 filename.py a b N1 [N2 N3 N4...]")
    sys.exit(1)

a = float(sys.argv[1])
b = float(sys.argv[2])
Ns = [int(arg) for arg in sys.argv[3:]] # args 3, 4, ... 

for N in Ns:
    value = expansion(a, b, N)
    print(f"{N:>6d} {value:>12.10f}")
