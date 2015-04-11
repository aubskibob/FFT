/*

mainwindow.cpp

Assignment 2 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
*/

#include "mainwindow.h"

#include "include/fftw3.h"
#include <cmath>

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
    double *in;
    int nyh;
    fftw_complex* out;
    fftw_plan plan_forward;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (double*)malloc(sizeof(double) * nrows * ncols);

    for(int i = 0; i < nrows; i++)
        for(int j = 0; j < ncols; j++)
            in[i*ncols + j] = image[i][j];

    nyh = (ncols / 2) + 1;

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * nyh);

    plan_forward = fftw_plan_dft_r2c_2d(nrows, ncols, in, out, FFTW_ESTIMATE);

    fftw_execute(plan_forward);

    grayscale(image);

    double mag;
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            if(j < nyh)
                mag = sqrt(out[i*nyh + j][0] * out[i*nyh + j][0]
                    + out[i*nyh + j][1] * out[i*nyh + j][1]);
            else
                mag = sqrt(out[i*nyh + nyh - (j % nyh)][0] * out[i*nyh + nyh - (j % nyh)][0]
                    + out[i*nyh + nyh - (j % nyh)][1] * out[i*nyh + nyh - (j % nyh)][1]);
            mag = (int)log(mag);
            if(mag < 0)
                mag = 0;
            else if(mag > 255)
                mag = 255;

            image[(i + nrows / 2) % nrows][(j + ncols / 2) % ncols] = mag;
        }
    }

    fftw_destroy_plan(plan_forward);

    free(in);
    fftw_free(out);

    return true;
}

bool MainWindow::Menu_Frequency_fftw_fft_v2(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_plan plan;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = image[i][j];
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    plan = fftw_plan_dft_2d(nrows, ncols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);

    grayscale(image);

    double mag;
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = sqrt(out[i*ncols + j][0] * out[i*ncols + j][0]
                + out[i*ncols + j][1] * out[i*ncols + j][1]);
            mag = (int)log(mag);
            if(mag < 0)
                mag = 0;
            else if(mag > 255)
                mag = 255;

            image[i][j] = mag;
        }
    }

    return true;
}
