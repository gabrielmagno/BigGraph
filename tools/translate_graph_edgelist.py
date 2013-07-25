import sys
import gzip
import re

file_graph = sys.argv[1]

if re.search("\.gz$", file_graph):
    opener = gzip.open
else:
    opener = open

table_ids = {}
infile = open(file_graph+".tableids", "r")
for line in infile:
    id_new, id_old = line.rstrip().split(" ")
    table_ids[id_old] = id_new
infile.close()

infile = opener(file_graph, "r")
for line in infile:
    id_old_a, id_old_b = line.rstrip().split(" ")
    id_new_a, id_new_b = table_ids[id_old_a], table_ids[id_old_b]
    sys.stdout.write("%s %s\n" % (id_new_a, id_new_b))
infile.close()

