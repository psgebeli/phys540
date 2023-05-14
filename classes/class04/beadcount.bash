#!/bin/bash

if (( $# != 1))
then
    exit 1
elif (( $1 < 1))
then
    exit 1
fi
N=$1
for i in `jot - 0 $N`
do
    NUM=`./beads $i $N | wc -l`
    echo "("$N" choose "$i") = "$NUM
done
