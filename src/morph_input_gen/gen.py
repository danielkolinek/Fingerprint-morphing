import numpy as np


# load needed arrays
# numpy part
morph_ori = np.loadtxt('morph_ori.csv', delimiter=',')
morph_freq = np.loadtxt('morph_freq.csv', delimiter=',')
# list of touples part
import csv
with open('morph_minutiae.csv') as f:
    morph_minutiae_string =[tuple(line) for line in csv.reader(f)]
# covert list of strings (morph_minutiae) to list of ints
morph_minutiae=[]
for x in morph_minutiae_string:
    morph_minutiae.append((int(x[0]), int(x[1])))

