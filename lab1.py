# Задание
#  1.3.3. С клавиатуры вводятся расширение имени для поиска файлов (например, txt) и имя файла результата. 
# Необходимо найти все файлы с этим расширением и сохранить их имена в результирующем файле. 
# В случае если файл для хранения результата уже существует, его старое содержимое должно быть сохранено, 
# а новые записи надо добавлять в конец файла.

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
