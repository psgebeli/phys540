using Random

rng = MersenneTwister(1975);

N = 100 
phi = rand(rng,N,N)

function oldsource(i,j)
    half = 0.5*(N+1)
    dx = i-half
    dy = j-half
    if dx*dx + dy*dy < 0.0625*N*N
        return 10
    else
        return 0
    end
end

function source(i,j)
    quarter = 0.25*(N+1)
    dx1 = i-quarter
    dy1 = j-quarter
    threequarter = 0.75*(N+1)
    dx2 = i-threequarter
    dy2 = j-threequarter
    if dx1*dx1 + dy1*dy1 < 0.0625*N*N
        return +10
    elseif dx2*dx2 + dy2*dy2 < 0.0625*N*N
        return -10
    else
        return 0
    end
end

err = 1
while err > 1.0E-8
#for sweeps in 1:1000
    #println("sweep=$sweeps")
    thiserr = 0
    i0 = rand(rng,0:(N-1))
    j0 = rand(rng,0:(N-1))
    for i1 in 0:2:(N-1)
        for j1 in 0:2:(N-1)
            i = (i0 + i1)%N + 1
            j = (j0 + j1)%N + 1
            #println("i=$i j=$j")
            right = if (i == N) 1 else i+1 end
            left = if (i == 1) N else i-1 end
            up = if (j == N) 1 else j+1 end
            down = if (j == 1 ) N else j-1 end
            update = 0.25*( phi[right,j] + phi[left,j] + phi[i,up] + phi[i,down] - source(i,j) )
            dphi = abs(phi[i,j] - update)
            if dphi > thiserr
                thiserr = dphi
            end
            phi[i,j] = 0.95*phi[i,j] + 0.05*update
        end
    end
    global err = thiserr
    println("error is $err")
end

for i in 1:N
    for j in 1:N
        print(phi[i,j],"  ")
    end
    println("")
end
