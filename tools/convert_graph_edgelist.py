import sys
import gzip
import re

file_graph = sys.argv[1]

if re.search("\.gz$", file_graph):
    opener = gzip.open
else:
    opener = open

user = None
successors = []

outfile = open(file_graph+".graph", "w")

infile = opener(file_graph+".nnodes", "r")
outfile.write(infile.read())
infile.close()

infile = opener(file_graph+".nedges", "r")
outfile.write(infile.read())
infile.close()

infile = opener(file_graph+".sorted", "r")
for line in infile:
    user_from, user_to = line.rstrip().split(" ")
    if user_from != user:
        if user is not None:
            outfile.write("%s %d %s\n" % (str(user), len(successors), " ".join(successors)))
        successors = [user_to]
        user = user_from
    else:
        successors.append(user_to)
outfile.write("%s %d %s\n" % (str(user), len(successors), " ".join(successors)))
infile.close()

outfile.close()
