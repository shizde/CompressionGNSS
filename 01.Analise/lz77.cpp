#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

//#define LOOKAHEAD_SIZE 4
//#define SEARCH_SIZE 6

#define LOOKAHEAD_SIZE 16
#define SEARCH_SIZE 12


inline int filesize(std::ifstream&);
struct Triplet chooseBest(std::vector<Triplet>&);
inline void transfer(std::vector<char>&, uint8_t, char);
inline void writeTriplet(struct Triplet, std::vector<char>&);
std::vector<char> encode(char*&, int&);


struct Triplet {
    int offset;
    int length;
    char token;
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }

    std::ifstream input{argv[1], std::ios_base::binary};
    assert(input.is_open());

    int size = filesize(input);
    char* array = {new char[size]};
    input.read(array, size);
    input.close();



    std::ofstream output{std::string(argv[1]) + ".lz77", std::ios_base::binary};
    assert(output.is_open());

    std::vector<char> result = encode(array, size);
    output.write(result.data(), result.size());
    output.close();

    delete[] array;
    std::cout << "Previous size: " << size << " ";
    std::cout << "Compressed size: " << result.size() << "\n";
    std::cout << "Results saved to ./" << argv[1] << ".lz77" << "\n";
    return 0;
}


std::vector<char> encode(char* &array, int &size) {
    std::vector<char> search;
    search.reserve(SEARCH_SIZE);

    std::vector<char> look;
    look.reserve(LOOKAHEAD_SIZE+150);

    std::vector<Triplet> paths;
    std::vector<char> output;

    int x = 0;
    while (x < size) {
        look.push_back(array[x]);
        x++;

        if (look.size() == LOOKAHEAD_SIZE) {
             std::vector<char>::iterator l_it = look.begin(); 
             int offset = 0;
             int length = 0;
             for (auto s_it = search.begin(); s_it < search.end(); s_it++) {

                 if (*s_it == *l_it) {
                     if (!offset)
                         offset = std::distance(s_it, search.end());
                     l_it++;
                     length++;

                     if (length >= int(look.size()-1))
                         break;

                 } else {
                     if (offset)
                         paths.push_back(Triplet{offset, length, *l_it});
                     length = 0;
                     offset = 0;
                 }

             }

             /*  above for loop will find all possible triplets for a given token
             *  (unlike in real life where we can visually process the best path)
             *  we need to collect all in a vector and filter based on length.
             *  largest length = best compression */

             if (offset)  //a match is found, but reached the end of the vector
                 paths.push_back(Triplet{offset, length, *l_it}); 
             else if (paths.empty())  //no match was found in the dictionary
                 paths.push_back(Triplet{0, 0, *l_it});


             Triplet ideal = chooseBest(paths);
             writeTriplet(ideal, output);
             
             /* safely transfer the read data from lookahead buffer
              * into search buffer */

             for (auto x = ideal.length + 1; x > 0; x--) {
                 transfer(search, SEARCH_SIZE, look.at(0));
                 look.erase(look.begin());
             }

             while (!paths.empty())
                 paths.erase(paths.begin());
        }
    }
    // sometimes, depending on lookahead & search buffer sizes, the last n-bytes
    // of a file are not fully compressed. So something needs to be written here
    // for that.



    return output;
}

inline int filesize(std::ifstream &file) {
    file.seekg(std::ios::beg, std::ios::end);
    int size = file.tellg();
    file.seekg(0);
    return size;
}

inline void writeTriplet(struct Triplet in, std::vector<char> &out) {
    out.push_back(in.offset);
    out.push_back(in.length);
    out.push_back(in.token);
}

inline void transfer(std::vector<char> &target, const uint8_t limit, char token) {
    if (target.size() == limit)
        target.erase(target.begin());

    target.push_back(token);
}

struct Triplet chooseBest(std::vector<Triplet> &buffer) {
    int max = 0;
    int bestoffset = 0;
    for (auto it = buffer.begin(); it < buffer.end(); it++) {
        //prioritize a great length first and then smallest offset
        if (!bestoffset)
            bestoffset = it->offset;

        if (it->length > max) {
            max = it->length;
        } else if (it->offset < bestoffset && it->length == max) {
            bestoffset = it->offset;
        } else {
            buffer.erase(it);
        }

    }
    return buffer[0];
}
