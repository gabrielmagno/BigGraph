#!/bin/bash

file_base=$1
file_out=$2

if [ ! -f $file_base.graph ];
then
    echo "* Converting graph"
    ./tools/convert.sh $file_base
fi

if [ ! -f $file_base.tableids ];
then
    echo "* Creating table of ids"
    awk '{if (NR > 2) {print $1, $1}}' $file_base.graph | sort -k 1n > $file_base.tableids
fi

make

echo "#num vertex_id in_degree out_degree recipr clust_coeff pagerank wcc scc" > $file_out
./bin/algorithms_omp $file_base.graph | join $file_base.tableids - >> $file_out

