#!/bin/bash

for FILE in circle lines triangle square boxes
do
   epstopdf $FILE.eps
done

cd snapshots
for FILE in $(ls outfile*.eps)
do
   epstopdf $FILE
   BASE=${FILE%.eps}
   echo $BASE
   convert -density 72 $BASE.pdf $BASE.png
done
cd ..

convert -delay 3 -loop 0 -dispose Previous snapshots/outfile*.png collision.gif

