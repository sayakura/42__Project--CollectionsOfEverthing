import io
import os

path = './ans'

name_arr2 = []

for filename in os.listdir(path):
    name_arr2.append(filename)
name_arr2.sort()
"""
for filename in name_arr2: 
    map = path + '/' +filename
    if (os.stat(map).st_size == 0):
        file = open(map, 'w')
        file.write("MAP ERROR\n")
        file.close()
"""
for filename in name_arr2:
    map = path + '/' +filename
    file = open(map, 'r')
    file2 = open("answer", 'a')
    file2.write(file.read())
