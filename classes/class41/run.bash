#!/bin/bash

make capcount2
for n in 2 3 4 5 6 7 8 9 10 11 12 13
do
   ./capcount2 $n > all$n.txt
done