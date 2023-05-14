#!/bin/bash

for p in 0.1 0.2 0.3 0.4 0.45 0.5 0.55 0.58 0.59 0.6 0.61 0.62 0.65 0.70 0.72 0.75 0.80
do
   echo probability $p
   for samples in {1..50}
   do
      echo sample $samples
      echo $p $(python3 perc4.py $p report) >> cluster-size.dat
   done
done

