import functools
import operator
import datetime
import random
import math
import csv
import re
import os

# Definitions
location = 'PATH TO FILES'
files_in_dir = []

# r=>root, d=>directories, f=>files
for r, d, f in os.walk(location):
    for item in f:
        if '.json' in item:
            files_in_dir.append(os.path.join(r, item))

      

#COMPRESSING HUFFMAN FILES
for item in files_in_dir:
    huffman_command = './huffman '+item[55:]
    os.system(huffman_command)
   
#COMPRESSING LZ77 FILES
for item in files_in_dir:
    lz77_command = './lz77 '+item[55:]
    os.system(lz77_command)

#COMPRESSING LZW FILES
for item in files_in_dir:
    lzw_command = './lzwv5 -c '+item[55:]+' '+item[55:]+".lzw"
    os.system(lzw_command)

#COMPRESSING RLE FILES
for items in files_in_dir:
    rle_command = './rle '+item[55:]
    os.system(rle_command)

# WRITING RESULTS
with open("resultados.csv",mode='w') as csv_file:
    csv_file.write("Name, Original Size, Huffman, LZ77, LZW, LRE\n")
    for item in files_in_dir:
        huffman = item[55:] + '.compressed'
        lz77 = item[55:] + '.lz77'
        lzw = item[55:] + '.lzw'
        rle = item[55:] + '.rle'
        #Filename
        csv_file.write(item[55:]+',')
        #Original Size
        file_size_original = os.path.getsize(item[55:])
        csv_file.write(str(file_size_original)+',')
        #Huffman Size
        file_size_huffman = os.path.getsize(huffman)
        csv_file.write(str(file_size_huffman)+',')
        #LZ77 Size
        file_size_lz77 = os.path.getsize(lz77)
        csv_file.write(str(file_size_lz77)+',')
        #LZW Size
        file_size_lzw = os.path.getsize(lzw)
        csv_file.write(str(file_size_lzw)+',')
        #LRE Size
        file_size_rle = os.path.getsize(rle)
        csv_file.write(str(file_size_rle))
        #Close line
        csv_file.write('\n')

    
   
#=================================================#


