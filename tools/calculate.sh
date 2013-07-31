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

./bin/algorithms $file_base.graph $file_base.graph.temp

echo "#num vertex_id in_degree out_degree recipr clust_coeff pagerank wcc scc" > $2
join $file_base.tableids $file_base.graph.temp >> $2

rm $file_base.graph.temp

