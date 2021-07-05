import os
import subprocess
import sys

folder = sys.argv[1]    #path to folder including all folders
suf = sys.argv[2]       #sufix of input pictures (only input not result of morphing, since it is always .tif)
out_name = sys.argv[3]  #name of output csv
res_name = sys.argv[4]  #result folder name
morph_suf = '.tif'
divider = '\\'
exe = 'Bin\Win64_x64\VerifyFinger.exe'


def printToCsv(arrayToPrint):
    f = open(out_name+".csv", "w")
    index = 0
    for x in arrayToPrint:
        f.write(str(index) + ',' + str(x) + '\n')
        index += 1
    f.close()


flm = len(folder)-1

if(folder.rindex(divider) == flm):
    folder = folder[:flm]

morph_folder = folder + "/"+res_name+"/" 

files_count = 0
#get count of files
print(morph_folder)
for (dirpath, dirnames, filenames) in os.walk(morph_folder):
    for filename in filenames:
        if filename.endswith(morph_suf): 
            files_count+=2

results = [0] * 2000

#actual test count print
print('Test 0 of ' + str(files_count), end='\r')
actual_test = 0

for (dirpath, dirnames, filenames) in os.walk(morph_folder):
    for filename in filenames:
        if filename.endswith(morph_suf): 
            #get filenames
            dash_pos = filename.rindex('-')
            filename1 = folder + divider + 'a' + divider +filename[:dash_pos]+suf
            filename2 = folder + divider + 'b' + divider +filename[dash_pos+1:filename.rindex('.')]+suf
            morph_filename = os.sep.join([dirpath, filename])
            #start evaluation for fingerprint1
            index1 = int(subprocess.run([exe, filename1, morph_filename], stdout=subprocess.PIPE).returncode)
            actual_test += 1
            print('Test '+ str(actual_test) +' of ' + str(files_count), end='\r') # print actual step
            #start evaluation for fingerprint2
            index2 = int(subprocess.run([exe, filename2, morph_filename], stdout=subprocess.PIPE).returncode)
            if(index1 > index2):
                results[index2] += 1 
            else:
                results[index1] += 1
            actual_test += 1
            print('Test '+ str(actual_test) +' of ' + str(files_count), end='\r') # print actual step
            #write res to file
            printToCsv(results)
print('')
#print results to file
