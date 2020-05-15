import numpy as np

from functions.thinning import thinning

def minutiae(fingerprint):
    thinned = thinning(fingerprint.fingerprint)
    exit()