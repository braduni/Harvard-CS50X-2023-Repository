#include <cs50.h>
#include <stdio.h>

int get_height(void);
void create_pyramid(int height);

// Creates a right aligned pyramid of hashes with input height
int main(void)
{
    int height = get_height();
    create_pyramid(height);
}
// Prompt for height input, validates input is integer between 1-8
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    return n;
}
// Prints hashes as right aligned pyramid
void create_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i + j < height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}