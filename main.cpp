/*

main.cpp

Assignment 3 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   April 2015
Program Description:
    2-D FFT and frequency domain filtering (ideal, Butterworth, Gaussian, homomorphic)

Project Overview:
    We implemented the Fourier Transformation as a baseline function for this project.
    Specifically, we implemented a 2-D Fast Fourier Transformation called Fastest Fourier Transformation in the West (FFTW).
    We also implmented QTImageLib's fft2D for time to execute comparison.
    We used our implementation of the FFTW as our primary module to build frequency domain filters.
    The frequency domain filters we implemented are the ideal, Butterworth and homomorphic. Below lists all the filters we implemented.

Frequency domain filters:
    Ideal low pass
    Ideal high pass
    Ideal emphasis
    Butterworth low pass
    Butterworth high pass
    Butterworth emphasis
    Gaussian low pass
    Gaussian high pass
    Gaussian emphasis
    Homomorphic emphasis


Necessary Headers
    cmath.h
    mainwindow.h

Necessary Files:
    mainwindow.cpp \
    ideal_low_pass.cpp \
    ideal_high_pass.cpp \
    ideal_emphasis.cpp \
    butter_low_pass.cpp \
    butter_high_pass.cpp \
    gauss_low_pass.cpp \
    gauss_high_pass.cpp \
    gauss_emphasis.cpp \
    butter_emphasis.cpp \
    homomorphic.cpp \
    time_fftw.cpp \
    time_fft.cpp
*/

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    MainWindow mw;
    ImageApp app(argc, argv);
    app.AddActions(&mw);
    return app.Start();
}
