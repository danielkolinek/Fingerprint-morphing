'''
    Copy fingerprints to folders based on their classes
    ____________________________________________________

    Script is running generated program made in C++ with Innovatrics program 

    call the script like:
    python ./divideToClasses.py input_folder input_image_suffix output_folder path_to_class_detect.exe

    python ./divideToClasses.py C:/Users/danie/Documents/VUT/Otisky/db/fit_db bmp C:/Users/danie/Documents/VUT/Otisky/db/fit_db_classes C:/Users/danie/Documents/VUT/Otisky/Fingerprint-morphing/evaluation_modules/Compare_fingerprint/build/class_detect/Debug/class_detect.exe
'''
import os
import subprocess
import sys
import shutil
import cv2

def countFiles(folder):
    files_count = 0
    #get count of files
    for (dirpath, dirnames, filenames) in os.walk(folder):
        for filename in filenames:
            if filename.endswith(suf): 
                files_count+=1
    return files_count
    
# create folders if does not exist and return names of folder
def prepare_folders(res_dir):
    fingerprint_classes = ['unknown', 'left_loop', 'right_loop', 'arch', 'whorl']
    for f_class in fingerprint_classes:
        directory = res_dir + '/'+f_class
        if not os.path.exists(directory):
            os.makedirs(directory)
    return fingerprint_classes

if __name__ == "__main__":
    # load arguments
    folder = sys.argv[1]
    suf = sys.argv[2]
    res_dir = sys.argv[3]
    exe = sys.argv[4]

    # prepare folders for results
    fingerprint_classes = prepare_folders(res_dir)

    #actual fingerprint chacked count print
    files_count = countFiles(folder)
    #print('Fingerprint 0 of ' + str(files_count), end='/r')
    actual_test = 0



    for (dirpath, dirnames, filenames) in os.walk(folder):
        for filename in filenames:
            if filename.endswith(suf): 
                #ignore first images (*_1_*)
                if (filename.find('_1_') == 4):
                    continue
                #start evaluation for fingerprint1
                print('Test '+ str(actual_test) +' of ' + str(files_count))#, end='/r') # print actual step
                input_image = dirpath+'/'+filename
                #get size of image
                src = cv2.imread(input_image)
                print(input_image)
                #get class
                fingerprint_class = int(subprocess.run([exe, input_image, str(src.shape[0]), str(src.shape[1])], stdout=subprocess.PIPE).returncode)
                actual_test += 1
                #copy fingerprint to its folder
                if fingerprint_class >= 0 and fingerprint_class <=5:
                    shutil.copyfile(input_image, res_dir+'/'+fingerprint_classes[fingerprint_class]+'/'+filename)
