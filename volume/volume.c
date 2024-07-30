// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");  // Open input file in binary mode
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");  // Open output file in binary mode
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input);  // Close input file if output file cannot be opened
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t buffer_data[HEADER_SIZE];
    fread(buffer_data, HEADER_SIZE, 1, input);  // Read header from input
    fwrite(buffer_data, HEADER_SIZE, 1, output);  // Write header to output

    // Read samples from input file, modify volume, and write updated data to output file
    int16_t buffer_data_sample;
    while (fread(&buffer_data_sample, sizeof(int16_t), 1, input) == 1)
    {
        buffer_data_sample *= factor;  // Modify sample based on volume factor
        fwrite(&buffer_data_sample, sizeof(int16_t), 1, output);  // Write modified sample to output
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
