#!/bin/bash

make perc3 >&2

for L in 10 20 30 60 100 200 300 600
do
   echo Computing L = $L >&2
   for p in 0.3 0.4 0.5 0.55 0.57 0.58 0.585 0.59274621 0.605 0.61 0.62 0.63 0.65 0.7 0.75 0.80
   do
      echo Computing p = $p >&2
      echo $p $L $(./perc3 $L $p)
   done
   echo
   echo
done
