from fractions import Fraction # rational number class

# Capacitor value
C = Fraction(60) # Fraction(60,1)

def report(S):
    for n, c in S:
        if c.denominator != 1:
            print(f"{c} = {float(c)}  (x{n})")
        else:
            print(f"{c.numerator}  (x{n})")

# 1
this_set = { (1, C) }
print("Single capacitor:")
report(sorted(this_set))

nmax = 12
print(f"Up to {nmax} capacitors:")
while True:
    next_set = set()
    l = len(this_set)
    for nA, cA in this_set:
        for nB, cB in this_set:
            n = nA + nB
            if n <= nmax:
                next_set.add((n,cA+cB))
                next_set.add((n,1/(1/cA+1/cB)))
    #this_set = this_set.union(next_set)
    this_set = this_set | next_set
    ll = len(this_set)
    if l == ll: # no further changes/additions
        break
report(sorted(this_set, key=lambda x:x[1]))


