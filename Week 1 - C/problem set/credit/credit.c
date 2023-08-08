#include <cs50.h>
#include <stdio.h>

long get_card_number();
bool valid_length(long num);
bool checksum(long num);
void print_card_type(long num);

int main(void)
{
    long card_number = get_card_number();

    if (valid_length(card_number) && checksum(card_number))
    {
        print_card_type(card_number);
        return 0;
    }
    printf("INVALID\n");
}

//Prompt user for card number. No input validation
long get_card_number()
{
    long num;
    do
    {
        num = get_long("Number: ");
    }
    while (num < 0);

    return num;
}

bool valid_length(long num)
{
    int n = 1;
    while (num > 9)
    {
        num = num / 10;
        n++;
    }

    if (n == 13 || n == 15 || n == 16)
    {
        return true;
    }
    return false;
}

void print_card_type(long num)
{
    string amex = "AMEX\n";
    string mastercard = "MASTERCARD\n";
    string visa = "VISA\n";

    // store last 2 digits of card number
    long c = num;
    // reduces card number to first two digits.
    do
    {
        c = c / 10;
    }
    while (c > 100);

    if (c == 34 || c == 37)
    {
        printf("%s", amex);
    }
    else if (c >= 40 && c <= 49)
    {
        printf("%s", visa);
    }
    else if (c >= 51 && c <= 55)
    {
        printf("%s", mastercard);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Validates card using Luhn’s algorithm
// Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
// Add the sum to the sum of the digits that weren’t multiplied by 2
// If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid
bool checksum(long num)
{
    int cur;
    int cur2;
    int sum1 = 0;
    int sum2 = 0;
    int prod1;
    int prod2;
    int total = 0;

    do
    {
        // sum 1
        // Current last digit
        cur = num % 10;
        //Removes last digit from num
        num = num / 10;
        // Gets total
        sum1 = sum1 + cur;

        //sum 2
        cur2 = num % 10;
        num = num / 10;
        cur2 = cur2 * 2;
        // seperate product digits
        prod1 = cur2 % 10;
        prod2 = cur2 / 10;
        // total
        sum2 = sum2 + prod1 + prod2;
    }
    while (num > 0);

    total = sum1 + sum2;

    if (total % 10 == 0)
    {
        return true;
    }
    return false;
}