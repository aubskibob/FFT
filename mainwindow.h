#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimagelib.h>

class MainWindow : public QObject
{
    Q_OBJECT;

    public slots:
        bool Menu_Frequency_FFT(Image &image);

};

#endif // MAINWINDOW_H
