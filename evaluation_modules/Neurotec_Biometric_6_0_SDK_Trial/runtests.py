import os
import subprocess
import sys

"""
    Python script to run tests with use of VeriFinger tool

    run script:
    python runtests.py exe folder_a folder_b folder_res suf out_name

    example:
        cd D:/Download/Neurotec_Biometric_12_1_SDK_2021-04-15/Neurotec_Biometric_12_1_SDK/Bin/Win64_x64
        
        python runtests.py VerifyFingerCPP.exe D:/Download/fit_db_classes/arch/a_dpi/  D:/Download/fit_db_classes/arch/b_dpi/  D:/Download/fit_db_classes/arch/res/  .bmp result_arch
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/arch/a_dpi/  G:/fit_db_classes/arch/b_dpi/  G:/fit_db_classes/arch/res_center/  .bmp result_arch_center
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/combined/a_dpi/  G:/fit_db_classes/combined/b_dpi/  G:/fit_db_classes/combined/res/  .bmp result_combined
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/combined/a_dpi/  G:/fit_db_classes/combined/b_dpi/  G:/fit_db_classes/combined/res_center/  .bmp result_combined_center
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/left_loop/a_dpi/  G:/fit_db_classes/left_loop/b_dpi/  G:/fit_db_classes/left_loop/res/  .bmp result_left_loop
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/left_loop/a_dpi/  G:/fit_db_classes/left_loop/b_dpi/  G:/fit_db_classes/left_loop/res_center/  .bmp result_left_loop_center
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/right_loop/a_dpi/  G:/fit_db_classes/right_loop/b_dpi/  G:/fit_db_classes/right_loop/res/  .bmp result_right_loop
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/right_loop/a_dpi/  G:/fit_db_classes/right_loop/b_dpi/  G:/fit_db_classes/right_loop/res_center/  .bmp result_right_loop_center
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/whorl/a_dpi/  G:/fit_db_classes/whorl/b_dpi/  G:/fit_db_classes/whorl/res/  .bmp result_whorl
        python runtests.py VerifyFingerCPP.exe G:/fit_db_classes/whorl/a_dpi/  G:/fit_db_classes/whorl/b_dpi/  G:/fit_db_classes/whorl/res_center/  .bmp result_whorl_center
        TIMEOUT /T 1 ./VerifyFingerCPP.exe D:/Download/fit_db_classes/arch/res/1104_2_2_L2-1284_3_1_P4.tif D:/Download/fit_db_classes/arch/res/1104_2_2_L2-1284_3_1_P4.tif
"""

def printToCsv(arrayToPrint):
    f = open(out_name+".csv", "w")
    index = 0
    for x in arrayToPrint:
        f.write(str(index) + ',' + str(x) + '\n')
        index += 1
    f.close()

def recognise(exe, fingerprint1, fingerprint2, timeoutSeconds):
    index = 4000
    index_valid = False
    counter = 0
    max_tries = 10
    while((index > 2000 or not index_valid)):
        try:
            index = int(subprocess.run([exe, fingerprint1, fingerprint2], stdout=subprocess.PIPE, timeout=timeoutSeconds).returncode)#os.system(exe + " " +filename1 + " " +morph_filename)#int(subprocess.run([exe, filename1, morph_filename], stdout=subprocess.PIPE).returncode)
            index_valid = True
            print(index)
            if (index > 3221225477 or counter > max_tries):#exceprion for bad resolution of minutuae
                return -1
        except:
            index_valid = False
            if (counter > max_tries):#exceprion for bad resolution of minutuae
                return -1
        counter+=1 
    return index

# Load arguments 
exe = sys.argv[1]      #path to console VerifyFinger application with name
folder_a = sys.argv[2]      #path to folder with inputs a
folder_b = sys.argv[3]      #path to folder with inputs b
folder_res = sys.argv[4]    #path to folder with inputs results
suf = sys.argv[5]       #sufix of input pictures (only input not result of morphing, since it is always .tif)
out_name = sys.argv[6]  #name of output csv

# Set variables
morph_suf = '.tif'

files_count = 0
#get count of files
for (dirpath, dirnames, filenames) in os.walk(folder_res):
    for filename in filenames:
        if filename.endswith(morph_suf): 
            files_count+=1

results = [0] * 2000

#actual test count print
print('Test 0 of ' + str(files_count))#, end='/r')
actual_test = 0

for (dirpath, dirnames, filenames) in os.walk(folder_res):
    for filename in filenames:
        if filename.endswith(morph_suf): 
            #get filenames
            dash_pos = filename.rindex('-')
            filename1 = folder_a +filename[:dash_pos]+suf
            filename2 = folder_b +filename[dash_pos+1:filename.rindex('.')]+suf
            morph_filename = os.sep.join([dirpath, filename])
            #start evaluation for fingerprint1
            print(filename1)
            print(filename2)
            print(morph_filename)

            index1 = recognise(exe, filename1, morph_filename, 5)
            index2 = recognise(exe, filename2, morph_filename, 5)

            if(index1 >=0 and index2 >=0):
                if(index1 > index2):
                    results[index2] += 1 
                else:
                    results[index1] += 1
            actual_test += 1
            print('Test '+ str(actual_test) +' of ' + str(files_count)) # print actual step
            #write res to file
            printToCsv(results)
print('')

#print results to file
