#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void compress(char *data, int count, FILE *outfile);
void decompress(char *data, int count, FILE *outfile);
char *readFileData(char *filename, int *count_ptr);
int main(int num_args, char *arg_values[])
{
    if (num_args != 2)
    {
        printf("Usage: rle filename (produces filename.rle)\n");
        printf(" rle filename.rle (produces filename.plain)\n");
        exit(1);
    }
    char *input_filename = arg_values[1];
    // read the file data into an array
    int count;
    char *data = readFileData(input_filename, &count);
    // Call compress() or decompress().
    FILE *outfile;
    int len = strlen(input_filename);
    if (len < 4 || strcmp(input_filename + (len - 4), ".rle") != 0)
    {
        char output_filename[80];
        strcpy(output_filename, input_filename);
        strcat(output_filename, ".rle");
        printf("Compressing %s to %s\n", input_filename, output_filename);
        outfile = fopen(output_filename, "wb");
        compress(data, count, outfile);
    }
    else
    {
        char output_filename[80];
        strncpy(output_filename, input_filename, len - 4);
        output_filename[len - 4] = 0;
        strcat(output_filename, ".plain");
        printf("Decompressing %s to %s\n", input_filename, output_filename);
        outfile = fopen(output_filename, "wb");
        decompress(data, count, outfile);
    }
    // Close the output file to ensure data is saved.
    fclose(outfile);
    // Free the array we allocated
    delete data;
    return 0;
}
void compress(char *data, int count, FILE *outfile)
{
    // TODO: compress the data instead of just writing it out to the file
    for (int i = 0; i < count; ++i)
    {
        putc(data[i], outfile); // write out a single byte of data
    }
}
void decompress(char *data, int count, FILE *outfile)
{

    // TODO: decompress the data instead of just writing it out to the file
    for (int i = 0; i < count; ++i)
    {
        putc(data[i], outfile); // write out a single byte of data
    }
}
char *readFileData(char *filename, int *count_ptr)
{
    // Returns a pointer to an array storing the file data.
    // Sets the variable pointed to by 'count' to contain the file size.
    // Exits the program if the filename doesn't exist.
    FILE *infile = fopen(filename, "rb");
    if (!infile)
    {
        printf("No such file \"%s\"!\n", filename);
        exit(1);
    }
    // Get file size by going to the end of the file, getting the
    // position, and then going back to the start of the file.
    fseek(infile, 0, SEEK_END);
    int count = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    // read the data from the file
    char *data = new char[count];
    fread(data, 1, count, infile);
    fclose(infile);
    *count_ptr = count;
    return data;
}