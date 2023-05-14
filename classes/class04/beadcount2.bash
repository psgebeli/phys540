#!/bin/bash

if (( $# != 1 ))
then
    exit 1
elif (( $1 < 1 ))
then
    exit 1
fi

./beadcount.bash $1 | awk 'BEGIN { print $5 } { x += $5 } END { print x }'
