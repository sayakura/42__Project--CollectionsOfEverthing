import io
import os

execute = '../grimly'
path = './maps'
name_arr = []

for filename in os.listdir(path):
    name_arr.append(filename)
name_arr.sort()

for filename in name_arr:
    map = path + '/' + filename
    os.system(execute + ' ' + map + ' >> myoutput')
