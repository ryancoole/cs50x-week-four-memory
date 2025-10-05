#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// WAV header size in bytes
const int HEADER_SIZE = 44;

// Each audio sample is a 16-bit signed integer
const int SAMPLE_SIZE = sizeof(int16_t);

// Function prototypes
void copy_header(FILE *input, FILE *output);
void process_samples(FILE *input, FILE *output, float factor);

int main(int argc, char *argv[])
{
    // Ensure correct usage: program requires 3 arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input); // close input before exiting
        return 1;
    }

    // Convert third argument (factor) from string to float
    float factor = atof(argv[3]);

    // Copy WAV header from input to output
    copy_header(input, output);

    // Process audio samples and scale them by the factor
    process_samples(input, output, factor);

    // Close both files
    fclose(input);
    fclose(output);

    return 0;
}

// Function to copy the 44-byte WAV header
void copy_header(FILE *input, FILE *output)
{
    uint8_t header[HEADER_SIZE];

    // Read header from input file
    if (fread(header, HEADER_SIZE, 1, input) != 1)
    {
        printf("Error reading header.\n");
        exit(1);
    }

    // Write header to output file
    if (fwrite(header, HEADER_SIZE, 1, output) != 1)
    {
        printf("Error writing header.\n");
        exit(1);
    }
}

// Function to process and scale audio samples
void process_samples(FILE *input, FILE *output, float factor)
{
    int16_t buffer; // holds each audio sample

    // Read samples one by one until end of file
    while (fread(&buffer, SAMPLE_SIZE, 1, input) == 1)
    {
        // Use a larger type for scaling to avoid overflow
        int32_t temp = buffer * factor;

        // Clamp values to valid int16_t range
        if (temp > INT16_MAX)
            temp = INT16_MAX;
        if (temp < INT16_MIN)
            temp = INT16_MIN;

        // Store clamped result back into buffer
        buffer = (int16_t) temp;

        // Write updated sample to output file
        if (fwrite(&buffer, SAMPLE_SIZE, 1, output) != 1)
        {
            printf("Error writing sample.\n");
            exit(1);
        }
    }
}
