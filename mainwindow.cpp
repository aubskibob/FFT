/*

mainwindow.cpp

Assignment 2 for CSC 442

Author: Aubrey Olson // Matt Richard
Date:   Feb 2015
*/

#include "mainwindow.h"

/******************************************************************************
 * Function: Menu_Palette_Grayscale
 * Description: Uses the built in qtimagelib grayscale function to convert
 *              the image to grayscale.
 * Parameters: image - the image to operate on
 * Returns: true if the image was successfully updated; otherwise, false
 *****************************************************************************/
bool MainWindow::Menu_Palette_Grayscale(Image &image)
{
    grayscale(image);
    return true;
}
