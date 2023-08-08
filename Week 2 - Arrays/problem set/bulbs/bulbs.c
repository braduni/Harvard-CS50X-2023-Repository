#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void update_array(int value, int *binary);

int main(void)
{
    string input = get_string("Message: ");
    int len = strlen(input);
    int array[BITS_IN_BYTE];
    for (int i = 0; i < len; i++)
    {
        update_array(input[i], array);
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(array[j]);
        }
        printf("\n");
    }
}
// Changes array that pointer is passed to binary value of int passed
void update_array(int value, int *array)
{
    int remainder;
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        remainder = value % 2;
        // appends value back to front
        array[(BITS_IN_BYTE - 1) - i] = remainder;
        value = value / 2;
    }
}
// Prints bit value
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}