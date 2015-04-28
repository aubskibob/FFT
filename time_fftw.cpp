/*

time_fftw.cpp

Final Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   April 2015
*/

#include <mainwindow.h>
#include <QElapsedTimer>

#include <iostream>

using namespace std;

/******************************************************************************
 * Function: Menu_Frequency_Time_fftw
 * Description: Times the forward and inverse FFT of the given image using fftw
 *              and prints the results to the console.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully operated upon; otherwise, false
 *****************************************************************************/
bool MainWindow::Menu_Frequency_Time_fftw(Image &image)
{
    fftw_complex* in;
    fftw_complex* out;
    fftw_complex* out2;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    // initialize the input to the FFT with the image
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            // Negate every other value to shift the image by half the period
            in[i*ncols + j][0] = image[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fftw_plan plan = fftw_plan_dft_2d(nrows, ncols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Time forward FFT
    QElapsedTimer timer;
    timer.start();
    fftw_execute(plan);
    cout << "Forward fftw elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << endl;

    fftw_destroy_plan(plan);

    plan = fftw_plan_dft_2d(nrows, ncols, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    // Time inverse FFT
    timer.restart();
    fftw_execute(plan);
    cout << "Backward fftw elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << endl;

    fftw_destroy_plan(plan);

    fftw_free(in);
    fftw_free(out2);
    fftw_free(out);

    return true;
}
