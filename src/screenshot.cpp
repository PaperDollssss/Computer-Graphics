#include "texture_mapping.h"

// WriteBitmapFile
// according to the RGB data in bitmapData, save to bitmap
// filename is the filename will be saved
bool WriteBitmapFile(char *filename, int width, int height, unsigned char *bitmapData)
{
    // fill BITMAPFILEHEADER
    BITMAPFILEHEADER bitmapFileHeader;
    memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
    bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
    bitmapFileHeader.bfType = 0x4d42;
    bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // fill BITMAPINFOHEADER
    BITMAPINFOHEADER bitmapInfoHeader;
    memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = width;
    bitmapInfoHeader.biHeight = height;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 24;
    bitmapInfoHeader.biCompression = BI_RGB;
    bitmapInfoHeader.biSizeImage = width * abs(height) * 3;

    FILE *filePtr; // connect the bitmap file will be saved
    unsigned char tempRGB;
    unsigned int imageIdx;

    // change the position of R and B, because in bitmap is BGR but in memory is RGB
    for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
    {
        tempRGB = bitmapData[imageIdx];
        bitmapData[imageIdx] = bitmapData[imageIdx + 2];
        bitmapData[imageIdx + 2] = tempRGB;
    }

    if (fopen_s(&filePtr, filename, "wb"))
        return false;

    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);

    fclose(filePtr);
    return true;
}

// SaveScreenShot
void SaveScreenShot(int width, int height)
{
    const int windowsWidth = width, windowsHeight = height;
    const int len = windowsWidth * windowsHeight * 3;
    static void *screenData;
    screenData = malloc(len);
    memset(screenData, 0, len);
    glReadPixels(0, 0, windowsWidth, windowsHeight, GL_RGB, GL_UNSIGNED_BYTE, screenData);

    // create file name by time
    time_t tm = 0;
    tm = time(NULL);
    char lpstrFilename[256] = {0};
    sprintf_s(lpstrFilename, sizeof(lpstrFilename), "screenshot %Id.bmp", tm);

    WriteBitmapFile(lpstrFilename, windowsWidth, windowsHeight, (unsigned char *)screenData);

    free(screenData);
}