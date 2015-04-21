/*

mainwindow.cpp

Assignment 2 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
*/

#include "mainwindow.h"

#include <cmath>
#include <iostream>

/******************************************************************************
 * Function: Menu_Palette_Grayscale
 * Description: Uses the built in qtimagelib grayscale function to convert
 *              the image to grayscale.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/
/*bool MainWindow::Menu_Palette_Grayscale(Image &image)
{
    grayscale(image);
    return true;
}
*/

bool MainWindow::Menu_Histogram_Stretch(Image &image)
{
    histogramStretch( image );
    return true;
}

bool MainWindow::Menu_Frequency_fftw_fft(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // Initialize in variable using image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = image[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fft(in, out, nrows, ncols, FFTW_FORWARD);

    grayscale(image);

    double max_mag = 0;
    // Calculate magnitudes and find max magnitude
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = sqrt(out[i*ncols + j][0] * out[i*ncols + j][0]
                + out[i*ncols + j][1] * out[i*ncols + j][1]);

            if(max_mag < in[i*ncols + j][0])
                max_mag = in[i*ncols + j][0];
        }
    }

    double scale = 255.0 / log(max_mag + 1);
    double mag;
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = (int)(scale * log(in[i*ncols + j][0] + 1));
            if(mag < 0)
                mag = 0;
            else if(mag > 255)
                mag = 255;

            image[i][j] = mag;
        }
    }

    fftw_free(in);
    fftw_free(out);

    return true;
}

void MainWindow::fft(fftw_complex* in, fftw_complex* out, int nrows, int ncols, int sign)
{
    fftw_plan plan = fftw_plan_dft_2d(nrows, ncols, in, out, sign, FFTW_ESTIMATE);

    fftw_execute(plan);

    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            out[i*ncols + j][0] /= (double)nrows;
            out[i*ncols + j][1] /= (double)nrows;
        }
    }

    fftw_destroy_plan(plan);
}
