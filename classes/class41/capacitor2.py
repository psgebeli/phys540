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
set1 = { C }
print("Single capacitor:")
report(sorted(set1))

# 1+1
set2 = set()
for c in set1:
    set2.add(c + C)
    set2.add(1/(1/c + 1/C))
print("All two-capacitor combinations:")
report(sorted(set2))

# 2+1
set3 = set()
for c in set2:
    set3.add(c + C)
    set3.add(1/(1/c+1/C))
print("All three-capacitor combinations:")
report(sorted(set3))

# 3+1 and 2+2
set4 = set()
for c in set3:
    set4.add(c + C)
    set4.add(1/(1/c + 1/C))
for cA in set2:
    for cB in set2:
        set4.add(cA+cB)
        set4.add(1/(1/cA + 1/cB))
print("All four-capacitor combinations:")
report(sorted(set4))

# 4+1 and 3+2
set5 = set()
for c in set4:
    set5.add(c + C)
    set5.add(1/(1/c + 1/C))
for cA in set3:
    for cB in set2:
        set5.add(cA+cB)
        set5.add(1/(1/cA + 1/cB))
print("All five-capacitor combinations:")
report(sorted(set5))

