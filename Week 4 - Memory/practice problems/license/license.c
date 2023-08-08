#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers (array of pointers)
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // set ith pointer to memory allocation
        plates[idx] = malloc(7 * sizeof(char));

        if (plates[idx] == NULL)
        {
            return 2;
        }
        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }
    // close file
    fclose(infile);
    // print plates ith value and frees dynamic memory allocated
    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }
}
