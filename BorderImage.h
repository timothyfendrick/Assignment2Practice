//
// Created by Elizabeth Zak on 3/6/25.
//

//BorderedImage.h

#pragma once

#include "SimpleImage.h"



using namespace std;



class BorderedImage

{

public:
    //If only a width is provided, this is the constructer for BorderedImage
    BorderedImage(int w);
    //If a color is provided, this is the constructor for BorderedImage
    BorderedImage(int w, RGB c);


    //Our setter sets the width of the border using w
    //Our getter returns the width of the border
    void setBorderWidth(int w);

    int getBorderWidth();


    //Our setter sets the color
    //Our getter returns the color
    void setBorderColor(RGB c);

    RGB getBorderColor();



    //generate a new SimpleImage that has a border

    SimpleImage addBorder(const SimpleImage& image);



    //get the average RGB of every row and make the border from each avg

    SimpleImage addAvgRowBorder(const SimpleImage& image);

private:

    int borderWidth;

    RGB borderColor;

};