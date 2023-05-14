from dataclasses import dataclass
from typing import List

@dataclass
class Polynomial:
    a: List[float] # coefficients

    def __getitem__(self, n): # lets us access nth coeff with ()
        return self.a[n]

    def __setitem__(self, n, newvalue):
        self.a[n] = newvalue

    def __str__(self): # prints pretty representation
        if len(self.a) == 1:
            return str(self[0])
        s = ""
        if self[0] != 0:
            s += str(self[0])
        for i in range(1,len(self.a)):
            if i == 1:
                xn = "x"
            else:
                xn = "x^" + str(i)
            if self[i] == -1:
                s += " - " + xn
            elif self[i] > 0:
                s += " + " + str(self[i]) + xn
            elif self[i] < 0:
                s += " - " + str(abs(self[i])) + xn
        return s

    def __call__(self,x): # nested horners scheme, finds poly at some x
        eval = self.a[-1]
        for i in range(1,len(self.a)):
            eval *= x
            eval += self.a[-(1+i)]
        return eval

    # polynomial operations

    def __add__(self, other):
        N = len(self.a)
        M = len(other.a)
        K = max(N,M)
        sum = Polynomial([0]*K) # give me an array of K zeros
        for k in range(K):
            if k < N: sum[k] += self[k]
            if k < M: sum[k] += other[k]
        return sum

    def __sub__(self, other):
        N = len(self.a)
        M = len(other.a)
        K = max(N,M)
        sum = Polynomial([0]*K) # give me an array of K zeros
        for k in range(K):
            if k < N: sum[k] += self[k]
            if k < M: sum[k] -= other[k]
        return sum

    def __mul__(self, other):
        N = len(self.a)
        M = len(other.a)
        K = N+M-1
        prod = Polynomial([0]*K)
        for n in range(N):
            for m in range(M):
                prod[n+m] += self[n]*other[m]
        return prod

    def differentiate(self):
        N = len(self.a)
        if (N == 1):
            self.a = [0]
        else:
            for n in range(1,N):
                self[n-1] = n*self[n]
            del self.a[-1]
        return self

    def integrate(self,xL,xR):
        # int_xL^xR p(x) dx = P(xR) - P(xL)
        N = len(self.a)
        P = Polynomial([0]*(N+1))
        for n in range(1, N+1):
            P[n] = self[n-1]/n
        return P(xR) - P(xL)
    


# testing out our class

# defining polynomials
p = Polynomial([1,2,3])
q = Polynomial([-1,-2,-3,-4])
print("p(x) = ", p)
print("q(x) = ", q)
        
print("_____________________________")
print("Test addition")
print("p + q = ", p+q)

print("_____________________________")
print("Test multiplication")
r = p+q
s = p-q
print("(p+q)(p-q) = ", r*s)
print("           = p^2 - q^2")
print("           = ", p*p - q*q)


print("____________________________")
print("Test differentiation")
print("q(x) = ", q)
q.differentiate()
print("q'(x) = ", q)
q.differentiate()
print("q''(x) = ", q)
q.differentiate()
print("q^(3)(x) = ", q)

print("____________________________")
print("Test definite integration")
f = Polynomial([0,0,0,4])
print("f(x) = ", f)
print("int_0^1 f(x) dx = ", f.integrate(0,1))
print("int_1^2 p(x) dx = ", p.integrate(1,2))


# write columnar output to a file
p = Polynomial([1,2,3])
q = Polynomial([-1,-3,-3,4])
f = open("poly.dat", "w")
for i in range(101):
    x = (i-50)*0.02 # -1 --> 1 in reality
    f.write("{:6.3f} {:8.3f} {:8.3f} {:8.3f} {:8.3f}\n".format(x,p(x),q(x),(p*p-q*q)(x),(p+q)(x)))
f.close()
