"""
    Morphing of Fingerprints
    File:   args.py
    Author: Daniel Kolinek
    Date:   01/2021
    Brief:  Implements work with arguments

    Version: 1.0
"""

import argparse
"""
run :
    python morph.py --image_2 ../img/DB1_B/101_2.tif --image_1 ../img/DB1_B/102_2.tif --blocksize 10 --plot
or for testing:
    python morph.py `
        --folder1 ../../db/fit_db_classes/whorl/a `
        --folder2 ../../db/fit_db_classes/whorl/b `
        --folder3 ../../db/fit_db_classes/whorl/res_mask `
        --blocksize 10 --suf bmp --center --mask
"""
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
    parser.add_argument('--folder1', required=False,
                        metavar="folder",
                        help="First folder including images for generation")
    parser.add_argument('--folder2', required=False,
                        metavar="folder",
                        help="Second folder including images for generation")
    parser.add_argument('--folder3', required=False,
                        metavar="folder",
                        help="folder for generating results")
    parser.add_argument('--plot', 
                        action='store_true',  
                        help="Plot result with all steps")
    parser.add_argument('--suf', required=False,
                        metavar=".bmp/.tif /...",  
                        help="Input suffix of file")
    parser.add_argument('--center', 
                        action='store_true',  
                        help="Set barycenter as center of first fingerprint")
    parser.add_argument('--eq', 
                        action='store_true',  
                        help="Use CLAHE on result")
    parser.add_argument('--gaus', 
                        action='store_true',  
                        help="Use gaussian blur on result")
    parser.add_argument('--mask', 
                        action='store_true',  
                        help="Allighn fingerprints by masks")

    return parser