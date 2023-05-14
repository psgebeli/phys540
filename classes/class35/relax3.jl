using Random

rng = MersenneTwister(1975);

const N = 50
const a = 0.2 # relaaxtion param new := (1-a)*old + a*new

#phi = rand(rng,N,N)
phi = zeros(N,N)

function source1(i,j)
    half = 0.5*(N+1)
    dx = i-half
    dy = j-half
    if dx*dx + dy*dy < 0.0625*N*N
        return 10
    else
        return 0
    end
end

function source2(i,j)
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

function source3(i,j)
    quarter = 0.25*(N+1)
    dx1 = i-quarter
    dy1 = j-quarter
    threequarter = 0.75*(N+1)
    dx2 = i-threequarter
    dy2 = j-threequarter
    if dx1*dx1 + dy1*dy1 < 0.0625*N*N
        return +10
    elseif dx2*dx2 + dy2*dy2 < 0.04*N*N
        return -8
    else
        return 0
    end
end
err = 1
while err > 1.0E-4
#for sweeps in 1:1000
    #println("sweep=$sweeps")
    thiserr = 0
    for count in 1:(N*N)
        i = rand(rng,1:N)
        j = rand(rng,1:N)
        right = if (i == N) 1 else i+1 end
        left = if (i == 1) N else i-1 end
        up = if (j == N) 1 else j+1 end
        down = if (j == 1 ) N else j-1 end
        update = 0.25*( phi[right,j] + phi[left,j] + phi[i,up] + phi[i,down] - source1(i,j) )
        dphi = abs(phi[i,j] - update)
        if dphi > thiserr
            thiserr = dphi
        end
        phi[i,j] = (1-a)*phi[i,j] + a*update
    end
    global err = thiserr
    println("error is $err")
end

# output scalar phi
open("phi.dat", "w") do file
    for i in 1:N
        for j in 1:N
            write(file, " " * string(phi[i,j]) * " ")
        end
        write(file, "\n")
    end
end

# output field E = -grad phi
open("E.dat", "w") do file
    for i in 1:N
        right = if (i == N) 1 else i+1 end
        left = if (i == 1) N else i-1 end
        for j in 1:N
            up = if (j == N) 1 else j+1 end
            down = if (j == 1 ) N else j-1 end
            Ex = -0.5*(phi[right,j] - phi[left,j]);
            Ey = -0.5*(phi[i,up] - phi[i,down]);
            write(file, string(i) * " " * string(j) * " " * string(Ex) * " " * string(Ey) * "\n")
        end
    end
end
