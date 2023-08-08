#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_letters(string input);
bool unique_characters(string input);
void ciphertext(string text, string key);

int main(int argc, string argv[])
{
    // Checks correct amount of command-line argument are passed
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key_input = argv[1];

    // Checks key input length is 26 and promps user appropriately
    if (strlen(key_input) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Checks key input is alphabetical characters and promps user appropriately
    if (only_letters(key_input) == false)
    {
        printf("Key must contain only alphabetical characters.\n");
        return 1;
    }

    // Checks key input is all unique characters and promps user appropriately
    if (unique_characters(key_input) == false)
    {
        printf("Key must contain unique alphabetical characters.\n");
        return 1;
    }

    string plain_text = get_string("plaintext:  ");
    printf("ciphertext: ");
    ciphertext(plain_text, key_input);
    printf("\n");
    return 0;
}
// Checks whether each char in input passed is alphabetical
bool only_letters(string input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(input[i]) == false)
        {
            return false;
        }
    }
    return true;
}
// Checks whether char in input is unique
bool unique_characters(string input)
{
    int len = strlen(input);
    // Iterates through every postion after i to see whether any value matches current value
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (tolower(input[i]) == tolower(input[j]))
            {
                return false;
            }
        }
    }
    return true;
}

// Prints cipher equivalent for each char in text using key
void ciphertext(string text, string key)
{
    int len = strlen(text);
    // Checks if current char is lower or uppercase and removes ascii value of 'a' or 'A' from char to get correct position in key
    for (int i = 0; i < len; i++)
    {
        int ch = text[i];
        if (isalpha(ch) && islower(ch))
        {
            printf("%c", tolower(key[ch - 97]));
        }
        else if (isalpha(ch) && isupper(ch))
        {
            printf("%c", toupper(key[ch - 65]));
        }
        else
        {
            printf("%c", ch);

        }
    }
}