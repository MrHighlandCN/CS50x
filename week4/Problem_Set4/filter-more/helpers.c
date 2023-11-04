#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int red = image[i][j].rgbtRed;
            unsigned int green = image[i][j].rgbtGreen;
            unsigned int blue = image[i][j].rgbtBlue;
            unsigned int avg = round((red + blue + green) / 3.0);
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
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE subImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = image[i][j].rgbtRed;
            float sumGreen = image[i][j].rgbtGreen;
            float sumBlue = image[i][j].rgbtBlue;
            float count;
            if (i == 0)
            {
                if (j == 0)
                {
                    sumRed += image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    sumGreen += image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    sumBlue += image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    count = 4;
                }
                else if (j == width - 1)
                {
                    sumRed += image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    sumGreen += image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    sumBlue += image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    count = 4;
                }
                else
                {
                    sumRed += image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                              image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    sumGreen += image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    sumBlue += image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                               image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    count = 6;
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    count = 4;
                }
                else if (j == width - 1)
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
                    count = 4;
                }
                else
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                               image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
                    count = 6;
                }
            }
            else
            {
                if (j == 0)
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed +
                              image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                    count = 6;
                }
                else if (j == width - 1)
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed +
                              image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                               image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                    count = 6;
                }
                else
                {
                    sumRed += image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                              image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    sumGreen += image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    sumBlue += image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                               image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                               image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    count = 9;
                }
            }
            int avgRed = round(sumRed / count);
            int avgGreen = round(sumGreen / count);
            int avgBlue = round(sumBlue / count);
            subImage[i][j].rgbtRed = avgRed;
            subImage[i][j].rgbtGreen = avgGreen;
            subImage[i][j].rgbtBlue = avgBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = subImage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE subImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float productRedX = 0;
            float productGreenX = 0;
            float productBlueX = 0;

            float productRedY = 0;
            float productGreenY = 0;
            float productBlueY = 0;
            if (i == 0)
            {
                if (j == 0)
                {
                    // Gx
                    productRedX += image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                    productGreenX += image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                    productBlueX += image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;

                    // Gy
                    productRedY += image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                    productGreenY += image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                    productBlueY += image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;
                }
                else if (j == width - 1)
                {
                    // Gx
                    productRedX += image[i][j - 1].rgbtRed * (-2) - image[i + 1][j - 1].rgbtRed;
                    productGreenX += image[i][j - 1].rgbtGreen * (-2) - image[i + 1][j - 1].rgbtGreen;
                    productBlueX += image[i][j - 1].rgbtBlue * (-2) - image[i + 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed;
                    productGreenY += image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen;
                    productBlueY += image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue;
                }
                else
                {
                    // Gx
                    productRedX += image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed * (-2) -
                                   image[i + 1][j - 1].rgbtRed;
                    productGreenX += image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen +
                                     image[i][j - 1].rgbtGreen * (-2) - image[i + 1][j - 1].rgbtGreen;
                    productBlueX += image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue * (-2) -
                                    image[i + 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    productGreenY += image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    productBlueY += image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    // Gx
                    productRedX += image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed;
                    productGreenX += image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen;
                    productBlueX += image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j + 1].rgbtRed;
                    productGreenY += image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j + 1].rgbtGreen;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j + 1].rgbtBlue;
                }
                else if (j == width - 1)
                {
                    // Gx
                    productRedX += image[i][j - 1].rgbtRed * (-2) - image[i - 1][j - 1].rgbtRed;
                    productGreenX += image[i][j - 1].rgbtGreen * (-2) - image[i - 1][j - 1].rgbtGreen;
                    productBlueX += image[i][j - 1].rgbtBlue * (-2) - image[i - 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j - 1].rgbtRed;
                    productGreenY += image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j - 1].rgbtGreen;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j - 1].rgbtBlue;
                }
                else
                {
                    // Gx
                    productRedX += image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed * (-2) -
                                   image[i - 1][j - 1].rgbtRed;
                    productGreenX += image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen +
                                     image[i][j - 1].rgbtGreen * (-2) - image[i - 1][j - 1].rgbtGreen;
                    productBlueX += image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue * (-2) -
                                    image[i - 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                    productGreenY +=
                        image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                }
            }
            else
            {
                if (j == 0)
                {
                    // Gx
                    productRedX += image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                    productGreenX += image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                    productBlueX += image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                   image[i + 1][j].rgbtRed * 2;
                    productGreenY += image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j + 1].rgbtGreen +
                                     image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                    image[i + 1][j].rgbtBlue * 2;
                }
                else if (j == width - 1)
                {
                    // Gx
                    productRedX += -image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed * (-2) - image[i + 1][j - 1].rgbtRed;
                    productGreenX +=
                        -image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen * (-2) - image[i + 1][j - 1].rgbtGreen;
                    productBlueX += -image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue * (-2) - image[i + 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                   image[i + 1][j].rgbtRed * 2;
                    productGreenY += image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j - 1].rgbtGreen +
                                     image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                    image[i + 1][j].rgbtBlue * 2;
                }
                else
                {
                    // Gx
                    productRedX += image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed * (-2) -
                                   image[i - 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    productGreenX += image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen +
                                     image[i][j - 1].rgbtGreen * (-2) - image[i - 1][j - 1].rgbtGreen +
                                     image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    productBlueX += image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue * (-2) -
                                    image[i - 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;

                    // Gy
                    productRedY += image[i - 1][j].rgbtRed * (-2) - image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed +
                                   image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed;
                    productGreenY += image[i - 1][j].rgbtGreen * (-2) - image[i - 1][j + 1].rgbtGreen -
                                     image[i - 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2 +
                                     image[i + 1][j - 1].rgbtGreen;
                    productBlueY += image[i - 1][j].rgbtBlue * (-2) - image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue +
                                    image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue;
                }
            }
            int Red = round(sqrt(pow(productRedX, 2) + pow(productRedY, 2)));
            int Green = round(sqrt(pow(productGreenX, 2) + pow(productGreenY, 2)));
            int Blue = round(sqrt(pow(productBlueX, 2) + pow(productBlueY, 2)));
            if (Red >= 255)
                Red = 255;
            if (Green >= 255)
                Green = 255;
            if (Blue >= 255)
                Blue = 255;
            subImage[i][j].rgbtRed = Red;
            subImage[i][j].rgbtGreen = Green;
            subImage[i][j].rgbtBlue = Blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = subImage[i][j];
        }
    }
    return;
}
