#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}
// 48 is '0' ascii value
int convert(string input)
{
    int len = strlen(input);
    // base case
    if (len == 1)
    {
        return input[0] - 48;
    }

    char last_char = input[len - 1];
    int converted_char = last_char - 48;
    input[len - 1] = '\0';
    return converted_char + 10 * convert(input);
}