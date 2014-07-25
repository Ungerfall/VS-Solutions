#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MAXCHANNELS 4

#include "FrameRequestHandler.h"
#include <highgui.h>
#include <cv.h>
#include <megalib1.h>
#include "dirent.h"
#include "Poco\DateTime.h"

using namespace cv;

extern std::vector<unsigned char> CurrentFrame;

void InitCamera();
void GetFrame();
void LibRun(UINT*, int);
void CreateHttpResponse(std::string, std::string);
bool ReadWholeDirectory(std::string);
void NextFrame();