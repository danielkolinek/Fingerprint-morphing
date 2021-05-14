import numpy as np


# load needed arrays
# numpy part
morph_ori = np.loadtxt('morph_ori.csv', delimiter=',')
morph_freq = np.loadtxt('morph_freq.csv', delimiter=',')

# list of touples part 
## termintions
import csv
with open('morph_terminations.csv') as f:
    morph_terminations_string =[tuple(line) for line in csv.reader(f)]
# covert list of strings (morph_minutiae) to list of ints
morph_terminations=[]
for x in morph_terminations_string:
    morph_terminations.append((int(x[0]), int(x[1])))

## bifurcations
import csv
with open('morph_bifurcations.csv') as f:
    morph_bifurcations_string =[tuple(line) for line in csv.reader(f)]
# covert list of strings (morph_minutiae) to list of ints
morph_bifurcations=[]
for x in morph_bifurcations_string:
    morph_bifurcations.append((int(x[0]), int(x[1])))

