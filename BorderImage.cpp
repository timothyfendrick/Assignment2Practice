//
// Created by Elizabeth Zak on 3/7/25.
//

#include "BorderImage.h"

#include <iostream>
#include <ostream>

#include"SimpleImage.h"

BorderedImage::BorderedImage(int w) {
    //we already have the image's width
    borderWidth = w;
    borderColor = RGB(255, 0, 0); //We set our default border to red because we are Firebirds
}

BorderedImage::BorderedImage(int w, RGB c) {
    borderWidth = w;
    borderColor = c;
}

void BorderedImage::setBorderWidth(int w) {
    borderWidth = w;
}

int BorderedImage::getBorderWidth() {
    return borderWidth;
}

void BorderedImage::setBorderColor(RGB c) {
    borderColor = c;
}

RGB BorderedImage::getBorderColor() {
    return borderColor;
}

SimpleImage BorderedImage::addBorder(const SimpleImage& image) {
    int width = image.getWidthInColumns();
    cout << width << endl;
    int height = image.getHeightInRows();
    cout << height << endl;

    SimpleImage newImage(height + 2 * borderWidth, width + 2 * borderWidth);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            //void setPixel(int row, int column,
            //unsigned char r, unsigned char g, unsigned char b);
            newImage.setPixel(j + borderWidth, i + borderWidth,
                image.getPixel(j, i).rgb.red, image.getPixel(j, i).rgb.green,
                image.getPixel(j, i).rgb.blue);
        }
    }
    //Now we set the border pixels
    for (int i = 0; i < width + 2 * borderWidth; i++) {
        for (int j = 0; j < height + 2 * borderWidth; j++) {
            if (j < borderWidth || j >= height + borderWidth || i < borderWidth || i >= width + borderWidth) {
                newImage.setPixel(j, i, borderColor.red, borderColor.green, borderColor.blue);
            }
        }

    } return newImage;
}

SimpleImage BorderedImage::addAvgRowBorder(const SimpleImage& image) {
    int width = image.getWidthInColumns();
    int height = image.getHeightInRows();
    //create a new image to store the result with its border
    SimpleImage newImage(width + 2 * borderWidth, height + 2 * borderWidth);
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            Pixel p = image.getPixel(col, row);
            newImage.setPixel(col + borderWidth, row + borderWidth, p.rgb.red,p.rgb.green,p.rgb.blue);
        }
    }

    for (int i = 0; i < height + 2 * borderWidth; i++) {
        for (int j = borderWidth; j < width + 2 * borderWidth; j++) {

            if (j < borderWidth || j >= width + borderWidth || i < borderWidth || i >= height + borderWidth) {
                newImage.setPixel(j, i, borderColor.red, borderColor.green, borderColor.blue);
            }
        }

    }

    for (int i = 0; i < height + 2 * borderWidth; i++) {
        for (int j = borderWidth; j < width + 2 * borderWidth; j++) {

            if (j < borderWidth || j >= width + borderWidth || i < borderWidth || i >= height + borderWidth) {
                newImage.setPixel(j, i, borderColor.red, borderColor.green, borderColor.blue);
            }
        }

    }

}

//STOP at avgRowBorder