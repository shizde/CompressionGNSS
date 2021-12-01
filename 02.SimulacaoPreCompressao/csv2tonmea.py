import functools
import operator
import datetime
import random
import math
import csv
import re

# Function to convert Decimal Degrees into DMS Format (Degrees, Minutes, Seconds)
def deg_to_dms(deg, type='lat'):
    decimals, number = math.modf(deg)
    d = int(number)
    m = int(decimals * 60)
#   In seconds field, for Default DGS use 3600.00 || For NMEA DGS use 360000.00
    s = (deg - d - m / 60) * 360000.00
    compass = {
        'lat': ('N', 'S'),
        'lon': ('E', 'W')
    }
    compass_str = compass[type][0 if d >= 0 else 1]
#    Returning Default DGS    
#    return '{}º{}\'{:.2f}"{}'.format(abs(d), abs(m), abs(s), compass_str)
#   
#   Returning the NMEA DGS Format
    return '{}{}.{:.0f},{}'.format(abs(d), abs(m), abs(s), compass_str)


# Calculating the Checksum for NMEA String

def checksum(sentence):
    sentence = sentence.strip('\n')
    nmeadata, cksum = sentence.split('*', 1)
    calc_cksum_int = functools.reduce(operator.xor, (ord(s) for s in nmeadata), 0)
    calc_cksum_conv = hex(calc_cksum_int)
    calc_cksum = str.upper(calc_cksum_conv)[2:]


    return nmeadata, int(cksum,16),calc_cksum

# Definition of Files Paths and Files Names
path_open = '/home/rperez/Dropbox/Projects/packJson/04 - 200pontos/'
file_open = 'zigzagZI200'
format_open = '.csv'
path_write = '/home/rperez/Dropbox/Projects/packJson/04 - 200pontos/'
file_write = 'NMEA'+file_open
format_write = '.txt'


# Opening the CSV Read File and NMEA Write File
with open(path_open+file_open+format_open, mode='r') as csv_file, open(path_write+file_write+format_write, mode='a') as out_file:
    # Python CSV Library to read and access data
    csv_reader = csv.DictReader(csv_file)
    line_count = 0
    # Iteration to manipulate data row by row
    adder = 0
    for row in csv_reader:
        # Getting only raw values for Latitude and Longitude from each row
        finder_lat = re.search("{'lat': '(.*)',",str(row))
        lat_raw = float(finder_lat.group(1))
        finder_lng = re.search(", 'long': '(.*)'}", str(row))
        lng_raw = float(finder_lng.group(1))

        # Converting Decimal Degrees into DGS Format
        lat = deg_to_dms(lat_raw,'lat')
        lng = deg_to_dms(lng_raw,'lon')

        # Fixed values for NMEA String
        nmea_format = '$GPRMC'
        status = 'A'
        utc_raw = 115130.00
        adder += 5     
        utc = format((utc_raw+adder),'.2f') 

        # Generating Pseudo-Random Values to fill the NMEA String fields
        num_sattelites = random.randint(15,22)
        altitude_meters = round(random.uniform(380.0, 420.0), 1)
        altitude_reference_meters = round(random.uniform(40.0,60.0),1)
        speed = round(random.uniform(0.001,0.004),3)
        COG = round(random.uniform(60.00,80.00),2)
        fix_data = '281020'
        mode = 'A'

        # $GPGGA FIELDS
        # utc = datetime.datetime.utcnow()
        # FS = 1
        # HDOP = round(random.uniform(1, 1.5), 2)
        # DGPStation = 0


        raw_string = nmea_format+','+str(utc)+','+status+','+str(lat)+','+str(lng)+','+str(speed)+','+str(COG)+','+fix_data+','+mode+'*'+'00'
        CS = checksum(raw_string)
        print(CS)
        out_file.write(str(CS)+'\n')
        line_count += 1
    print(f'Processed {line_count} lines.')


#### Future improvements ####
### Convert all Files in a directory
# folder_path = sys.argv[1]  <- receive the path via command line
# folder_path = '/home/rperez/Dropbox/01 - PRafael/01 - Dados/01 - ProcessNMEA/00 - CodigoFonte' <- Static path
# Before cicle to open the files, open directory with CSVs Files
# for filename in glob.glob(os.path.join(folder_path, '.htm')):
#
#
# Receive the files to convert via command line
# file_open = sys.argv[1]
# format_open = sys.argv[2]
# format_write = sys.argv[3]
