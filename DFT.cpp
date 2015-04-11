/*

FFT.cpp

Final Assignment for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
*/

#include "mainwindow.h"
#include <math.h>

/******************************************************************************
 * Function: Menu_FFT
 * Description: FFT the given image.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/
bool MainWindow::Menu_Frequency_DFT(Image &image)
{
    /*Image imageCopy = image;

    if(image.IsNull())
        return false;

    int nrows = image.Height();
    int ncols = image.Width();
    int real[nrows];
    int imag[nrows];

    // Loop through every pixel in the image
    for(int r = 0; r < nrows; r++)
    {
        real[r] = image
    }

    return true;*/
}

/*
   Direct fourier transform
*/
int DFT(int dir,int m,double *x1,double *y1)
{
   long i,k;
   double arg;
   double cosarg,sinarg;
   double *x2 = 0,*y2 = 0;

    if (x2 == NULL || y2 == NULL)
     return(FALSE);

    for (i=0;i<m;i++) {
     x2[i] = 0;
     y2[i] = 0;
     arg = - dir * 2.0 * 3.141592654 * (double)i / (double)m;
     for (k=0;k<m;k++) {
        cosarg = cos(k * arg);
        sinarg = sin(k * arg);
        x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
        y2[i] += (x1[k] * sinarg + y1[k] * cosarg);
     }
    }

    /* Copy the data back */
    if (dir == 1) {
     for (i=0;i<m;i++) {
        x1[i] = x2[i] / (double)m;
        y1[i] = y2[i] / (double)m;
     }
    } else {
     for (i=0;i<m;i++) {
        x1[i] = x2[i];
        y1[i] = y2[i];
     }
    }

    return(TRUE);
    }
