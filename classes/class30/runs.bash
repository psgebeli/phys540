#!/bin/bash

make van-der-pol

test -e vpd.dat && rm vdp.dat
for mu in 0.1 0.2 0.5 1.0 2.0 5.0
do
   echo Running van der Pol for mu=$mu
   ./van-der-pol $mu >> vdp.dat
done

test -e vdp-forced.dat && rm vdp-forced.dat
for mu in 8.53
do
   for A in 1.2 2.5
   do
      for w in 0.6283185 0.7512 0.85
      do
         echo Running van der Pol for mu=$mu A=$A w=$w
         ./van-der-pol $mu $A $w >> vdp-forced.dat
      done
   done
done

