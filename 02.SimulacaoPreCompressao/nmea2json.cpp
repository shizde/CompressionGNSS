#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <cstring>
#include <sstream>

#define OPEN_FILE "NMEA2JSON.txt"

#define FILENAME "NMEA2JSON"

void print_vector(std::vector<std::string> print_vector){
    for (size_t i = 0; i < print_vector.size(); i++)
    {
        std::cout << print_vector[i] << std::endl;
    }
};

void create_json(std::vector<std::string> vector_timestamp,
                 std::int_fast16_t number_of_samples,
                 std::int_fast16_t FX,
                 std::vector<std::string> vector_position_latitude,
                 std::vector<std::string> vector_degrees_latitude,
                 std::vector<std::string> vector_minutes_latitude,
                 std::vector<std::string> vector_seconds_latitude,
                 std::vector<std::string> vector_position_longitude,
                 std::vector<std::string> vector_degrees_longitude,
                 std::vector<std::string> vector_minutes_longitude,
                 std::vector<std::string> vector_seconds_longitude)
{
    //VERIFICAR A POSIÇÃO GLOBAL DAS COORDENADAS PARA FX
    int PL = 2;
    int PN = 2;
    int counterNorth = 0;
    int counterSouth = 0;
    int counterWest = 0;
    int counterEast = 0;
    std::vector<std::int_fast16_t> vectorPL;
    std::vector<std::int_fast16_t> vectorPN;

    for (size_t i = 0; i < vector_position_latitude.size(); i++)
    {
        if (vector_position_latitude[i] == "N")
        {
            PL = 0;
            vectorPL.push_back(PL);
            counterNorth++;
        } 
        else if (vector_position_latitude[i] == "S")
        {
            PL = 1;
            vectorPL.push_back(PL);
            counterSouth++;
        } 
        else
        {
            std::cout << "Bad GPS Format. Latitude reference not valid on row <" << i << "> of file." << std::endl;
            break;
        }
        
    }

    for (size_t i = 0; i < vector_position_longitude.size(); i++)
    {
        if (vector_position_longitude[i] == "W")
        {
            PN = 0;
            vectorPN.push_back(PN);
            counterWest++;
        }
        else if (vector_position_longitude[i] == "E")
        {
            PN = 1;
            vectorPN.push_back(PN);
            counterEast++;
        }
        else
        {
            std::cout << "Bad GPS Format. Longitude reference not valid on row <" << i << "> of file." << std::endl;
            break;
        }
    }

    // CRIAR JSON

    std::fstream json_file;
    json_file.open(FILENAME, std::ios::out);
    if (!json_file)
    {
        std::cout << "Error during JSON creation." << std::endl;
    }
    else
    {
        std::cout << "JSON File created." << std::endl;
        json_file << "coords = {" << std::endl;
        json_file << "\t\"TS\": ";
        json_file << vector_timestamp[0] << "," << std::endl;
        json_file << "\t\"NS\": ";
        json_file << number_of_samples << "," << std::endl;
        json_file << "\t\"FX\": ";
        json_file << FX << "," << std::endl;
        // GENERATING LATITUDE
        json_file << "\t\"lat\": {" << std::endl;
        // POSITION
        json_file << "\t\t\"PL\":";
        if (counterNorth == number_of_samples || counterSouth == number_of_samples)
        {
            json_file << PL << "," << std::endl;
        } 
        else {
            json_file << "[";
            for (size_t i = 0; i < vectorPL.size(); i++)
            {
                json_file << vectorPL[i];
                if (i != vectorPL.size() - 1)
                {
                    json_file << ",";
                }
            }
            json_file << "]," << std::endl;
        }
        
        // DEGREES
        json_file << "\t\t\"DL\":[";
        for (size_t i = 0; i < vector_degrees_latitude.size(); i++)
        {
            json_file << vector_degrees_latitude[i];
            if (i != vector_degrees_latitude.size() - 1)
            {
                json_file << ",";
            }
            
        }
        json_file << "]," << std::endl;
        // MINUTES
        json_file << "\t\t\"ML\":[";
        for (size_t i = 0; i < vector_minutes_latitude.size(); i++)
        {
            json_file << vector_minutes_latitude[i];
            if (i != vector_minutes_latitude.size() - 1)
            {
                json_file << ",";
            }
        }
        json_file << "]," << std::endl;
        // SECONDS
        json_file << "\t\t\"SL\":[";
        for (size_t i = 0; i < vector_seconds_latitude.size(); i++)
        {
            json_file << vector_seconds_latitude[i];
            if (i != vector_seconds_latitude.size() - 1)
            {
                json_file << ",";
            }
        }
        json_file << "]" << std::endl;
        json_file << "\t}," << std::endl;
        // GENERATING LONGITUDE
        json_file << "\t\"lng\": {" << std::endl;
        // POSITION
        json_file << "\t\t\"PN\":";
        if (counterWest == number_of_samples || counterEast == number_of_samples)
        {
            json_file << PL << "," << std::endl;
        }
        else
        {
            json_file << "[";
            for (size_t i = 0; i < vectorPN.size(); i++)
            {
                json_file << vectorPN[i];
                if (i != vectorPN.size() - 1)
                {
                    json_file << ",";
                }
            }
            json_file << "]," << std::endl;
        }

        // DEGREES
        json_file << "\t\t\"DN\":[";
        for (size_t i = 0; i < vector_degrees_longitude.size(); i++)
        {
            json_file << vector_degrees_longitude[i];
            if (i != vector_degrees_longitude.size() - 1)
            {
                json_file << ",";
            }
        }
        json_file << "]," << std::endl;
        // MINUTES
        json_file << "\t\t\"MN\":[";
        for (size_t i = 0; i < vector_minutes_longitude.size(); i++)
        {
            json_file << vector_minutes_longitude[i];
            if (i != vector_minutes_longitude.size() - 1)
            {
                json_file << ",";
            }
        }
        json_file << "]," << std::endl;
        // SECONDS
        json_file << "\t\t\"SN\":[";
        for (size_t i = 0; i < vector_seconds_longitude.size(); i++)
        {
            json_file << vector_seconds_longitude[i];
            if (i != vector_seconds_longitude.size() - 1)
            {
                json_file << ",";
            }
        }
        json_file << "]" << std::endl;
        json_file << "\t\t}" << std::endl;
        json_file << "}" <<std::endl;
        json_file.close();
    }
};

