#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average value from current pixel rgb and apply
            float avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE original = image[i][j];
            // Convert pixel rgb using to sepia formula
            float sepiaRed = round(.393 * original.rgbtRed + .769 * original.rgbtGreen + .189 * original.rgbtBlue);
            float sepiaGreen = round(.349 * original.rgbtRed + .686 * original.rgbtGreen + .168 * original.rgbtBlue);
            float sepiaBlue = round(.272 * original.rgbtRed + .534 * original.rgbtGreen + .131 * original.rgbtBlue);
            // Check value within range or sets to max range
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image.
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    float total_red;
    float total_blue;
    float total_green;
    int count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            total_red = total_blue = total_green = count = 0;
            // 3x3 box
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check width or height not out of bounds
                    if ((i + k) < 0 || (i + k) > (height - 1) || (j + l) < 0 || (j + l) > (width - 1))
                    {
                        continue;
                    }
                    // add the rgb values of pixel to totals
                    total_red += copy[i + k][j + l].rgbtRed;
                    total_green += copy[i + k][j + l].rgbtGreen;
                    total_blue += copy[i + k][j + l].rgbtBlue;
                    count += 1;
                }
            }
            // add avg to pixel
            image[i][j].rgbtRed = round(total_red / count);
            image[i][j].rgbtBlue = round(total_blue / count);
            image[i][j].rgbtGreen = round(total_green / count);
        }
    }
    return;
}