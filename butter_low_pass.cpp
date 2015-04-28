/*

butter_low_pass.cpp

Final Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Apr 2015
*/

#include <mainwindow.h>
#include <cmath>

/******************************************************************************
 * Function: Menu_Frequency_Butterworth_Low_Pass
 * Description: Applys an Butterworth low pass filter on the given
 *              image in the frequency domain.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/

bool MainWindow::Menu_Frequency_Butterworth_Low_Pass(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    double cutoff = 10;
    if(!Dialog("Butterworth Low Pass Filter").Add(cutoff, "cutoff").Show())
        return false;

    if(cutoff <= 0)
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    // allocate memory
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // populate the complex array with intensity values from the image (reals) and 0's (imaginary)
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = image[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // execute the forward Fourier Transformation
    fft(in, out, nrows, ncols, FFTW_FORWARD);

    int center_x = ncols / 2.0;
    int center_y = nrows / 2.0;

    // apply the butterworth low pass filter
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            float D = sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x));
            float H = 1/(1+pow((D/cutoff),4));

            out[i*ncols + j][0] *= H;
            out[i*ncols + j][1] *= H;

        }
    }

    // execute the inverse Fourier Transformation
    fft(out, out2, nrows, ncols, FFTW_BACKWARD);

    double mag;
    // compute magnitude and update image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = sqrt(out2[i*ncols + j][0] * out2[i*ncols + j][0]
                    + out2[i*ncols + j][1] * out2[i*ncols + j][1]);
            if(mag < 0)
                mag = 0;
            else if(mag > 255)
                mag = 255;

            image[i][j] = mag;
        }
    }

    // delete and free memory
    fftw_free(in);
    fftw_free(out2);
    fftw_free(out);

    return true;
}
