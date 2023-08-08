#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line argument size is correct
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    char infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    // Check file can
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    char *filenameptr = malloc(8 * sizeof(char));
    int image_total = 0;
    FILE *outptr = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check whether jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file
            if (image_total > 0)
            {
                fclose(outptr);
            }
            // Create new file name
            sprintf(filenameptr, "%03i.jpg", image_total);
            // Open new file to write
            outptr = fopen(filenameptr, "w");
            image_total += 1;
        }

        if (outptr != NULL)
        {
            // write to file
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }
    // Free memory
    free(filenameptr);
    fclose(inptr);
    fclose(outptr);
    return 0;
}