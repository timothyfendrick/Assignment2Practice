//
// Created by timot on 3/17/2025.
//

#include <cmath>
#include "LineDetectedImage.h"
#include <iostream>
#include <vector>

using namespace std;

LineDetectedImage::LineDetectedImage(int r, int dt) {
    radius = r;
    detectionThreshold = dt;
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

    int rows = original.getHeightInRows();
    int cols = original.getWidthInColumns();
    SimpleImage newImage = original;

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(col != 0 && col != cols - 1) {

                if(row != 0 && row != rows - 1) {
                    if(col != 0 && col != cols - 1) {
                        vector <vector <Pixel>> pixelGrid(3);
                    createGrid(pixelGrid, newImage, row, col);

                    //Checking pixel for vertical line
                    //pixelGrid[1][1] is center pixel
                    Pixel pC = pixelGrid[1][1];
                    for(int i = 0; i < sizeof(pC.rgb.rgbV); i++) {
                        for(int rowGrid = 0; rowGrid < pixelGrid.size(); rowGrid++) {
                            for(int colGrid = 0; colGrid < pixelGrid[row].size(); colGrid++) {
                                //Checking if pI is going to be the center pixel
                                if(rowGrid != 1 && colGrid != 1) {
                                    Pixel pI = pixelGrid[rowGrid][colGrid];
                                    Pixel pCompare; //Initializing pCompare so it can be used in set in the first loop and used in the second for loop
                                    //cI is colorIndex, the color in rgbV we are looking at
                                    for(int cI; cI < sizeof(pI.rgb.rgbV); cI++) {
                                        //Checking if pixel is a different color then the center pixel
                                        if(abs(pI.rgb.rgbV[cI] - pC.rgb.rgbV[cI]) >= detectionThreshold) {
                                            int rOpp = rowGrid;
                                            int colOpp = colGrid;
                                            findOpposite(rOpp, colOpp);
                                            //pCompare is the opposite pixel of pI
                                            pCompare = pixelGrid[rOpp][colOpp];
                                            break;
                                        }
                                    }
                                    for(int cI; cI < sizeof(pI.rgb.rgbV); cI++) {
                                        //Checking if oppositePixel is also different than centerPixel
                                        if(abs(pCompare.rgb.rgbV[cI] - pC.rgb.rgbV[cI]) >= detectionThreshold) {
                                            //Set center Pixel to black
                                            newImage.setPixel(row, col, 0, 0, 0);
                                            break;
                                        }
                                    }
                                }


                            }

                    }
                    }
                        // if(pL.rgb.rgbV[i] == pR.rgb.rgbV[i] && pI.rgb.rgbV[i] != pR.rgb.rgbV[i]) {
                        //     newImage.setPixel(row, col, 0,0,0);
                        //     break;
                        // }
                    }
                    // for(vector <Pixel>& pRow: pixelGrid) {
                    //     for(Pixel p: pRow) {
                    //         p.printPixel();
                    //     }
                    // }
                }



                // Pixel pL = original.getPixel(row, col - 1);
                // Pixel pI = original.getPixel(row, col);
                // Pixel pR = original.getPixel(row, col + 1);
                // vector <Pixel> pixelVector;
                // pixelVector.push_back(pL);
                // pixelVector.push_back(pI);
                // pixelVector.push_back(pR);
                //
                //
                // for(int i = 0; i < sizeof(pI.rgb.rgbV); i++) {
                //     if(pL.rgb.rgbV[i] == pR.rgb.rgbV[i] && pI.rgb.rgbV[i] != pR.rgb.rgbV[i]) {
                //         newImage.setPixel(row, col, 0,0,0);
                //         break;
                //     }
                // }
                // if((pL.rgb.red == pR.rgb.red) && (pI.rgb.red != pR.rgb.red)) {
                //     cout << row << " " << col << " ";
                //     for (Pixel p : pixelVector) {
                //         cout << (int) (p.rgb.red) << " ";
                //     }
                //     cout << endl;
                //     newImage.setPixel(row, col, 0,0,0);
                // }
            }
        }
    }

    return newImage;

    {
        // for(int row = 0; row < rows; row++) {
    //     for(int col = 0; col < cols; col++) {
    //         //Checking Diagnol
    //         if(row != rows && col != cols) {
    //             Pixel p1 = original.getPixel(row, col);
    //             Pixel p2 = original.getPixel(row + 1, col + 1);
    //             if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
    //                 if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
    //                     if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
    //                         newImage.setPixel(row,col,255,255,255);
    //                         newImage.setPixel(row + 1,col + 1,255,255,255);
    //                         break;
    //                     }
    //                 }
    //             }
    //             newImage.setPixel(row,col,0,0,0);
    //             newImage.setPixel(row + 1,col + 1,0,0,0);
    //         }
    //         //Checking Up n DOwn
    //         if(row != rows) {
    //             Pixel p1 = original.getPixel(row, col);
    //             Pixel p2 = original.getPixel(row + 1, col);
    //             if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
    //                 if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
    //                     if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
    //                         newImage.setPixel(row,col,255,255,255);
    //                         newImage.setPixel(row + 1,col,255,255,255);
    //                         break;
    //                     }
    //                 }
    //             }
    //             newImage.setPixel(row,col,0,0,0);
    //             newImage.setPixel(row + 1,col,0,0,0);
    //         }
    //         //Checking Side to side
    //         if(col != cols) {
    //             Pixel p1 = original.getPixel(row, col);
    //             Pixel p2 = original.getPixel(row, col + 1);
    //             if(abs(p1.rgb.red - p2.rgb.red) < detectionThreshold) {
    //                 if(abs(p1.rgb.green - p2.rgb.green) < detectionThreshold) {
    //                     if(abs(p1.rgb.blue - p2.rgb.blue) < detectionThreshold) {
    //                         newImage.setPixel(row,col,255,255,255);
    //                         newImage.setPixel(row,col + 1,255,255,255);
    //                         break;
    //                     }
    //                 }
    //             }
    //             newImage.setPixel(row,col,0,0,0);
    //             newImage.setPixel(row,col + 1,0,0,0);
    //         }
    //
    //     }
    // }
    //    return newImage;
    }

}

void LineDetectedImage::createGrid(vector <vector <Pixel>> &pixelGrid, SimpleImage &image, int row, int col) {
    int colInit = row;

    //Moves to top left of grid
    row -= 1;
    col -= 1;

    //Loops through rows and then adds pixel in each col to pixelGrid
    for(row; row < pixelGrid.size(); row++) {
        //Establishes size of pixelGrid for lop
        int size = colInit + 2;
        for(col; col < size; col++) {
            pixelGrid[row].push_back(image.getPixel(row, col));
            cout << "Grid: " << row << " " << col << endl;
        }
        cout << endl;
        //Resets col to start
        col = colInit - 1;

    }
}

void LineDetectedImage::findOpposite(int &cRow, int &cCol) {
    if(cRow == 0) {
        cRow = 2;
    }else if(cRow == 2) {
        cRow = 0;
    }

    if(cCol == 0) {
        cCol = 2;
    }else if(cCol == 2) {
        cCol = 0;
    }
}