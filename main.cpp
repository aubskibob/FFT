/*

main.cpp

Assignment 2 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
Program Description:  This program shows all of the neighborhood processes detailed in class and at
                        http://www.mcs.sdsmt.edu/csc442/Assignments/PA2.pdf.  It can open, modify,  and
                        save user-specified images.

Necessary Headers
    math.h
    mainwindow.h

Necessary Files:
    mainwindow.cpp \
    smoothing3_3.cpp \
    sharpening.cpp \
    outofrange.cpp \
    meanfilterN_N.cpp \
    outofrangeN_N.cpp \
    kirsh_direction.cpp \
    kirsh_magnitude.cpp \
    laplacian.cpp \
    maximum.cpp \
    median_plus.cpp \
    minimum.cpp \
    emboss.cpp \
    median.cpp \
    standardDevN_N.cpp \
    sobel_edge_mag.cpp \
    sobel_edge_dir.cpp \
    gaussian_smoothing.cpp
*/

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    MainWindow mw;
    ImageApp app(argc, argv);
    app.AddActions(&mw);
    return app.Start();
}
