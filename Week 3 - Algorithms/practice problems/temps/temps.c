// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void selection_sort_cities(void);
void bubble_sort_cities(void);
void insertion_sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    bubble_sort_cities();
    //insertion_sort_cities();
    //selection_sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}
void bubble_sort_cities(void)
{
    avg_temp t;
    int n = NUM_CITIES - 1;
    int swapped = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                t = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = t;
                swapped = 1;
            }
        }
        // no swaps means array is already sorted
        if (swapped == 0)
        {
            break;
        }
    }
}

void selection_sort_cities(void)
{
    avg_temp t;

    for (int i = 0; i < NUM_CITIES; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            if (temps[min_index].temp < temps[j].temp)
            {
                min_index = j;
            }
        }

        t = temps[min_index];
        temps[min_index] = temps[i];
        temps[i] = t;
    }
}

void insertion_sort_cities(void)
{
    for (int i = 1; i < NUM_CITIES; i++)
    {
        avg_temp key = temps[i];
        int j = i - 1;

        while (key.temp > temps[j].temp && j >= 0)
        {
            temps[j + 1] = temps[j];
            j--;
        }
        temps[j + 1] = key;
    }
}