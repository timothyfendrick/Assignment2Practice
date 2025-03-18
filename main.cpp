#include <iostream>
#include "SimpleImage.h"
#include "BorderImage.h"
#include "LineDetectedImage.h"

using namespace std;

void grayImage(string sourceBmpFilePath, string destinationBmpFilePath);
void flipHorizontal(string sourceBmpFilePath, string destinationBmpFilePath);
void redImage(string sourceBmpFilePath, string destinationBmpFilePath);

int main()
{

    string originalImageFilePath = "bmp-example-file-download-500x500.bmp";

    string resultFilePath = "result.bmp";

    string copyFilePath = "copy.bmp";

    SimpleImage originalImage(originalImageFilePath);
    SimpleImage resultImage(1,1);
    SimpleImage copyImage = originalImage;

    BorderedImage borderImage(100, RGB {0,0,0});

    resultImage = borderImage.addBorder(originalImage);

    resultImage.writeBMPFile(resultFilePath);
    copyImage.writeBMPFile(copyFilePath);

    // THIS SHIT WORKS
    // string redImageFilePath = "redImage.bmp";
    // string redImageWBFilePath = "redImageWBorder.bmp";
    //
    // SimpleImage redImage(redImageFilePath);
    // SimpleImage redImageWB(1,1);
    //
    // BorderedImage borderImage(2, RGB {0,0,0});
    //
    // redImageWB = borderImage.addBorder(redImage);
    //
    // redImageWB.writeBMPFile(redImageWBFilePath);

    // SimpleImage img1("C:/Users/timot/OneDrive/Documents/BMP/snail.bmp");
    //
    // SimpleImage img2("C:/Users/timot/OneDrive/Documents/BMP/result.bmp");
    //
    //
    //
    // LineDetectedImage lineDetectionImage(1, 220);
    //
    // SimpleImage withLines1 = lineDetectionImage.detectLine(img1);
    //
    // withLines1.writeBMPFile("C:/Users/timot/OneDrive/Documents/BMP/result.bmp");
    //
    //
    //
    // SimpleImage withLines2 = lineDetectionImage.detectLine(img2);
    //
    // withLines2.writeBMPFile("/path/to/img2.bmp");

    // string destinationFilePath = "snail.bmp";
    // string filePath = "sample1.bmp";
    // BorderedImage newBorderImage(2);
    //
    // SimpleImage originalImage(filePath);
    //
    // SimpleImage borderedImage(destinationFilePath);
    //
    // borderedImage = newBorderImage.addBorder(originalImage);
    //
    // borderedImage.writeBMPFile(destinationFilePath);

    // SimpleImage testImage(10,10);
    //
    // Pixel redPix{.rgb{.red = 255, .green = 0, .blue = 0}, .row = -1, .column = -1};
    //
    // for(int row = 0; row < testImage.getHeightInRows(); row++) {
    //     for(int col = 0; col < testImage.getWidthInColumns(); col++) {
    //         testImage.setPixel(row, col, redPix.rgb.red, redPix.rgb.green, redPix.rgb.blue);
    //     }
    // }

    // cout<<"Simple Image Example"<<endl;
    // redImage("C:/Users/timot/OneDrive/Documents/BMP/snail.bmp", "C:/Users/timot/OneDrive/Documents/BMP/result.bmp");
    // //flipHorizontal("", "");
    // return 0;
}
//--
void grayImage(string sourceBmpFilePath, string destinationBmpFilePath)
{
    SimpleImage source(sourceBmpFilePath);
    SimpleImage destination(source.getHeightInRows(), source.getWidthInColumns());

    vector < Pixel > allPixels = source.getAllPixels();

    for(int i = 0;i < allPixels.size();i++)
    {
        Pixel p = allPixels[i];
        int avgPixelColor = (p.rgb.red + p.rgb.green + p.rgb.blue) / 3;

        p.rgb.red = avgPixelColor;
        p.rgb.green = avgPixelColor;
        p.rgb.blue = avgPixelColor;

        allPixels[i] = p;
    }

    destination.setAllPixels(allPixels);
    destination.writeBMPFile(destinationBmpFilePath);
}
void redImage(string sourceBmpFilePath, string destinationBmpFilePath)
{
    SimpleImage source(sourceBmpFilePath);
    SimpleImage destination(source.getHeightInRows(), source.getWidthInColumns());

    vector < Pixel > allPixels = source.getAllPixels();

    for(int i = 0;i < allPixels.size();i++)
    {
        Pixel p = allPixels[i];
        int redtoadd = p.rgb.red;
        if (p.rgb.red + redtoadd < 255) {
            p.rgb.red += redtoadd;
        } else {
         p.rgb.red = 255;
        }


        allPixels[i] = p;
    }

    destination.setAllPixels(allPixels);
    destination.writeBMPFile(destinationBmpFilePath);
}


//--
void flipHorizontal(string sourceBmpFilePath, string destinationBmpFilePath)
{
    SimpleImage source(sourceBmpFilePath);
    SimpleImage destination(source.getHeightInRows(), source.getWidthInColumns());

    vector < Pixel > allPixels = source.getAllPixels();

    for(int i = 0;i < allPixels.size();i++)
    {
        Pixel p = allPixels[i];
        p.column = (source.getWidthInColumns() - 1) - p.column;
        allPixels[i] = p;
    }

    destination.setAllPixels(allPixels);
    destination.writeBMPFile(destinationBmpFilePath);
}

// RGB color = RGB(210, 0, 0);
// int intTotal = 0;
// int output = color.red;
// intTotal += color.red;
// cout << color.red << endl;
// cout << output << endl;
// cout << intTotal << endl;
// color.red += 100;
// output = color.red;
// intTotal += 100;
// cout << color.red << endl;
// cout << output << endl;
// cout << intTotal << endl;