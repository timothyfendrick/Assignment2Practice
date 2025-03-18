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

    int radius;

    int detectionThreshold;

};