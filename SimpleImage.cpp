#include "SimpleImage.h"
#include <iostream>
#include <fstream>

using namespace std;

SimpleImage::SimpleImage(int numRows, int numCols) 
{
    pixels.resize(numRows);

    for(int r = 0;r < pixels.size();r++) {
        for(int c = 0;c < numCols;c++) {
            Pixel newPixel;
            newPixel.row = r;
            newPixel.column = c;

            pixels[r].push_back(newPixel);
        }
    }
}
//--
SimpleImage::SimpleImage(string bmpFilePath) 
{
    readBMPFile(bmpFilePath);
}
//--
int SimpleImage::getHeightInRows() const
{
    return pixels.size();
}
//--
int SimpleImage::getWidthInColumns() const
{
    int retVal = 0;
    if(getHeightInRows() > 0)
    {
        retVal = pixels[0].size();
    }
    return retVal;
}
//--
int SimpleImage::getNumberOfPixels() const
{
    return getHeightInRows() * getWidthInColumns();
}
//--
bool SimpleImage::isPixelInBounds(int row, int column) const
{
    bool retVal = false;
    //the row and col must be non-negative and less than the height and width
    if(row >= 0 && row < getHeightInRows() && column >= 0 && column < getWidthInColumns())
    {
        retVal = true;
    }
    return retVal;
}
//--
Pixel SimpleImage::getPixel(int row, int column) const
{
    //default pixel w/ invalid row/column values
    Pixel retVal {.row = -1, .column = -1};

    if(isPixelInBounds(row, column))
    {
        retVal = pixels[row][column];
    }
    else
    {
        cout<<"Outside the bounds of the image: (row "<<row<<", column "<<column<<")"<<endl;
    }

    return retVal;
}
//--
void SimpleImage::setPixel(int row, int column, unsigned char r, unsigned char g, unsigned char b)
{
    //check the bounds
    if(isPixelInBounds(row, column))
    {
        pixels[row][column].rgb.red = r;
        pixels[row][column].rgb.green = g;
        pixels[row][column].rgb.blue = b;
    }
    else
    {
        cout<<"Outside the bounds of the image: (row "<<row<<", column "<<column<<")"<<endl;
    }
}
//--
vector < Pixel > SimpleImage::getAllPixels() const
{
    vector < Pixel > allPixels;

    int numRows = getHeightInRows();
    int numCols = getWidthInColumns();

    for(int r = 0;r < numRows;r++)
    {
        for(int c = 0;c < numCols;c++)
        {
            allPixels.push_back(pixels[r][c]);
        }
    }

    return allPixels;
}
//--
void SimpleImage::setAllPixels(const vector < Pixel >& allPixels)
{
    for(int i = 0;i < allPixels.size();i++)
    {
        Pixel p = allPixels[i];
        pixels[p.row][p.column] = allPixels[i];
    }
}
//--
void SimpleImage::writeBMPFile(string bmpFilePath) const
{
    //get the number of rows and columns
    int numRows = getHeightInRows();
    int numCols = getWidthInColumns();

    //if there is at least one row and column
    if(numRows > 0 && numCols > 0)
    {
        //open the file
        ofstream outFile;
        outFile.open(bmpFilePath, ios::binary);

        //if the file can be opened
        if(outFile.good())
        {
            //calculate the number of padding bytes
            int paddingBytesPerRow = getNumberOfPaddingBytesPerRow();

            //calculate the amount of pixel data (non-header)
            int pixelDataSize = numRows * ((numCols * 3) + paddingBytesPerRow);

            //calculate the size of the entire file
            int fileSize = 54 + pixelDataSize;

            //write the vector of pixels to a file in bitmap format
            //BM
            outFile.write("BM", 2);
            //file size
            convertTo4ByteLittleEndian(fileSize, outFile);
            //4 unused 0's
            convertTo4ByteLittleEndian(0, outFile);
            //offset to data 54 (40 + 14)
            convertTo4ByteLittleEndian(54, outFile);
            //size of the header
            convertTo4ByteLittleEndian(40, outFile);
            //width- number of columns
            convertTo4ByteLittleEndian(numCols, outFile);
            //height- number of rows
            convertTo4ByteLittleEndian(numRows, outFile);
            //number of color planes
            convertTo2ByteLittleEndian(1, outFile);
            //number of bits per pixel
            convertTo2ByteLittleEndian(24, outFile);
            //compression method
            convertTo4ByteLittleEndian(0, outFile);
            //image size
            convertTo4ByteLittleEndian(pixelDataSize, outFile);
            //horizontal/vert resolution
            convertTo4ByteLittleEndian(2835, outFile);
            convertTo4ByteLittleEndian(2835, outFile);
            //number of colors in the palette
            convertTo4ByteLittleEndian(0, outFile);
            //number of important colors
            convertTo4ByteLittleEndian(0, outFile);

            //pixel data in bottom-up order, BGR order, with padding
            for(int r = numRows - 1;r >= 0;r--)
            {
                //add the row of pixel data
                for(int c = 0;c < numCols;c++)
                {
                    RGB rgb = pixels[r][c].rgb;
                    outFile.put(rgb.blue);
                    outFile.put(rgb.green);
                    outFile.put(rgb.red);
                }

                //add the padding (if there is any)
                for(int i = 0; i < paddingBytesPerRow; i++)
                {
                    outFile.put((unsigned char)0);
                }
            }

            //close the file
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file " << bmpFilePath << endl;
        }
    }
}
//--
void SimpleImage::readBMPFile(string bmpFilePath)
{
    //open the file
    ifstream inFile;
    inFile.open(bmpFilePath, ios::binary);

    //if the file can be opened
    if(inFile.good())
    {
        //read the header
        char header[54];
        inFile.read(header, 54);

        //get the width
        int numCols = 0;
        for(int i = 0;i < 4;i++)
        {
            unsigned char aByte = (unsigned char)header[18 + i];
            numCols += int(aByte) << (i * 8);
        }

        //get the height
        int numRows = 0;
        for(int i = 0;i < 4;i++)
        {
            unsigned char aByte = (unsigned char)header[22 + i];
            numRows += int(aByte) << (i * 8);
        }

        //if the height is positive then the rows are stored bottom-to-top
        //if the height is negative then the rows are stored top-to-bottom
        bool rowsBottomUp = true;
        if(numRows < 0)
        {
            numRows = -numRows;
            rowsBottomUp = false;
        }

        //update the vector of pixels to match the size of the image
        pixels.resize(numRows);
        for(int i = 0;i < numRows;i++)
        {
            pixels[i].resize(numCols);
        }

        //calculate the number of padding bytes
        int paddingBytesPerRow = getNumberOfPaddingBytesPerRow();

        //calculate the amount of pixel data (non-header)
        int pixelDataSize = numRows * ((numCols * 3) + paddingBytesPerRow);

        //read the pixel data
        char* pixelData = new char[pixelDataSize];
        inFile.read(pixelData, pixelDataSize);
        int pixelDataIndex = 0;

        //rows are stored bottom up
        if(rowsBottomUp)
        {
            for (int r = numRows - 1; r >= 0; r--) {
                for (int c = 0; c < numCols; c++) {
                    RGB rgb;
                    rgb.blue = (unsigned char) pixelData[pixelDataIndex];
                    rgb.green = (unsigned char) pixelData[pixelDataIndex + 1];
                    rgb.red = (unsigned char) pixelData[pixelDataIndex + 2];
                    rgb.updateArray();

                    pixels[r][c].rgb = rgb;
                    pixels[r][c].row = r;
                    pixels[r][c].column = c;

                    pixelDataIndex += 3;
                }
                //skip the padding
                pixelDataIndex += paddingBytesPerRow;
            }
        }
        else //rows are stored top to bottom
        {
            for (int r = 0; r < numRows; r++) {
                for (int c = 0; c < numCols; c++) {
                    RGB rgb;
                    rgb.blue = (unsigned char) pixelData[pixelDataIndex];
                    rgb.green = (unsigned char) pixelData[pixelDataIndex + 1];
                    rgb.red = (unsigned char) pixelData[pixelDataIndex + 2];

                    pixels[r][c].rgb = rgb;
                    pixels[r][c].row = r;
                    pixels[r][c].column = c;

                    pixelDataIndex += 3;
                }
                //skip the padding
                pixelDataIndex += paddingBytesPerRow;
            }
        }
        //free the memory
        delete [] pixelData;

        //close the file
        inFile.close();
    }
    else
    {
        cout << "Error: Unable to open file " << bmpFilePath << endl;
    }
}
//--
void SimpleImage::convertTo4ByteLittleEndian(int num, ofstream& outFile) const
{
    outFile.put((unsigned char)(num & 0x000000FF));
    outFile.put((unsigned char)((num & 0x0000FF00) >> 8));
    outFile.put((unsigned char)((num & 0x00FF0000) >> 16));
    outFile.put((unsigned char)((num & 0xFF000000) >> 24));
}
//--
void SimpleImage::convertTo2ByteLittleEndian(int num, ofstream& outFile) const
{
    outFile.put((unsigned char)(num & 0x000000FF));
    outFile.put((unsigned char)((num & 0x0000FF00) >> 8));
}
//--
int SimpleImage::getNumberOfPaddingBytesPerRow() const
{
    int numCols = getWidthInColumns();
    //default to no padding
    int paddingBytesPerRow = 0;
    //if the number of pixel bytes is not a multiple of 4
    if(((numCols * 3) % 4) != 0)
    {
        //set the padding to sum up to a multiple of 4
        paddingBytesPerRow = 4 - ((numCols * 3) % 4);
    }
    return paddingBytesPerRow;
}