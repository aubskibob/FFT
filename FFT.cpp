/*

FFT.cpp

Final Assignment for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
*/

#include "mainwindow.h"
#include <complex.h>
#include <iostream>

/******************************************************************************
 * Function: Menu_FFT
 * Description: FFT the given image.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/

int isPowerOfTwo (int x)
{
    while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
        x /= 2;

    return (x == 1);
}

int pow2roundup (int x)
{
    if (x < 0) return 0;

    --x;

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x+1;
}
/*
bool MainWindow::Menu_Frequency_FFT(Image &image)
{
    Image imageCopy;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();
    bool rowsSquare = isPowerOfTwo(nrows);
    bool colsSquare = isPowerOfTwo(ncols);

    //if the image is not a square power of two we need to make it so
    if(!rowsSquare)
    {
        //round up to the next power of 2
        nrows = pow2roundup(nrows);
    }
    //if the image is not a square power of two we need to make it so
    if(!colsSquare)
    {
        //round up to the next power of 2
        ncols = pow2roundup(ncols);
    }

    //if the image was found to not be square and a power of two make it so with old image centered in new image surrounded by 0's
    if(!rowsSquare && !colsSquare)
    {
        // create a new image with appropiate proportions
        imageCopy = *new Image(nrows,ncols);
        int originalRows = image.Height();
        int originalCols = image.Width();
        int bufferRows = (nrows - originalRows) / 2;
        //int bufferCols = (ncols - originalCols) / 2;

        for(int r = 0; r < nrows; r++)
        {
            for(int c = 0; c < ncols; c++)
            {
                if((r < bufferRows || r > (bufferRows + originalRows)))
                      //  && (c < bufferCols || c > (bufferCols + originalCols)))
                    imageCopy[r][c] = 0;
                else
                    imageCopy[r][c] = 128;
            }
        }
    }
    else
    {
        imageCopy = image;
    }

    float **allReals = new float*[nrows];
    float **allImaginary = new float*[ncols];

    // Loop through every pixel in the image and build an array
    for(int c = 0; c < ncols; c++)
    {
        allReals[c] = new float[ncols];
    }

    // Loop through every pixel in the image and build an array
    for(int c = 0; c < ncols; c++)
    {
        allImaginary[c] = new float[ncols];
    }

    // Loop through every pixel in the image and build an array
    for(int r = 0; r < nrows; r++)
    {
        for(int c = 0; c < ncols; c++)
        {
            allReals[r][c] = 0.0;
            allImaginary[r][c] = 0.0;
        }
    }

    //fft2D(1,nrows,ncols,allReals,allImaginary);

    image = *new Image(nrows,ncols);

    image = imageCopy;

    return true;
}

*/