void compress_huffman(){
    system("./archive NMEAteste.json");   
}

void compress_lzwv5(){
    system("./lzwv5 -c NMEAteste.json NMEAteste.lzw");
}

void decompress_huffman(){
    system("./extract coords.json.compressed");
}

void decompress_lzwv5(){
    system("./lzwv5 -d NMEAteste.lzw NMEAteste2.json");
}

std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void analyze(){
    std::string huffman_name;
    std::string lzw_name;
    huffman_name.append(FILENAME);
    huffman_name.append(".json.compressed");
    lzw_name.append(FILENAME);
    lzw_name.append(".lzw")
    std::cout << filesize("json_writer.h") << std::endl;
    std::fstream result_file;
    result_file.open(FILENAME, std::ios::out);
    result_file << "Compression Analisys" << std::endl;
    result_file << "\n--------------------\n\n" << std::endl;
    result_file << "Original File: " << FILENAME << std::endl;
    result_file << "Size: " << filesize(FILENAME) << std::endl;
    result_file << "--------------------" << std::endl;
    result_file << "Compressions" << std::endl;
    result_file << "--------------------" << std::endl;
    result_file << "Huffman Algorithm" << std::endl;
    result_file << "Size: " << filesize(huffman_name) << " MB" << std::endl;
    result_file << "Lempel-Ziv-Wielch Algorithm" << std::endl;
    result_file << "Size: " << filesize(lzw_name) << " MB" << std::endl;

}
int main(){
    // Counters for FX Parameter
    int counterFxDegreeLat = -1, counterFxMinuteLat = -1, counterFxDegreeLng = -1, counterFxMinuteLng = -1;
    int FX;

    // Opening SimData File
    std::ifstream ip(OPEN_FILE);
    //std::ifstream ip("NMEAmD_30pts_ZigZag2.txt");

    //if(!ip.is_open()) std::cout << "Error: File Open" << "\n";

    int numSamples = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // READ SIMDATA VARIABLES
    std::string line;
    std::string read_type_nmea;
    std::string read_timestamp;
    std::string read_a;
    std::string read_latitude;
    std::string read_latitude_reference;
    std::string read_longitude;
    std::string read_longitude_reference;
    std::string read_deslocation;
    std::string read_speed;
    std::string read_date;
    std::string read_a2;
    std::string read_checksum;
    std::string degrees_latitude;
    std::string minutes_latitude;
    std::string seconds_latitude;
    std::string degrees_longitude;
    std::string minutes_longitude;
    std::string seconds_longitude;
    std::string fxDegreeLat = "70";
    std::string fxMinuteLat = "70";
    std::string fxDegreeLng = "70";
    std::string fxMinuteLng = "70";
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    // VECTORS FOR JSON STRUCTURE
    std::vector<std::string> vector_timestamp;
    std::vector<std::string> vector_position_latitude;
    std::vector<std::string> vector_degrees_latitude;
    std::vector<std::string> vector_minutes_latitude;
    std::vector<std::string> vector_seconds_latitude;
    std::vector<std::string> vector_position_longitude;
    std::vector<std::string> vector_degrees_longitude;
    std::vector<std::string> vector_minutes_longitude;
    std::vector<std::string> vector_seconds_longitude;
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    while(getline(ip,line)){
        std::stringstream s_stream(line);
           // READ AND GET DATA FROM EACH STRING
        std::getline(s_stream, read_type_nmea, ',');
        std::getline(s_stream, read_timestamp, ',');
        std::getline(s_stream, read_a, ',');
        std::getline(s_stream, read_latitude, ',');
        std::getline(s_stream, read_latitude_reference, ',');
        std::getline(s_stream, read_longitude, ',');
        std::getline(s_stream, read_longitude_reference, ',');
        std::getline(s_stream, read_deslocation, ',');
        std::getline(s_stream, read_speed, ',');
        std::getline(s_stream, read_date, ',');
        std::getline(s_stream, read_a2, ',');
        std::getline(s_stream, read_checksum, '\n');

        // PARSE GPS DATA 
        degrees_latitude = read_latitude.substr(0,2);
        minutes_latitude = read_latitude.substr(2,2);
        seconds_latitude = read_latitude.substr(5,4);
        degrees_longitude = read_longitude.substr(0,2);
        minutes_longitude = read_longitude.substr(2,2);
        seconds_longitude = read_longitude.substr(5,4);

        // CHECK DEGREES AND MINUTES IN ORDER TO DEFINE FX PARAMETER
        if (degrees_latitude != fxDegreeLat)
        {
            counterFxDegreeLat++;
            fxDegreeLat = degrees_latitude;
        }
        if (minutes_latitude != fxMinuteLat)
        {
            counterFxMinuteLat++;
            fxMinuteLat = minutes_latitude;
        }
        if (degrees_longitude != fxDegreeLng)
        {
            counterFxDegreeLng++;
            fxDegreeLng = degrees_longitude;
        }
        if (minutes_longitude != fxMinuteLng)
        {
            counterFxMinuteLng++;
            fxMinuteLng = minutes_longitude;
        }

        // ADDING DATA TO JSON VECTORS
        vector_timestamp.push_back(read_timestamp);
        vector_position_latitude.push_back(read_latitude_reference);
        vector_degrees_latitude.push_back(degrees_latitude);
        vector_minutes_latitude.push_back(minutes_latitude);
        vector_seconds_latitude.push_back(seconds_latitude);
        vector_position_longitude.push_back(read_longitude_reference);
        vector_degrees_longitude.push_back(degrees_longitude);
        vector_minutes_longitude.push_back(minutes_longitude);
        vector_seconds_longitude.push_back(seconds_longitude);

        // KEEP TRACK OF NUMBER OF SAMPLES ANALYZED
        numSamples++;
    }
    // DEFINING FX PARAMETER
    if (counterFxDegreeLat == 0 && counterFxDegreeLng == 0)
    {
        if (counterFxMinuteLat == 0 && counterFxMinuteLng == 0)
        {
            FX = 2;
            vector_degrees_latitude.clear();
            vector_degrees_latitude.push_back(degrees_latitude);
            vector_degrees_longitude.clear();
            vector_degrees_longitude.push_back(degrees_longitude);
            vector_minutes_latitude.clear();
            vector_minutes_latitude.push_back(minutes_latitude);
            vector_minutes_longitude.clear();
            vector_minutes_longitude.push_back(minutes_longitude);
        }
        else
        {
            FX = 1;
            vector_degrees_latitude.clear();
            vector_degrees_latitude.push_back(degrees_latitude);
            vector_degrees_longitude.clear();
            vector_degrees_longitude.push_back(degrees_longitude);
        }
    }
    else
    {
        FX = 0;
    }
    ip.close();
    //print_vector(vector_position_latitude);

    // CREATING JSON FILE
    create_json(vector_timestamp,numSamples, FX,
                vector_position_latitude,vector_degrees_latitude,vector_minutes_latitude,vector_seconds_latitude,
                vector_position_longitude,vector_degrees_longitude,vector_minutes_longitude,vector_seconds_longitude);

    // std::cout << "------- Huffman Compression ------- " << std::endl;
    // compress_huffman();
    // std::cout << "-----------------------------------" << std::endl;
    // std::cout << "-- Lempel-Ziv-Wielch Compression --" << std::endl;
    // compress_lzwv5();
    // std::cout << "-----------------------------------" << std::endl;
    //decompress_huffman();
    //decompress_lzwv5();

}
