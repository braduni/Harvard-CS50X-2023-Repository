#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *inptr = fopen(argv[1], "r");
    // Check file can be opened
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(header) == 1)
    {
        printf("Unsupported file format.\n");
        return 1;
    }

    // Open output file for writing
    FILE *outptr = fopen(argv[2], "w");

    if (outptr == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);
    BYTE buffer[block_size];

    // Set pointer to end-of-file
    if (fseek(inptr, block_size, SEEK_END))
    {
        printf("fseek failed to set pointer position to end-of-%s.\n", argv[2]);
        return 1;
    }
    // Iterates from end of file to header
    while ((ftell(inptr) - block_size) > sizeof(header))
    {
        // Pointer is offset -2 block-sizes from current position
        if (fseek(inptr, - 2 * block_size, SEEK_CUR))
        {
            printf("fseek failed to set new pointer position.\n");
            return 1;
        }

        // Read and write
        fread(&buffer, block_size, 1, inptr);
        fwrite(&buffer, block_size, 1, outptr);
    }
    fclose(outptr);
    fclose(inptr);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return (header.bitsPerSample / 8) * header.numChannels;
}