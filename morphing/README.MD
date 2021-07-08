# Morph fingerprints

Aplication for fingerprint morphing

## Run morphing
`python3 morph.py [-h] --image_1 _ --image_2 _ --blocksize _ --save --tests _ --plot _ --suf _`         

-   `-h`, `--help`
    -   show help

-   `--image_1 /path/to/first/fingerprint/image/`
    -   Path to first fingerprint image

-   `--image_2 /path/to/second/fingerprint/image/`
    -   Path to second fingerprint image

-   `--blocksize int`
    -   Blocksize for orientation field (image will be divided into blocksize x blocksize squares and for each square will be counted orientation, frequency image)

-   `--save`
    -   Filename for result image, not required, if not given no save will be created (example `--save result` will create result.jpg)

-   `--tests`
    -   Folder including test images

-   `--plot`
    -   Plot result with all steps

-   `--suf`
    -   Suffix of file (.bmp /.tif /...)
## Example run:
`python morph.py --image_1 ../img/DB1_B/101_2.tif --image_2 ../img/DB1_B/102_2.tif --blocksize 10 --save result --type 1`

## Author: 
    Daniel Kolínek, xkolin05