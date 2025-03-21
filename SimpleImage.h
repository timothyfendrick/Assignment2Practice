#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
using namespace std;

struct RGB
{
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
    unsigned char rgbV[3]  = {red, green, blue};

    void updateArray() {
        rgbV[0] = red;
        rgbV[1] = green;
        rgbV[2] = blue;
    }

    void printRGB() {
        cout << "RGB: " << (int) (red) << ", " << (int) (green) << ", " << (int) (blue) << endl;
    }
};

struct Pixel
{
    RGB rgb;
    int row = -1;
    int column = -1;

    void printPixel() {
        cout << "Row: " << row << " Column: " << column << " ";
        rgb.printRGB();
    }
};

class SimpleImage
{
public:
    SimpleImage(int numRows, int numCols);
    SimpleImage(string bmpFilePath);

    int getHeightInRows() const;
    int getWidthInColumns() const;
    int getNumberOfPixels() const;

    Pixel getPixel(int row, int column) const;
    void setPixel(int row, int column, unsigned char r, unsigned char g, unsigned char b);

    vector < Pixel > getAllPixels() const;
    void setAllPixels(const vector < Pixel >& allPixels);
    
    void writeBMPFile(string bmpFilePath) const;
    void readBMPFile(string bmpFilePath);
private:
    vector < vector < Pixel > > pixels;

    bool isPixelInBounds(int row, int column) const;

    void convertTo4ByteLittleEndian(int num, ofstream& outFile) const;
    void convertTo2ByteLittleEndian(int num, ofstream& outFile) const;
    int getNumberOfPaddingBytesPerRow() const;
};