import os
import sys
from PIL import Image

folder = sys.argv[1]
dpi = int(sys.argv[2])

for (dirpath, dirnames, filenames) in os.walk(folder):
    for filename in filenames:
        if filename.endswith('.tif'): 
            im = Image.open(os.sep.join([dirpath, filename]))
            im.save("res/" + filename, dpi=(dpi, dpi))