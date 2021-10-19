#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            BYTE average = round ((float)(image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3);
            image[y][x].rgbtBlue = average;
            image[y][x].rgbtGreen = average;
            image[y][x].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE tmp;

            tmp.rgbtBlue = image[y][x].rgbtBlue;
            tmp.rgbtGreen = image[y][x].rgbtGreen;
            tmp.rgbtRed = image[y][x].rgbtRed;

            image[y][x].rgbtBlue = image[y][width - x - 1].rgbtBlue;
            image[y][x].rgbtGreen = image[y][width - x - 1].rgbtGreen;
            image[y][x].rgbtRed = image[y][width - x - 1].rgbtRed;

            image[y][width - x - 1].rgbtBlue = tmp.rgbtBlue;
            image[y][width - x - 1].rgbtGreen = tmp.rgbtGreen;
            image[y][width - x - 1].rgbtRed = tmp.rgbtRed;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
