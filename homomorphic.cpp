/*

homomorphic.cpp

Final Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   April 2015
*/

#include <mainwindow.h>
#include <cmath>

/******************************************************************************
 * Function: Menu_Frequency_Homomorphic
 * Description: Applys a homomorphic filter on the given image in the
 *              frequency domain.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/
bool MainWindow::Menu_Frequency_Homomorphic(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    double cutoff = 10;
    double gamma_high = 2;
    double gamma_low = 1;
    // Get gamma values and cutoff from the user
    if(!Dialog("Homomorphic Filter").Add(cutoff, "Cutoff").Add(gamma_high, "Gamma High").Add(gamma_low, "Gamma Low").Show())
        return false;

    if(cutoff <= 0)
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // initialize in variable with the log of the image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            // negate every other value to shift FFT by half the period
            in[i*ncols + j][0] = log(image[i][j] + 1) * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fft(in, out, nrows, ncols, FFTW_FORWARD);

    int center_x = ncols / 2.0;
    int center_y = nrows / 2.0;

    // homomorphic filter
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            float D = sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x));
            float H = (gamma_high - gamma_low) * (1.0 - exp((-D*D)/(cutoff*cutoff))) + gamma_low;

            out[i*ncols + j][0] *= H;
            out[i*ncols + j][1] *= H;

        }
    }

    fft(out, out2, nrows, ncols, FFTW_BACKWARD);

    double mag;
    // exponentiate and update image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = exp(out2[i*ncols + j][0]);

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
