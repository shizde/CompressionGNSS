import numpy as np
import pandas as pd   
import time
# FILE DECLARATIONS
FILENAME = "21141500"
HUF_FORMAT = ".HUF"
JSON_FORMAT = ".JSON"

# SEPARATE DICTIONARY DATA
dec_dict = []
len_dict = []
cod_dict = []
bin_dict = []

content = ""

# DATA ENGINEERING PROCESS
try:
    dt = np.dtype('B')
    data = np.fromfile(FILENAME+HUF_FORMAT, dtype=dt)
    df = pd.DataFrame(data, columns=['ASCII'])
    #print(df)

except IOError:
    print("Error while opening the file.")

# FIRST VALUE EQUALS TO THE DICTIONARY CONTENT SIZE
content_size = df.size
#print(df.loc[0])
dictionar_size = df.at[0,'ASCII'] * 3

# ITERATE THROUGH DECIMAL
for i in range(1, dictionar_size+1,3):
    byte = df.at[i,'ASCII']
    dec_dict.append(byte)

# ITERATE THROUGH LENGHT OF 
for i in range(2, dictionar_size+1,3):
    byte = df.at[i,'ASCII']
    len_dict.append(byte)

# ITERATE THROUGH BINARY
for i in range(3, dictionar_size+1,3):
    byte = df.at[i,'ASCII']
    cod_dict.append(byte)

# REWRITE BINARY VALUE FOR EACH CODE
for y,z in zip(len_dict,cod_dict):
    binary = str("{0:08b}".format(z))
    slice_binary = int(y)
    bin_dict.append(binary[-slice_binary:])

# ITERATE THROUGH FILE CONTENT
for j in range(dictionar_size+1,content_size):
    byte = df.at[j,'ASCII']
    binary = "{0:08b}".format(byte)
    content += str(binary)

#print(dictionar_size)
#print(dec_dict)
#print(len_dict)
#print(cod_dict)
#print(bin_dict)
#print(content)

# DECODE FILE
with open(FILENAME+JSON_FORMAT,'a') as result_file:    
    i=0
    code_search = ""
    decoded = ""
    arr = np.array(bin_dict)
    while i < len(content)-8:
        code_search += content[i]
        if code_search in bin_dict:
            result = np.where(arr == code_search)
            index = int(result[0])
            character_decoded = chr(dec_dict[index])
            #print(character_decoded)
            decoded += character_decoded
            result_file.write(character_decoded)
            code_search = ""
        i += 1
        
    print(decoded)

result_file.close()
