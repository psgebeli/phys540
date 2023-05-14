# Capacitor value
C = 60.0

# 1
set1 = { C }
print("Single capacitor:")
print(sorted(set1))

# 1+1
set2 = set()
for c in set1:
    set2.add(c + C)
    set2.add(1/(1/c + 1/C))
print("All two-capacitor combinations:")
print(sorted(set2))

# 2+1
set3 = set()
for c in set2:
    set3.add(c + C)
    set3.add(1/(1/c+1/C))
print("All three-capacitor combinations:")
print(sorted(set3))

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
print(sorted(set4))

