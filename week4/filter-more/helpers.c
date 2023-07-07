#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            // avarage of rgb to create grayscale
            float a = round((r + g + b) / 3.0);

            image[h][w].rgbtRed = image[h][w].rgbtGreen = image[h][w].rgbtBlue = a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        float n = floor((width - 1) / 2.0);

        for (int w = 0; w <= n; w++)
        {
            // load left side
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            // rewrite left side
            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;

            // rewrite right side
            image[h][width - w - 1].rgbtRed = r;
            image[h][width - w - 1].rgbtGreen = g;
            image[h][width - w - 1].rgbtBlue = b;
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float counter = 0;
    int sum = 0;

    /** Start from 1 row before it and end at 1 row after it- total of 3rows */
    for (int r = i - 1; r < (i + 2); r++)
    {
        /** Start from 1 block before it and end at 1 block after it- total of 3blocks */
        for (int c = j - 1; c < (j + 2); c ++)
        {
            // just for existing pixels
            if (r < 0 || c < 0 || r >= height || c >= width)
            {
                continue;
            }
            if (color_position == 0)
            {
                sum += image[r][c].rgbtRed;
            }
            else if (color_position == 1)
            {
                sum += image[r][c].rgbtGreen;
            }
            else
            {
                sum += image[r][c].rgbtBlue;
            }
            counter++;
        }
    }
    return round(sum / counter);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy to work with original values
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // blur for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, 2);
        }
    }
    return;
}

int edgeDetection(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    int GxF[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}},
    GyF[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}},
    Gx = 0,
    Gy = 0,
    sum = 0,
    row = 0,
    colum = 0;

    /** Start from 1 row before it and end at 1 row after it- total of 3rows */
    for (int r = i - 1; r < (i + 2); r++)
    {
        colum = 0;
        /** Start from 1 block before it and end at 1 block after it- total of 3blocks */
        for (int c = j - 1; c < (j + 2); c ++)
        {
            // just for existing pixels
            if (r >= 0 && c >= 0 && r < height && c < width)
            {
                if (color_position == 0)
                {
                    Gx += image[r][c].rgbtRed * GxF[row][colum];
                    Gy += image[r][c].rgbtRed * GyF[row][colum];
                }
                else if (color_position == 1)
                {
                    Gx += image[r][c].rgbtGreen * GxF[row][colum];
                    Gy += image[r][c].rgbtGreen * GyF[row][colum];
                }
                else
                {
                    Gx += image[r][c].rgbtBlue * GxF[row][colum];
                    Gy += image[r][c].rgbtBlue * GyF[row][colum];
                }
            }
            colum++;
        }
        row++;
    }

    sum = round(sqrt(Gx * Gx + Gy * Gy));

    if (sum > 255)
    {
        return 255;
    }
    else
    {
        return sum;
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy to work with original values
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // detect for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edgeDetection(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = edgeDetection(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = edgeDetection(i, j, height, width, copy, 2);
        }
    }
    return;
}
