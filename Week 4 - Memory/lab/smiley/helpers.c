#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to pink
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            // Checks whether current pixel is black
            if (pixel.rgbtRed == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtBlue == 0x00)
            {
                // Set pixel to pink rgb values
                image[i][j].rgbtRed = 0xFF;
                image[i][j].rgbtGreen = 0xC0;
                image[i][j].rgbtBlue = 0xCB;
            }
        }
    }
}