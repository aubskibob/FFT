#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimagelib.h>
#include "include/fftw3.h"

class MainWindow : public QObject
{
    Q_OBJECT

    public slots:
        bool Menu_Frequency_fftw_fft(Image &image);
        bool Menu_Histogram_Stretch(Image &image);
        bool Menu_Frequency_Ideal_Low_Pass(Image &image);
        bool Menu_Frequency_Ideal_High_Pass(Image &image);
        bool Menu_Frequency_Ideal_Emphasis(Image &image);
        bool Menu_Frequency_Butterworth_Low_Pass(Image &image);
        bool Menu_Frequency_Butterworth_High_Pass(Image &image);
        bool Menu_Frequency_Butterworth_Emphasis(Image &image);
        bool Menu_Frequency_Gaussian_Low_Pass(Image &image);
        bool Menu_Frequency_Gaussian_High_Pass(Image &image);
        bool Menu_Frequency_Gaussian_Emphasis(Image &image);
        bool Menu_Frequency_Homomorphic(Image &image);
        bool Menu_Frequency_Time_fftw(Image &image);
        bool Menu_Frequency_Time_fft(Image &image);

    private:
        void fft(fftw_complex* in, fftw_complex* out, int nrows, int ncols, int sign);
};

#endif // MAINWINDOW_H
