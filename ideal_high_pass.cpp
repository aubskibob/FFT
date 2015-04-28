/*

ideal_high_pass.cpp

Final Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   April 2015
*/

#include <mainwindow.h>
#include <cmath>

/******************************************************************************
 * Function: Menu_Frequency_Ideal_High_Pass
 * Description: Applys an ideal high pass filter on the given image in the
 *              frequency domain.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/
bool MainWindow::Menu_Frequency_Ideal_High_Pass(Image &image)
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

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // Initialize in variable with the image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            // negate every other value to shift FFT by half the period
            in[i*ncols + j][0] = image[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fft(in, out, nrows, ncols, FFTW_FORWARD);

    int center_x = ncols / 2.0;
    int center_y = nrows / 2.0;

    // high pass filter
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            if(r > sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x)))
            {
                out[i*ncols + j][0] = 0;
                out[i*ncols + j][1] = 0;
            }
        }
    }

    fft(out, out2, nrows, ncols, FFTW_BACKWARD);

    double mag;
    // compute magnitude and update image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = sqrt(out2[i*ncols + j][0] * out2[i*ncols + j][0]
                + out2[i*ncols + j][1] * out2[i*ncols + j][1]);

            if(mag > 255)
                mag = 255;

            image[i][j] = mag;
        }
    }

    fftw_free(in);
    fftw_free(out2);
    fftw_free(out);

    return true;
}
