awk 'BEGIN { imax = 0; } { if ($2 > imax) imax = $2; a[$2]+=1; n+=1; } END { for (i=1; i <= imax; ++i) print i,a[i]/n; }' sand.dat > hist-size.dat

