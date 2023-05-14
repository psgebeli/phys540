#!/bin/bash 

echo "" > bob-damped.dat
for m in 10
do
    for d in 0.001 0.01 0.1 1.0
    do
        echo "# mass ratio "$m" and drag" $d >> bob-damped.dat
        echo mass ratio $m and drag $d
        python3 bob-damped.py $m $d >> bob-damped.dat
        echo "" >> bob-damped.dat
        echo "" >> bob-damped.dat # for gnuplot, interpets empty space as separation
        # between datasets
    done
done