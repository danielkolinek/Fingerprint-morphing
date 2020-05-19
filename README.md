# Morph fingerprints

Aplication for fingerprint morphing

## Contents:
-   img: Some example input images
-   src: source code
    - functions: functions need

## Run morphing
`python3 morph.py [-h] --image_1 /path/to/first/fingerprint/image/ --image_2 /path/to/second/fingerprint/image/ --blocksize int `         

-   `-h`, `--help`
    -   show help

-   `--image_1 /path/to/first/fingerprint/image/`
    -   Path to first fingerprint image

-   `--image_2 /path/to/second/fingerprint/image/`
    -   Path to second fingerprint image

-   `--blocksize int`
    -   Blocksize for orientation field (image will be divided into blocksize x blocksize squares and for each square will be counted orientation, frequency image)

# Example run:
`python3 morph.py --image_1 ../img/DB1_B/101_2.tif --image_2 ../img/DB1_B/102_2.tif --blocksize 10`

## Author: 
    Daniel Kolínek, xkolin05