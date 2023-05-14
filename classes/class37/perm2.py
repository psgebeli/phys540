import random

BrightRed = "\u001b[31;1m";
BrightGreen = "\u001b[32;1m";
BrightYellow = "\u001b[33;1m";
BrightBlue = "\u001b[34;1m";
BrightMagenta = "\u001b[35;1m";
ResetColour = "\u001b[0m";

collection = [ BrightRed+"Apple"+ResetColour, \
               BrightYellow+"Banana"+ResetColour, \
               BrightGreen+"Pear"+ResetColour, \
               BrightMagenta+"Orange"+ResetColour, \
               BrightBlue+"Kiwi"+ResetColour ]

print("List:")
print(collection)

print("\nRange over list elements:")
for fruit in collection:
    print(fruit)

print("\nRange over enumerated list elements:")
for index, fruit in enumerate(collection):
    print("#{}".format(index+1), fruit)

def permutation(x, p):
    # sanity check
    q = p.copy()
    q.sort()
    assert q == list(range(len(p))) # [0, 1, 2, .., N-1]
    assert len(x) == len(p)
    #
    return [x[p[n]] for n in range(len(p))] # [x[p[0]], x[p[1]], ..]

p0 = [_ for _ in range(5)]
collection0 = permutation(collection, p0)

def printlist(x):
    for index, element in enumerate(x):
        print(element+(", " if index+1!=len(x) else ""), end="")
    print("")

def listcmp(x, y):
    assert len(x) == len(y)
    for i in range(len(x)):
        print("{:6} --> {:6}".format(x[i],y[i]))

p1 = [0, 2, 1, 3, 4]
p2 = [1, 2, 3, 4, 0]

collection1 = permutation(collection, p1)
collection2 = permutation(collection, p2)

print("\nEffect of permutation p1:")
listcmp(collection, collection1)

print("\nEffect of permutation p2:")
listcmp(collection, collection2)

print("\nEffect of p2*p1 in composition:")
collection12 = permutation(permutation(collection, p1), p2)
listcmp(collection, collection12)

# random.shuffle

def rnd_permutation(x):
    N = len(x)
    y = x.copy()
    # n takes on values 0, 1, 2, ..., N-1 in turn
    for n in range(N):
        # select k in { n, n+1, ..., N-1 }
        k = random.randint(n, N-1) # n <= k <= N-1
        # swap y[n] and y[k]
        tmp = y[n]
        y[n] = y[k]
        y[k] = tmp
    return y

print("\nA random permutation:")
listcmp(collection, rnd_permutation(collection))

print("\nSeveral random permutation:")
for _ in range(10):
    print(rnd_permutation(collection))

def print_cycles(p):
    N = len(p)
    visited = [False]*N
    for k in range(N):
        if visited[k]:
            continue
        i = k
        visited[i] = True
        print("({}".format(i), end="")
        while p[i] != k:
            i = p[i]
            visited[i] = True
            print(",", i, end="")
        print(")", end="")
    print("")

print("\nCycle notation for p0, p1, and p2:")
print_cycles(p0)
print_cycles(p1)
print_cycles(p2)

# Lehmer code
def perm2factoradic(p):
    # For N elements, there are N! permutations.
    # Convert the permutation into the (N-1)-digit
    # falling factoradic representation with
    # f[0] < n, f[1] < n-1, ..., f[n-2] < 2
    # corresponding to
    # f[0] + 2!*f[1] + 3!*f[2] + 4!*f[3} + ... + (n-1)!*f[n-2]
    N = len(p)
    f = [0]*(N-1)
    for k in range(N-1):
        pk = p[k]
        i = 0
        for j in range(k+1, N):
            if p[j] < pk:
                i = i+1
        f[k] = i
    return f

print("\nObserve the conversion from permutation -> factoradic:")
f0 = perm2factoradic(p0)
f1 = perm2factoradic(p1)
f2 = perm2factoradic(p2)
p3 = rnd_permutation(p0)
f3 = perm2factoradic(p3)
f4 = perm2factoradic(rnd_permutation(p0))
print(f0)
print(f1)
print(f2)
print(f3)
print(f4)

def factoradic2perm(f):
    N = 1+len(f)
    p = [i for i in range(N)] # p = [0, 1, 2, ..., N-1]
    for k in range(N-1): # k = 0, 1, .., N-2
        i = f[k]
        if i != 0:
            # rotating the elements 
            #   p[k], p[k+1], ..., p[k+i]
            # to the right by one position:
            #   p[k+i], p[k], p[k+1], ..., p[k+i-1]
            tmp = p[k:k+i+1].copy()
            M = len(tmp)
            for j in range(M):
                p[k + (j+1)%M] = tmp[j]
    return p

print("\nPermutations recovered from the factoradics:")
print(p1, "-->", factoradic2perm(f1))
print(p2, "-->", factoradic2perm(f2))

print("\nVerify conversions from perm -> fact > perm:")
for _ in range(20):
    p = rnd_permutation(p0)
    f = perm2factoradic(p)
    pp = factoradic2perm(f)
    print(f,":",p,"<-->",pp, \
    BrightGreen+"\u2713"+ResetColour if p==pp else \
    BrightRed+"\u2717"+ResetColour)

def int2factoradic(num):
    nfactlist = [1, 1]
    nfact = 1
    n = 1
    while nfact*(n+1) <= num:
        nfact = nfact*(n+1)
        nfactlist.append(nfact)
        n = n+1
    result = []
    while n != 0:
        div = num//(nfactlist[n])
        rem = num%(nfactlist[n])
        result = [div] + result
        num = rem
        n = n-1
    return result

print("\nShow the factoradics:")
for k in range(1,21):
    print(k, int2factoradic(k))

print("\nStep through all 5! permutations on 5 elements:")
for k in range(120):
    f = int2factoradic(k)
    f = [0]*(4-len(f)) + f
    #print(k,f)
    p = factoradic2perm(f)
    print("#{}".format(k+1),f,p)

print("\nStep through all 5! permutations of the 5 fruits:")
for k in range(120):
    f = int2factoradic(k)
    f = [0]*(4-len(f)) + f
    p = factoradic2perm(f)
    printlist(permutation(collection,p))

