# Задание
# 2.3.2. При помощи анализа цепочек выяснить, какой из файлов корневого каталога 
# занимает наибольшее число кластеров. Имя этого файла показать на экране.

import os
import sys

# default cluster size for NTFS
cluster_size = 8 * 1024        

biggest = ("", -1)

print("Input directory for searching largest file: ")
directory = input()

print("Searching in: " + directory + " ...")

def search(dir):
    global biggest
    for item in os.listdir(dir):
        item = dir + "/" + item
        if os.path.isdir(item):
            search(item)
        else:
            itemsize = os.path.getsize(item)
            if itemsize > biggest[1]:
                    biggest = (item, itemsize)

search(directory)

if biggest[1] != -1:
    print("File: {:^40}".format(biggest[0]))
    print("File size: {:^40} KB".format(biggest[1]))
    print("Num of clusters: {:^40}".format(biggest[1] // cluster_size))

    