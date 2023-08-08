#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string input);
char rotate(char ch, int key);

int main(int argc, string argv[])
{
    // Checks there's 1 command line argument entered.
    if (argc != 2)
    {
        printf("1 command-line argument required.\n");
        return 1;
    }
    // Checks argument passed is decimal digits
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plain_text = get_string("plaintext:  ");
    int len = strlen(plain_text);
    // Converts string to int
    int key = atoi(argv[1]);

    printf("ciphertext: ");

    for (int i = 0; i < len; i++)
    {
        printf("%c", rotate(plain_text[i], key));
    }
    printf("\n");
    return 0;
}
// Checks whether each char is a decimal digit i.e Ascii value of current char is between 48 and 57
bool only_digits(string input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            return false;
        }
    }
    return true;
}
// Rotates the passed char ch by int key amount of positions if its alphabetical wrapping around from z-a or Z-A
// Returns non-alphabetical characters unchanged
char rotate(char ch, int key)
{
    // Sets appropriate value for lowercase and uppercase characters
    int case_val = (islower(ch)) ? 97 : 65;

    // Removes ascii value of 'A' or 'a' from ch, increments ch by key amount, remainder ch after modulus 26 is incremented by case-val
    if (isalpha(ch))
    {
        return ((((ch - case_val) + key) % 26) + case_val);
    }
    return ch;
}