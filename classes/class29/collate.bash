#!/bin/bash

sort -n -k1 -n -k2 cluster-size.dat | awk -f collate.awk > ave-cluster-size.dat
