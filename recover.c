#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512 // Each block on the memory card is 512 bytes
typedef uint8_t BYTE;  // BYTE = unsigned 8-bit integer (1 byte)

int main(int argc, char *argv[])
{
    // Ensure correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the memory card file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE]; // Temporary storage for each 512-byte block
    FILE *outptr = NULL;     // Pointer for output JPEG file
    char filename[8];        // Storage for "###.jpg" filenames
    int file_count = 0;      // JPEG counter
    int found_jpg = 0;       // Flag: have we started writing JPEGs?

    // Read 512 bytes at a time from the memory card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check if the block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If we were already writing a JPEG, close the previous one
            if (found_jpg)
            {
                fclose(outptr);
            }
            else
            {
                found_jpg = 1; // First JPEG found
            }

            // Create a new filename and open new output file
            sprintf(filename, "%03i.jpg", file_count);
            outptr = fopen(filename, "w");
            file_count++;
        }

        // If we’re currently writing to a JPEG, keep writing
        if (found_jpg)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    // Close any remaining open file and input file
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);

    return 0;
}
