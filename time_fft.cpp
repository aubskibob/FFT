/*

time_fftw.cpp

Final Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   April 2015
*/

#include <mainwindow.h>
#include <QElapsedTimer>
#include <complex.h>
#include <iostream>

using namespace std;

/******************************************************************************
 * Function: Menu_Frequency_Time_fft
 * Description: Times the forward and inverse FFT of the given image using fftw
 *              and prints the results to the console.
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

bool MainWindow::Menu_Frequency_Time_fft(Image &image)
{
    Image imageCopy;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();
    bool rowsSquare = isPowerOfTwo(nrows);
    bool colsSquare = isPowerOfTwo(ncols);

    //if the image dimensions are not a power of two we need to make it so
    if(!rowsSquare)
    {
        //round up to the next power of 2
        nrows = pow2roundup(nrows);
    }
    //if the image dimensions are not a power of two we need to make it so
    if(!colsSquare)
    {
        //round up to the next power of 2
        ncols = pow2roundup(ncols);
    }

    //if the image dimensions are not a power of two we need to make the old image centered in new image surrounded by 0's
    if(!rowsSquare || !colsSquare)
    {

        cout << "nrows: " << nrows << endl;
        cout << "ncols: " << ncols << endl;

        // create a new image with appropiate proportions
        imageCopy = *new Image(nrows,ncols);
        int originalRows = image.Height();
        int originalCols = image.Width();
        int bufferRows = (nrows - originalRows) / 2;
        int bufferCols = (ncols - originalCols) / 2;

        for(int r = 0; r < nrows; r++)
        {
            for(int c = 0; c < ncols; c++)
            {
                if((r < bufferRows || r > (bufferRows + originalRows) - 1) || (c < bufferCols || c > (bufferCols + originalCols) - 1))
                    imageCopy[r][c] = 0;
                else
                    imageCopy[r][c] = image[r - bufferRows][c - bufferCols];
            }
        }
    }
    else
    {
        imageCopy = image;
    }

    float **allReals = new float*[nrows];
    float **allImaginary = new float*[nrows];

    // finish building array
    for(int r = 0; r < nrows; r++)
    {
        allReals[r] = new float[ncols];
        allImaginary[r] = new float[ncols];
    }

    // Loop through every pixel and dump into real and imaginary array
    for(int r = 0; r < nrows; r++)
    {
        for(int c = 0; c < ncols; c++)
        {

            //std::cout << r << " " << c << std::endl;
            allReals[r][c] = imageCopy[r][c]  * ((r + c) % 2 == 0 ? 1 : -1);
            allImaginary[r][c] = 0.0;
        }
    }

    // Loop through every pixel in the image and build an array
    for(int r = 0; r < nrows; r++)
    {
        for(int c = 0; c < ncols; c++)
        {
            imageCopy[r][c] = allReals[r][c];
            allImaginary[r][c] = 0.0;
        }
    }

    QElapsedTimer timer;
    timer.start();
    fft2D(1,nrows,ncols,allReals,allImaginary);
    std::cout << "Forward fft elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << std::endl;

    timer.restart();
    fft2D(0,nrows,ncols,allReals,allImaginary);
    std::cout << "Backward fft elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << std::endl;

    // Loop through every pixel in the image and build an array
    for(int r = 0; r < nrows; r++)
    {
        delete[] allReals[r];
        delete[] allImaginary[r];
    }

    delete[] allReals;
    delete[] allImaginary;

    return true;
}


