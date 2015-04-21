

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
            float H = (gamma_high - gamma_low) * (1.0 - exp((-1*D*D)/(cutoff*cutoff))) + gamma_low;
            //float H = (1.0 - exp((-1*D*D)/(cutoff*cutoff)));

            //std::cout << "H: " << H << std::endl;

            out[i*ncols + j][0] *= H;
            out[i*ncols + j][1] *= H;

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

    std::cout << "max_mag: " << max_mag << std::endl;

    double mag;
    // scale image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            mag = (int)(255.0 / exp(max_mag) * exp(in[i*ncols + j][0]));
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