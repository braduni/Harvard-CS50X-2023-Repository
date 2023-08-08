#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_grade_level(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int grade_level = get_grade_level(count_letters(text), count_words(text), count_sentences(text));

    if (grade_level > 15)
    {
        printf("Grade 16+\n");
    }
    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}
// Returns total of letters from input text
int count_letters(string text)
{
    int total = 0;
    // Checks if current char in loop is alphabetical and increments total
    for (int i = 0; i < strlen(text); i++)
    {
        char ch = text[i];
        if (isalpha(ch))
        {
            total++;
        }
    }
    return total;
}
//Todo attempt a solution that will tolerate multiple spaces between words or indeed, no words!
int count_words(string text)
{
    int total = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        char ch = text[i];
        if (isblank(ch))
        {
            total++;
        }
    }
    return total;
}
// Returns total amount of sentences from input text
int count_sentences(string text)
{
    int total = 0;
    // Checks whether the char in text of position i ascii value is the same as ! or ? or . ascii value
    for (int i = 0; i < strlen(text); i++)
    {
        int ch = text[i];
        if (ch == '!' || ch == '.' || ch == '?')
        {
            total++;
        }
    }
    return total;
}
// Calculates grade level using Coleman-Liau index formula
int get_grade_level(int letters, int words, int sentences)
{
    // Calculates average number of letters per 100 words
    float letter_avg = (float) letters / words * 100;
    // Calculates average number of sentences per 100 words
    float sentence_avg = (float)  sentences / words * 100;
    // Calculates index using Coleman-Liau index formula
    float index = 0.0588 * letter_avg - 0.296 * sentence_avg - 15.8;
    // Return index rounded
    return round(index);
}