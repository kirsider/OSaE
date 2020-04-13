import os, glob

print("Input path for searching files: ",)
path = input()

try:
    os.chdir(path)
except Exception:
    print("There is no such directory.")

print("Input file extension (i.e. txt, doc): ",)
extension = input()

print("Input file name for saving data: ")
filename = input()

with open(filename, 'a') as file:
    for fname in glob.glob("*." + extension):
        file.writelines(fname + "\n")
        print(fname)
