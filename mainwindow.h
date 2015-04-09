#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimagelib.h>

class MainWindow : public QObject
{
    Q_OBJECT;

    public slots:
        bool Menu_Palette_Grayscale(Image &image);

};

#endif // MAINWINDOW_H
