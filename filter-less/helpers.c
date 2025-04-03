#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg;

            image[i][j].rgbtGreen = avg;

            image[i][j].rgbtBlue = avg;
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
            int red_value = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                  .189 * image[i][j].rgbtBlue);
            int green_value = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                    .168 * image[i][j].rgbtBlue);
            int blue_value = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                   .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = red_value;

            image[i][j].rgbtGreen = green_value;

            image[i][j].rgbtBlue = blue_value;
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
            RGBTRIPLE temp[height][width];
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
