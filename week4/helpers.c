#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            float sum;
            sum = pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue;
            int avg = round(sum / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
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
            RGBTRIPLE tmp;
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate average value
            int r = 0, g = 0, b = 0;
            int cnt = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di < height && j + dj >= 0 && j + dj < width)
                    {
                        r += image[i + di][j + dj].rgbtRed;
                        g += image[i + di][j + dj].rgbtGreen;
                        b += image[i + di][j + dj].rgbtBlue;
                        cnt++;
                    }
                }
            }

            copy_image[i][j].rgbtRed = round(r / (float) cnt);
            copy_image[i][j].rgbtGreen = round(g / (float) cnt);
            copy_image[i][j].rgbtBlue = round(b / (float) cnt);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy_image[i][j];
        }
    }

    return;
}

int cliping(int pixel)
{
    if (pixel > 255)
    {
        return 255;
    }
    else if (pixel < 0)
    {
        return 0;
    }
    return pixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rx = 0, gx = 0, bx = 0;
            int ry = 0, gy = 0, by = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di < height && j + dj >= 0 && j + dj < width)
                    {
                        rx += image[i + di][j + dj].rgbtRed * Gx[di + 1][dj + 1];
                        gx += image[i + di][j + dj].rgbtGreen * Gx[di + 1][dj + 1];
                        bx += image[i + di][j + dj].rgbtBlue * Gx[di + 1][dj + 1];

                        ry += image[i + di][j + dj].rgbtRed * Gy[di + 1][dj + 1];
                        gy += image[i + di][j + dj].rgbtGreen * Gy[di + 1][dj + 1];
                        by += image[i + di][j + dj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }

            int pixel_r = round(sqrt(rx * rx + ry * ry));
            int pixel_g = round(sqrt(gx * gx + gy * gy));
            int pixel_b = round(sqrt(bx * bx + by * by));
            pixel_r = cliping(pixel_r);
            pixel_g = cliping(pixel_g);
            pixel_b = cliping(pixel_b);
            copy_image[i][j].rgbtRed = pixel_r;
            copy_image[i][j].rgbtGreen = pixel_g;
            copy_image[i][j].rgbtBlue = pixel_b;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy_image[i][j];
        }
    }
    return;
}
