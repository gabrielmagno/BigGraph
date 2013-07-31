#!/bin/bash

file_graph=$1
file_extension="${file_graph##*.}"

if [ $file_extension != "gz" ]
then
    READ="cat"
    WRITE="cat"
else
    READ="zcat"
    WRITE="gzip -c"
fi

$READ $file_graph | awk '{print $1; print $2}' | sort | uniq | shuf | awk '{print (NR-1), $0}' > $file_graph.tableids

python tools/translate_graph_edgelist.py $file_graph | sort -k1n -k2n | uniq | $WRITE > $file_graph.sorted

cat $file_graph.tableids | wc -l | $WRITE > $file_graph.nnodes
$READ $file_graph.sorted | wc -l | $WRITE > $file_graph.nedges
python tools/convert_graph_edgelist.py $file_graph

rm $file_graph.sorted $file_graph.nnodes $file_graph.nedges

