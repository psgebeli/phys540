from dataclasses import dataclass
from typing import List

@dataclass
class Polynomial:
    a: List[float]

    def __getitem__(self, n):
        return self.a[n]

    def __setitem__(self, n, newvalue):
        self.a[n] = newvalue

    def __str__(self):
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

    def __call__(self,x):
        eval = self.a[-1]
        for i in range(1,len(self.a)):
            eval *= x
            eval += self.a[-(1+i)]
        return eval

p = Polynomial([1,2,3])
q = Polynomial([-1,-2,-3,-4])
print("p(x) = ", p)
print("q(x) = ", q)

print("p(3.0) = ", p(3.0))
print("q(4.5) = ", q(4.5))
