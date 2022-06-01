//
// Created by weichen on 2022/6/1
//
#ifndef FINAL_PROJECT_SRC_SCREENSHOT_H_
#define FINAL_PROJECT_SRC_SCREENSHOT_H_

// WriteBitmapFile
bool WriteBitmapFile(char *filename, int width, int height, unsigned char *bitmapData);

// SaveScreenShot
void SaveScreenShot(int width, int height);

#endif