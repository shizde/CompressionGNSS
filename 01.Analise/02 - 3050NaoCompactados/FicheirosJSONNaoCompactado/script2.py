import functools
import operator
import datetime
import random
import math
import csv
import re
import os

# Definitions
location = '/home/rperez/Dropbox/01 - PRafael/01 - Dados/04 - Simulacao/03 - AnalisadorLZ77/02 - NaoCompactados/FicheirosJSONNaoCompactado'
files_in_dir = []

# r=>root, d=>directories, f=>files
for r, d, f in os.walk(location):
    for item in f:
        if '.json' in item:
            files_in_dir.append(os.path.join(r, item))


def remover_lz77():
    # Definitions
    location = '/home/rperez/Dropbox/01 - PRafael/01 - Dados/04 - Simulacao/03 - AnalisadorLZ77/02 - NaoCompactados/FicheirosJSONNaoCompactado'
    files_in_dir = []

    # r=>root, d=>directories, f=>files
    for r, d, f in os.walk(location):
        for item in f:
            if '.json' in item:
                files_in_dir.append(os.path.join(r, item))

    for item in files_in_dir:
        if item[-5:] == '.lz77':
            command = 'rm ' + item[127:]
            os.system(command)

os.system('rm resultados.csv')
with open("resultados.csv", mode='a') as csv_file:
            for item in files_in_dir:
                if item[-5:] == '.json':
                    lz77 = item[127:] + '.lz77'
                    lz77_command = './lz77 -c -i '+item[127:]+' -o '+lz77
                    os.system(lz77_command)

                    #Filename
                    csv_file.write(item[127:]+',')
                    #Original Size
                    file_size_original = os.path.getsize(item[127:])
                    csv_file.write(str(file_size_original)+',')
                    #LZ77 Size
                    file_size_lz77 = os.path.getsize(lz77)
                    csv_file.write(str(file_size_lz77)+',')
                    #Close line
                    csv_file.write('\n')
                    #print('Name:', item[127:], 'O.Size:',file_size_original,'LZ77:',file_size_lz77,'I:',i,'J:',j)
            remover_lz77()
