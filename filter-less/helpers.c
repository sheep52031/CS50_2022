#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int  averge = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // round it to
            averge = (int)(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0) + 0.5);

            image[i][j].rgbtRed = averge;
            image[i][j].rgbtGreen = averge;
            image[i][j].rgbtBlue = averge;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // One by one claulate.
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            // If number over 255 then set 255.
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp;

    // Swap pixel until half width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {

            temp = image[i][j];

            image[i][j] = image[i][(width - 1) - j];

            image[i][(width - 1) - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage[height][width];
    int tempRed = 0;
    int tempGreen = 0;
    int tempBlue = 0;
    // count can check around the pixel have other pixels?
    float count;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempRed = 0;
            tempGreen = 0;
            tempBlue = 0;
            count = 1.0;

            // Top left
            if (i > 0 && j > 0)
            {
                tempRed += image[i - 1][j - 1].rgbtRed;
                tempGreen += image[i - 1][j - 1].rgbtGreen;
                tempBlue += image[i - 1][j - 1].rgbtBlue;
                count += 1.0;
            }

            // Top miiddle
            if (i > 0)
            {
                tempRed += image[i - 1][j].rgbtRed;
                tempGreen +=  image[i - 1][j].rgbtGreen;
                tempBlue +=  image[i - 1][j].rgbtBlue;
                count += 1.0;
            }
            // Top right
            if (i > 0 && j < (width - 1))
            {
                tempRed += image[i - 1][j + 1].rgbtRed;
                tempGreen += image[i - 1][j + 1].rgbtGreen;
                tempBlue += image[i - 1][j + 1].rgbtBlue;
                count += 1.0;
            }
            // Middle left
            if (j > 0)
            {
                tempRed += image[i][j - 1].rgbtRed;
                tempGreen += image[i][j - 1].rgbtGreen;
                tempBlue += image[i][j - 1].rgbtBlue;
                count += 1.0;
            }
            // Middle right
            if (j < (width - 1))
            {
                tempRed += image[i][j + 1].rgbtRed;
                tempGreen += image[i][j + 1].rgbtGreen;
                tempBlue += image[i][j + 1].rgbtBlue;
                count += 1.0;
            }
            // Buttom left
            if (i < (height - 1) && j > 0)
            {
                tempRed += image[i + 1][j - 1].rgbtRed;
                tempGreen += image[i + 1][j - 1].rgbtGreen;
                tempBlue += image[i + 1][j - 1].rgbtBlue;
                count += 1.0;
            }
            // Button middele
            if (i < (height - 1))
            {
                tempRed += image[i + 1][j].rgbtRed;
                tempGreen += image[i + 1][j].rgbtGreen;
                tempBlue += image[i + 1][j].rgbtBlue;
                count += 1.0;
            }
            // Button right
            if (i < (height - 1) && j < (width - 1))
            {
                tempRed += image[i + 1][j + 1].rgbtRed;
                tempGreen += image[i + 1][j + 1].rgbtGreen;
                tempBlue += image[i + 1][j + 1].rgbtBlue;
                count += 1.0;
            }

            // Add all of around pixel if this pixel around have others pixels and divide by around pixel number include itself.
            copyimage[i][j].rgbtRed = round((tempRed + image[i][j].rgbtRed) / count);
            copyimage[i][j].rgbtGreen = round((tempGreen + image[i][j].rgbtGreen) / count);
            copyimage[i][j].rgbtBlue = round((tempBlue + image[i][j].rgbtBlue) / count);
        }
    }


    // return all image pixel to image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copyimage[i][j];
        }
    }
    return;
}
