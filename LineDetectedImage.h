//
// Created by timot on 3/17/2025.
//

#pragma once

#include "SimpleImage.h"



class LineDetectedImage{

public:

    LineDetectedImage(int r, int dt);



    int getRadius();

    void setRadius(int r);



    int getDetectionThreshold();

    void setDetectionThreshold(int dt);



    SimpleImage detectLine(const SimpleImage& original);

private:

    void createGrid(vector <vector <Pixel>> &pixelGrid, SimpleImage &image, int row, int col);
    void findOpposite(int &cRow, int &cCol);
    int radius;

    int detectionThreshold;

};