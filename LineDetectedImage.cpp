//
// Created by timot on 3/17/2025.
//

#include <cmath>
#include "LineDetectedImage.h"

LineDetectedImage::LineDetectedImage(int r, int dt) {

}

int LineDetectedImage::getRadius() {
    return radius;
}

void LineDetectedImage::setRadius(int r) {
    radius = r;
}

int LineDetectedImage::getDetectionThreshold() {
    return detectionThreshold;
}

void LineDetectedImage::setDetectionThreshold(int t) {
    detectionThreshold = t;
}

SimpleImage LineDetectedImage::detectLine(const SimpleImage& original) {
    SimpleImage newImage = original;
    int rows = original.getHeightInRows();
    int cols = original.getWidthInColumns();
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            //Checking Diagnol
            if(row != rows && col != cols) {
                Pixel p1 = original.getPixel(row, col);
                Pixel p2 = original.getPixel(row + 1, col + 1);
                if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
                    if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
                        if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
                            newImage.setPixel(row,col,255,255,255);
                            newImage.setPixel(row + 1,col + 1,255,255,255);
                            break;
                        }
                    }
                }
                newImage.setPixel(row,col,0,0,0);
                newImage.setPixel(row + 1,col + 1,0,0,0);
            }
            //Checking Up n DOwn
            if(row != rows) {
                Pixel p1 = original.getPixel(row, col);
                Pixel p2 = original.getPixel(row + 1, col);
                if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
                    if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
                        if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
                            newImage.setPixel(row,col,255,255,255);
                            newImage.setPixel(row + 1,col,255,255,255);
                            break;
                        }
                    }
                }
                newImage.setPixel(row,col,0,0,0);
                newImage.setPixel(row + 1,col,0,0,0);
            }
            //Checking Side to side
            if(col != cols) {
                Pixel p1 = original.getPixel(row, col);
                Pixel p2 = original.getPixel(row, col + 1);
                if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
                    if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
                        if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
                            newImage.setPixel(row,col,255,255,255);
                            newImage.setPixel(row,col + 1,255,255,255);
                            break;
                        }
                    }
                }
                newImage.setPixel(row,col,0,0,0);
                newImage.setPixel(row,col + 1,0,0,0);
            }

        }
    }
    return newImage;
}