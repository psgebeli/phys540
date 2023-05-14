awk 'BEGIN { t = 0; imax = 0;} { i = $1-t; if (i > imax) imax = i; a[i]+=1; t=$1; n+=1; } END { for (i=1; i <= imax; ++i) print i,a[i]/n; }' sand.dat > hist-time.dat

