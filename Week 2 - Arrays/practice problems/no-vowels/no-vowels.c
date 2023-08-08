// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

char *replace(char *input);

int main(int argc, string argv[])
{
    string result = replace(argv[1]);
    printf("%s\n", result);
}

char * replace(char * input)
{
    static char output[100] = "";

    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        char ch = input[i];
        switch (ch)
        {
            case 'a':
                strcat(output, "6");
                break;
            case 'e':
                strcat(output, "3");
                break;
            case 'i':
                strcat(output, "1");
                break;
            case 'o':
                strncat(output, "0", 1);
                break;
            default:
                strncat(output, &ch, 1);
                break;
        }
    }
    return output;
}