#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <stdlib.h>
#include <Windows.h>
#include <ctime>

#include <highgui.h>
#include <cv.h>

using namespace cv;
using namespace std;

bool exists(char* filePath)
{
	//This will get the file attributes bitlist of the file
	DWORD fileAtt = GetFileAttributesA(filePath);

	//If an error occurred it will equal to INVALID_FILE_ATTRIBUTES
	if(fileAtt == INVALID_FILE_ATTRIBUTES)
		//So lets throw an exception when an error has occurred
		throw GetLastError();

	//If the path referers to a directory it should also not exists.
	return ( ( fileAtt & FILE_ATTRIBUTE_DIRECTORY ) == 0 ); 
}

char* get_name(char* filepath)
{
	char *newfilepath;
	char *_drive = NULL;
	char *_dir = NULL;
	char *_fname = NULL;
	char *_ext = NULL;	
	srand(time_t(NULL));

	newfilepath = filepath;
	for (int i = 0; i < 10000; i++)
	{
		_splitpath(newfilepath, _drive, _dir, _fname, _ext);
		_fname += rand() % i + 20;
		newfilepath = _drive + *_dir + *_fname + *_ext;
		if (exists(newfilepath) == false)
			break;
	}
	return newfilepath;
}

int main(int argc, const char** argv)
{
	/*FILE *input;
	uchar *data = NULL;

	input = fopen("D:\\saveimage.bmp", "rb");
	fseek(input, 0, SEEK_END);
	long int count = ftell(input);
	rewind(input);
	data = (uchar*)malloc(sizeof(uchar)*count);
	fread(data, 1, count, input);*/

	/*Size size = Size(384, 288); 
	int depth  = IPL_DEPTH_32F; 
	int channels = 3; 
	Mat *frame =  CreateImageHeader(size, depth, channels);
	frame->imageData = data;
	cvNamedWindow("win1", 1);
	cvShowImage("win1", frame);*/
	///////////////////////////////////////////////////////////////////////////////////////////
	
	/*Mat img(Size(384, 288), CV_8UC1, data);
	imwrite(get_name("D:\учёба\C, C++, C#\\UsingOpenCV\\frames\\image.jpg"), img);
	namedWindow("image", 1);
	imshow("image", img);
	waitKey(0);*/
	///////////////////////////////////////////////////////////////////////////////////////////
	/*Mat img(Size(384, 288), CV_8UC3, data);
	cvtColor(img, img2, CV_GRAY2BGR);
	namedWindow("image", 1);
	imshow("image", img);*/
	///////////////////////////////////////////////////////////////////////////////////////////
	/*CvMat Mat = cvMat(1, 1, CV_8UC1, data);
	IplImage *img = cvDecodeImage(&Mat);

	cvNamedWindow("win1", CV_WINDOW_AUTOSIZE);
	cvShowImage("win1", img);
	cvWaitKey(10);

	cvReleaseImageHeader(&img);
	cvDestroyWindow("win1");*/


	///////////////////////////////////////////////////////////////////////////////////////////
	/*int channels = 1; 
	IplImage* cv_image;
	IplImage *pIm = NULL;
	uchar *data;
	int wid;
	int hei;


	cv_image = cvLoadImage("D:\\saveimage2.bmp", 1);
	if (!cv_image)
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
        return -1;
	}

	data = (uchar*)cv_image->imageData;
	wid = cv_image->width;
	hei = cv_image->height;

	pIm = cvCreateImageHeader(cvSize(wid, hei), IPL_DEPTH_8U, 1);
	cvSetData(pIm, cv_image, wid);

	cvNamedWindow("win1", CV_WINDOW_AUTOSIZE);
	cvShowImage("win1", pIm);
	cvWaitKey(10);

	cvReleaseImageHeader(&pIm);
	cvDestroyWindow("win1");*/

	///////////////////////////////////////////////////////////////////////////////////////////
	Mat img = imread("D:\\картинки\\galstuk.jpg");

	if (img.empty())
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
          return -1;
     }

	FILE *output;
	output = fopen("buffer.dat", "wb");
	fwrite(img.data, sizeof(unsigned char), img.rows * img.cols, output);
	fclose(output);

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
    imshow("MyWindow", img);
    waitKey(0);

    destroyWindow("MyWindow");

	return 0;
}