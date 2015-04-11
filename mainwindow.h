#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimagelib.h>

class MainWindow : public QObject
{
    Q_OBJECT;

    public slots:
        //bool Menu_Frequency_FFT(Image &image);
        bool Menu_Frequency_fftw_fft(Image &image);
        bool Menu_Frequency_fftw_fft_v2(Image &image);
        bool Menu_Histogram_Stretch(Image &image);
};

#endif // MAINWINDOW_H
