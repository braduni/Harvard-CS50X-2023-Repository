// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// Return max value in array
int max(int array[], int n)
{
    int max = array[0];
    for (int i = 0; i < n - 1; i++)
    {
        if (max < array[i + 1])
        {
            max = array[i + 1];
        }
    }
    return max;
}
