#include <cs50.h>
#include <stdio.h>

int get_height();
void create_pyramid(int height);
// Draw a pyramid in mario to a specified height using hashes for bricks
int main(void)
{
    int height = get_height();
    create_pyramid(height);
}

// Prompt for height input, validates input is integer between 1-8
int get_height()
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
// Prints two adjacent pyramid with gap inbetween
void create_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height + i + 3; j++)
        {
            if (i + j < height - 1 || j == height || j == height + 1)
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