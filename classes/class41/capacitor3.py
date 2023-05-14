from fractions import Fraction # rational number class

# Capacitor value
C = Fraction(60) # Fraction(60,1)

def report(S):
    for c in S:
        if c.denominator != 1:
            print(f"{c} = {float(c)}")
        else:
            print(f"{c.numerator}")

# 1
this_set = { C }
print("Single capacitor:")
report(sorted(this_set))

for iter in range(4):
    next_set = set()
    for cA in this_set:
        for cB in this_set:
            next_set.add(cA+cB)
            next_set.add(1/(1/cA+1/cB))
    #this_set = this_set.union(next_set)
    this_set = this_set | next_set
    print(f"Iteration {iter+1}")
    report(sorted(this_set))

