"""
    Morphing of Fingerprints
    File:   args.py
    Author: Daniel Kolinek
    Date:   01/2021
    Brief:  Implements work with arguments

    Version: 1.0
"""

import argparse

# run like python3 morph.py --image_1 ../img/DB1_B/101_2.tif --image_2 ../img/DB1_B/102_2.tif --blocksize 10
def parse_args():
    parser = argparse.ArgumentParser(description='Morph two fingeprints')
    parser.add_argument("--image_1",
                        metavar="/path/to/first/fingerprint/image/", required=False,
                        help="Path to first fingerprint image")
    parser.add_argument("--image_2",
                        metavar="/path/to/second/fingerprint/image/", required=False,
                        help="Path to second fingerprint image")
    parser.add_argument('--blocksize', required=False,
                        metavar="int",
                        help="Blocksize for orientation field (image will be divided into blocksize x blocksize squares\
                        and for each square will be counted orientation)")
    parser.add_argument('--save', required=False,
                        metavar="filename",
                        help="filename for result (example \"--save result\" will create result.jpg)")
    parser.add_argument('--tests', required=False,
                        metavar="folder",
                        help="Folder including test images")
    parser.add_argument('--plot', 
                        action='store_true',  
                        help="Plot result with all steps")
    parser.add_argument('--suf', required=False,
                        metavar="Suffix of file (.bmp /.tif /...)",  
                        help="Input suffix of file")
    parser.add_argument('--type', required=False,
                        metavar="Type of morphed fingerprint generation",  
                        help="1 = picture based, 2 = minutiae based")

    return parser