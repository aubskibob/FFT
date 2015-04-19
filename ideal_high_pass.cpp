#include <mainwindow.h>
#include <cmath>

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
            if(r > sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x)))
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