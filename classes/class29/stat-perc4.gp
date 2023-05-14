probs=system("cat cluster-size.dat | cut -f1 -d' ' | sort -n | uniq")

set print "ave-cluster-size2.dat"
unset print

set print "ave-cluster-size2.dat" append
do for [p in probs] {
   stat "cluster-size.dat" using ($1==p ? $2 : 1/0) name "cluster" nooutput
   print p, cluster_mean, cluster_mean_err
}
unset print
