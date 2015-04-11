#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimagelib.h>
#include "include/fftw3.h"

class MainWindow : public QObject
{
    Q_OBJECT;

    public:
        void fft(fftw_complex* in, fftw_complex* out, int nrows, int ncols, int sign);

    public slots:
        //bool Menu_Frequency_FFT(Image &image);
        bool Menu_Frequency_fftw_fft(Image &image);
        bool Menu_Frequency_fftw_fft_v2(Image &image);
        //bool Menu_Frequency_FFT(Image &image);
        //bool Menu_Frequency_DFT(Image &image);
        bool Menu_Histogram_Stretch(Image &image);
        bool Menu_Frequency_Ideal_Low_Pass(Image &image);
};

#endif // MAINWINDOW_H
