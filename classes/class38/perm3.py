def is_valid_perm(p):
    for n in range(len(p)):
        if not n in p:
            return False
    return True

def is_valid_fact(f):
    # factoradic
    # f[0] + 2!*f[1] + 3!*f[2] + ... + (n-1)!*f[n-2]
    # in the form of a list f = [ f[0], f[1], ..., f[n-2] ]
    # with the list elements satisfying
    # f[0] < n, f[1] < n-1, ..., f[n-2] < 2
    n = len(f)+1
    for k in range(n-1):
        if f[k] >= n-k:
            return False
    return True

def permutation(x, p):
    assert is_valid_perm(p)
    return [x[p[n]] for n in range(len(p))]

def perm2fact(p):
    assert is_valid_perm(p)
    N = len(p)
    f = [0]*(N-1)
    for k in range(N-1):
        pk = p[k]
        i = 0
        for j in range(k+1, N):
            if p[j] < pk:
                i = i+1
        f[k] = i
    assert is_valid_fact(f)
    return f

def fact2perm(f):
    assert is_valid_fact(f)
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
    is_valid_perm(p)
    return p

def int2fact(num):
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

def fact2int(f):
    assert is_valid_fact(f)
    result = 0
    radix = 1
    n = len(f)+1
    for k in range(n-1):
        result += f[k]*radix
        radix *= k+2
    return result

def next_and_wrap(f):
    # increment f by one and possibly wrap around to 0 (modulo n!)
    assert is_valid_fact(f)
    n = len(f)+1
    f[0] += 1
    for k in range(n-1):
        if f[k] == n-k:
            f[k] = 0
            if (k < n-2):
                f[k+1] += 1
    assert is_valid_fact(f)

f = [0]*4  # maps to the identity permutation in S_5
for k in range(121):
    print("{}: ".format(k), f)
    next_and_wrap(f)

def next(f):
    # increment f by one and possibly wrap around to 0 (modulo n!)
    assert is_valid_fact(f)
    n = len(f)+1
    f[0] += 1
    for k in range(n-1):
        if f[k] == n-k:
            f[k] = 0
            if (k < n-2):
                f[k+1] += 1
            else:
                f[0] = -1
    assert is_valid_fact(f)

def incrementable(f):
    return f[0] != -1

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

def cycle_decomp(p):
    N = len(p)
    label = [-1]*N
    highestlabel = 0
    s = ""
    for k in range(N):
        if label[k] > -1:
            continue
        i = k
        label[i] = highestlabel
        s += "({}".format(i)
        while p[i] != k:
            i = p[i]
            label[i] = highestlabel
            s += ", {}".format(i)
        s += ") "
        highestlabel += 1
    return highestlabel, s

f = [0]*3
for k in range(24):
    p = fact2perm(f)
    h, s = cycle_decomp(p)
    print("{}: {} -> {}".format(h, f, s))
    next(f)

# print out all the 1-cycles, pure transpositions, and
# identity elements of S_8

f = [0]*7
unicycles = 0
transpositions = 0
identity = 0
for k in range(8*7*6*5*4*3*2):
    p = fact2perm(f)
    h, s = cycle_decomp(p)
    if h == 1:
        unicycles += 1
        print("{}: {} -> {}".format(h,f,s))
    elif h == 7:
        transpositions += 1
        print("{}: {} -> {}".format(h,f,s))
    elif h == 8:
        identity += 1
        print("{}: {} -> {}".format(h,f,s))
    next(f)
print("S_8 contains {} 1-cycles, {} pure transpositions, and {} identity element".format(unicycles,transpositions,identity))


def cycle_signature(p):
    N = len(p)
    label = [-1]*N
    highestlabel = 0
    sig = [0]*N
    s = ""
    for k in range(N):
        if label[k] > -1:
            continue
        i = k
        thiscycle = 0
        label[i] = highestlabel
        s += "({}".format(i)
        while p[i] != k:
            i = p[i]
            thiscycle += 1
            label[i] = highestlabel
            s += ", {}".format(i)
        s += ") "
        highestlabel += 1
        sig[thiscycle] += 1
    return highestlabel, sig, s

f = [0]*3
for k in range(24):
    p = fact2perm(f)
    h, sig, s = cycle_signature(p)
    print("{}/{}: {} -> {}".format(h,sig,f,s))
    next(f)
