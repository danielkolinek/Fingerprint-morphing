import os
import subprocess
import sys

folder = sys.argv[1]
suf = sys.argv[2]
morph_suf = '.tif'
divider = '\\'
exe = 'Bin\Win64_x64\VerifyFinger.exe'


def printToCsv(arrayToPrint):
    f = open("result.csv", "w")
    index = 0
    for x in arrayToPrint:
        f.write(str(index) + ',' + str(x) + '\n')
        index += 1
    f.close()


flm = len(folder)-1

if(folder.rindex(divider) == flm):
    folder = folder[:flm]

morph_folder = folder[:folder.rindex(divider)+1] + "morph-res" 

files_count = 0
#get count of files
for (dirpath, dirnames, filenames) in os.walk(morph_folder):
    for filename in filenames:
        if filename.endswith(suf): 
            files_count+=2

results = [0] * 2000

#actual test count print
print('Test 0 of ' + str(files_count), end='\r')
actual_test = 0

for (dirpath, dirnames, filenames) in os.walk(morph_folder):
    for filename in filenames:
        if filename.endswith(suf): 
            #get filenames
            dash_pos = filename.rindex('-')
            filename1 = folder + divider +filename[:dash_pos]+morph_suf
            filename2 = folder + divider +filename[dash_pos+1:filename.rindex('.')]+morph_suf
            morph_filename = os.sep.join([dirpath, filename])
            #start evaluation for fingerprint1
            index1 = int(subprocess.run([exe, filename1, morph_filename], stdout=subprocess.PIPE).returncode)
            actual_test += 1
            print('Test '+ str(actual_test) +' of ' + str(files_count), end='\r') # print actual step
            #start evaluation for fingerprint2
            index2 = int(subprocess.run([exe, filename2, morph_filename], stdout=subprocess.PIPE).returncode)
            if(index1 > 48 and index2 > 48):
                results[index1] += 1 
                results[index2] += 1 
            else:
                results[0] += 2
            actual_test += 1
            print('Test '+ str(actual_test) +' of ' + str(files_count), end='\r') # print actual step
            #write res to file
            printToCsv(results)
print('')
#print results to file
