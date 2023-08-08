// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Calculates bill with tax and tip and split between two.
float half(float bill, float tax, int tip)
{
    float total_after_tax = bill * (tax / 100.0) + bill;
    float total_after_tax_tip = total_after_tax * (tip / 100.00) + total_after_tax;
    return total_after_tax_tip / 2;
}
