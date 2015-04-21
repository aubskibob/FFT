

#include <mainwindow.h>
#include <cmath>

#include <iostream>

bool MainWindow::Menu_Frequency_Homomorphic(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    double cutoff = 10;
    double gamma_high = 10;
    double gamma_low = 2;
    if(!Dialog("Homomorphic Filter").Add(cutoff, "Cutoff").Add(gamma_high, "Gamma High").Add(gamma_low, "Gamma Low").Show())
        return false;

    if(cutoff <= 0)
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);\
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = log(image[i][j] + 1) * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fft(in, out, nrows, ncols, FFTW_FORWARD);

    int center_x = ncols / 2.0;
    int center_y = nrows / 2.0;

    // gaussian high pass filter
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

    double re, im;
    // compute magnitude
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            re = exp(out2[i*ncols + j][0]) * cos(out2[i*ncols + j][1]);
            im = exp(out2[i*ncols + j][0]) * sin(out2[i*ncols + j][1]);

            //mag = sqrt(out2[i*ncols + j][0] * out2[i*ncols + j][0]
            //    + out2[i*ncols + j][1] * out2[i*ncols + j][1]);
            mag = sqrt(re*re + im*im);

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
