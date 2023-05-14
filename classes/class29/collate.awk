BEGIN { p=-1; sum=0.0; sum2=0.0; count=0 }
      { if ($1!=p) {
         if (p!=-1) print p, sum/count, sqrt(((sum2/count) - (sum/count)**2)/count);
         p=$1;
         sum=$2;
         sum2=$2*$2;
         count=1
      } else {
         sum += $2;
         sum2 += $2*$2;
         count += 1 }
      }
END   { print p, sum/count, sqrt(((sum2/count) - (sum/count)**2)/count) }
