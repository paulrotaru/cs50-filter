#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //go to every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store the actual red, blue and green value
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //calculate average
            int aver = (int) ((round)(((red + blue + green) / 3.0)));

            //replace the original rgbt values with calculated average
            image[i][j].rgbtRed = aver;
            image[i][j].rgbtBlue = aver;
            image[i][j].rgbtGreen = aver;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     //go to every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store the actual red, blue and green value
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //calculate the new values according to the sepia formulas
            int newred = round(.393 * red + .769 * green + .189 * blue);
            int newblue = round(.272 * red + .534 * green + .131 * blue);
            int newgreen = round(.349 * red + .686 * green + .168 * blue);

            //check the new value to be less or equal with 255
            if (newred > 255)
            {
                newred = 255;
            }
            if (newblue > 255)
            {
                newblue = 255;
            }
            if (newgreen > 255)
            {
                newgreen = 255;
            }

            //replace the colours with the new colours
            image[i][j].rgbtRed = newred;
            image[i][j].rgbtBlue = newblue;
            image[i][j].rgbtGreen = newgreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create a holder to hold temporary the reverse image pixels
    RGBTRIPLE *buffer = calloc(3, 1);
    if (buffer == NULL)
    {
        return;
    }

    //go to every pixel from the halh of the collumns
    for (int i = 0; i < height; i++)
    {
        for (int j =0; j < width / 2; j++)
        {
            *buffer = image[i][j];
            image[i][j] = image [i][width - 1 -j];//oposite pixel
            image[i][width - 1 - j] = *buffer;
        }
    }
    free(buffer);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a new image to temporaly store the new values

    RGBTRIPLE new_image[height][width];

   //check all the pixels around one pixel and skip if they are outside
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalr = 0;
            int totalb = 0;
            int totalg = 0;
            int totalpixels = 0;
            //use l for line and c for column
            for (int l = -1; l < 2; l++)
            {
                if (i + l <0 || i + l > height - 1)
                {
                continue;
                }
                for (int c = -1; c < 2; c++)
                {
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    totalr = totalr + image[i + l][j + c].rgbtRed;
                    totalb = totalb + image[i + l][j + c].rgbtBlue;
                    totalg = totalg + image[i + l][j + c].rgbtGreen;
                    totalpixels ++;
                }
            }

            //calculate the average for the each color
            new_image[i][j].rgbtRed = (int) round((float)totalr / (float)totalpixels);
            new_image[i][j].rgbtBlue = (int) round((float)totalb / (float)totalpixels);
            new_image[i][j].rgbtGreen = (int) round((float)totalg / (float)totalpixels);

        }
    }
      //copy the new colors to the original image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
        }
    }

    return;
}
