#include <mainwindow.h>
#include <QElapsedTimer>

#include <iostream>

using namespace std;

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

    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            in[i*ncols + j][0] = image[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
            in[i*ncols + j][1] = 0;
        }
    }

    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nrows * ncols);

    fftw_plan plan = fftw_plan_dft_2d(nrows, ncols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    QElapsedTimer timer;
    timer.start();
    fftw_execute(plan);
    cout << "Forward fftw elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << endl;

    fftw_destroy_plan(plan);

    plan = fftw_plan_dft_2d(nrows, ncols, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    timer.restart();
    fftw_execute(plan);
    cout << "Backward fftw elapsed time: " << timer.nsecsElapsed() / 10.0e9 << " seconds" << endl;

    fftw_destroy_plan(plan);

    fftw_free(in);
    fftw_free(out2);
    fftw_free(out);

    return true;
}
