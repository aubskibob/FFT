#include <mainwindow.h>
#include <cmath>

bool MainWindow::Menu_Frequency_Ideal_Emphasis(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    double r = 10;
    double low = 0.5;
    double high = 2.0;
    if(!Dialog("Low Pass Filter").Add(r, "radius").Add(low, "low").Add(high, "high").Show())
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

    // high frequency emphasis filter
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            if(r > sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x)))
            {
                out[i*ncols + j][0] *= low;
                out[i*ncols + j][1] *= low;
            }
            else
            {
                out[i*ncols + j][0] *= high;
                out[i*ncols + j][1] *= high;
            }
        }
    }

    fft(out, out2, nrows, ncols, FFTW_BACKWARD);

    double mag;
    // compute magnitude
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
