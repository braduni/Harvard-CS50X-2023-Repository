#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2) ; j++)
        {
            //Swap pixel horizontally
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int red_total, green_total, blue_total;
    float count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_total = green_total = blue_total = 0;
            count = 0.0;
            // Iterate over 3x3 box around pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check whether height or width is out of bounds
                    if ((i + k) < 0 || (i + k) > (height - 1) || (j + l) < 0 || (j + l) > (width - 1))
                    {
                        continue;
                    }
                    // Increment totals
                    red_total += copy[i + k][j + l].rgbtRed;
                    green_total += copy[i + k][j + l].rgbtGreen;
                    blue_total += copy[i + k][j + l].rgbtBlue;
                    count += 1;
                }
            }
            // Update with average of 3x3 box totals
            image[i][j].rgbtRed = round(red_total / count);
            image[i][j].rgbtGreen = round(green_total / count);
            image[i][j].rgbtBlue = round(blue_total / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Initialise matrix
    int gx_arr[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_arr[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int r, g, b, gx_red, gx_green, gx_blue, gy_red, gy_green, gy_blue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = g = b = gx_red = gx_green = gx_blue = gy_red = gy_green = gy_blue = 0;
            // Iterate over 3x3 box for ith jth pixel
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // Check whether height or width is out of bounds
                    if ((i - 1 + k) < 0 || (i - 1 + k) > height - 1 || (j - 1 + l) < 0 || (j - 1 + l) > width - 1)
                    {
                        continue;
                    }
                    // gx rgb weighted sums totals 3x3 box for ith jth pixel
                    gx_red += copy[i - 1 + k][j - 1 + l].rgbtRed * gx_arr[k][l];
                    gx_green += copy[i - 1 + k][j - 1 + l].rgbtGreen * gx_arr[k][l];
                    gx_blue += copy[i - 1 + k][j - 1 + l].rgbtBlue * gx_arr[k][l];
                    // gy rgb weighted sums totals 3x3 for ith jth pixel
                    gy_red += copy[i - 1 + k][j - 1 + l].rgbtRed * gy_arr[k][l];
                    gy_green += copy[i - 1 + k][j - 1 + l].rgbtGreen * gy_arr[k][l];
                    gy_blue += copy[i - 1 + k][j - 1 + l].rgbtBlue * gy_arr[k][l];
                }
            }
            // square root of gx and gy for each colour channel
            r = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            g = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            b = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));

            // Cap r, g, b max value to 255
            if (r > 255)
            {
                r = 255;
            }

            if (g > 255)
            {
                g = 255;
            }

            if (b > 255)
            {
                b = 255;
            }
            // Set new values
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}