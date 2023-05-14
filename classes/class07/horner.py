# Horner's scheme for polynomials

def polynom1(x, a1, a0):
    return a1*x + a0

def polynom2(x, a2, a1, a0):
    return (a2*x + a1)*x + a0
    # cf. a2*x*x + a1*x + a0

def polynom3(x, a3, a2, a1, a0):
    return ((a3*x + a2)*x + a1)*x + a0
    #          ^  ^    ^  ^    ^  ^
    # 6 floating point operations
    # cf. a3*x*x*x + a2*x*x + a1*x + a0 which has 9 operations


# nested horners scheme computation
def polynom(x,a):
    val = a[0]
    for i in range(1,len(a)):
        val *= x
        val += a[i]
    return val

#polynomial
#p(x) = 3x^3 - 7x^2 + 2x - 5
p = [ 3, -7, 2, -5]

for i in range(-500,501):
    x = i/25
    print(x,polynom(x,p))
