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

    fftw_destroy_plan(plan);
}

bool MainWindow::Menu_Frequency_Ideal_Low_Pass(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    double r = 10;
    if(!Dialog("Low Pass Filter").Add(r, "radius").Show())
        return false;

    if(r <= 0)
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);\
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

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

    int center_x = ncols / 2.0;
    int center_y = nrows / 2.0;

    // low pass filter
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            if(r < sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x)))
            {
                out[i*ncols + j][0] = 0;
                out[i*ncols + j][1] = 0;
            }
        }
    }

    fft(out, out2, nrows, ncols, FFTW_BACKWARD);

    double max_mag = 0;
    // compute magnitude and find max magnitude
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = sqrt(out2[i*ncols + j][0] * out2[i*ncols + j][0]
                + out2[i*ncols + j][1] * out2[i*ncols + j][1]);

            if(max_mag < in[i*ncols + j][0])
                max_mag = in[i*ncols + j][0];
        }
    }

    double mag;
    // scale image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = (int)(255.0 / max_mag * in[i*ncols + j][0]);
            if(mag < 0)
                mag = 0;
            else if(mag > 255)
                mag = 255;

            image[i][j] = mag;
        }
    }

    fftw_free(in);
    fftw_free(out2);
    fftw_free(out);

    return true;
}
