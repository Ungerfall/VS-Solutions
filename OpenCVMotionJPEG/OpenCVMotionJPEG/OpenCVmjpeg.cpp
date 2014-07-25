#include "OpenCVmjpeg.h"

//size
const int WIDTH = 384;
const int HEIGHT = 288;

HDEVICE Hdv[2];
UINT NumberDevices;
TCHANNELPROPERTY CProp;
TDEVICEPROPERTY DProp;
UINT MaxChannels = 0;
void *SaveImage[MAXCHANNELS];

std::vector<unsigned char> CurrentFrame;

//инициализаци€ устройства
void InitCamera()
{
	_MPCreate();
	Hdv[0] = _IDAdd("C:\\Program Files\\MegaPixel Products\\MegaLib V1.2\\DEVICE\\MegaFrame4.DLL",0);
	_CHStart(0,1);

	_MDSetProperty(Hdv[0], WIDTH, HEIGHT, SQUARE_PIXELS);
	_MDSetProperty(Hdv[0], WIDTH, HEIGHT, SQUARE_PIXELS);
	NumberDevices = _IDGetNumberDevices();
	for(UINT dv = 0; dv < NumberDevices; dv++)
	{
		_IDGetDeviceProperty(Hdv[dv], &DProp);
		for(UINT i = 0; i < DProp.NumberChannels; i++)
		{
			_IDGetChannelProperty(Hdv[dv], i, &CProp);
			UINT cl;
			if(CProp.ColorCode == MAKEFOURCC('G','R','A','Y')) cl = 1;
			if(CProp.ColorCode == MAKEFOURCC('R','G','B',' ')) cl = 3;
			if(CProp.ColorCode == MAKEFOURCC('U','Y','V','Y')) cl = 2;
			if(CProp.ColorCode == MAKEFOURCC('Y','U','Y','2')) cl = 2;
			char *sit = new char[CProp.HorFrameSize * CProp.VerFrameSize * cl + 256];
			SaveImage[MaxChannels] = (PVOID)((UINT)(sit + 0x100) & 0xffffff00);
			MaxChannels++;
		}
	}
}

void GetFrame()
	{
		setlocale(LC_ALL, "Russian");
		while (1)
		{
			UINT MaxChannels;
			UINT *ImgTegg;
			bool check = false;
			int j = 0;
			while (!check)
			{
				MaxChannels = _IDGetMaxChannels();
				ImgTegg = new UINT [MaxChannels];
				_CHGetPicture(ImgTegg, SaveImage);
				for(UINT i = 0; i < MaxChannels; i++)
				{
					switch(ImgTegg[i])
					{
						case NOPICTURE : break;
						case PICTUREREADY : 
							LibRun(&i, j); 
							check = true; 
							break;
						case INPUTUNCONNECTED : break;
					}
				}
				delete ImgTegg;
				j++;
				//printf_s(" адр получен");
			}
		}
}

bool ReadWholeDirectory(std::string dirname)
{
	bool check = false;
	DIR *dir;
	struct dirent *ent;
	std::vector<int> params;
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(85);
	if ((dir = opendir (dirname.c_str())) != NULL)
	{
		int i = 0;
		while (1)
		{
			if ((ent = readdir(dir)) == NULL)
				rewinddir(dir);
			else
			{
				std::string filename = dirname + "\\" + std::string(ent->d_name);
				Mat img = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
				if (img.empty() == false)
				{
					cv::putText(img, std::to_string(i), Point(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 1.5, Scalar::all(255), 2, 8);
					std::vector<unsigned char> d;		
					imencode(".jpg", img, d, params);
					Poco::Mutex::ScopedLock lock(_mutex);
					CurrentFrame = d;
					Poco::Mutex::ScopedLock unlock(_mutex);
					check = true;
				}
			}
			i++;
		}
		closedir(dir);
	}

	return check;
}

void CreateHttpResponse(std::string name, std::string dirname)
{
	if (ReadWholeDirectory(dirname))
	{
		//for (unsigned int i = 0; i < list.size(); i++)
		//{
			//printf("%s\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n", name.c_str(), list[i].size());
			//std::string a(list[i].begin(), list[i].end());
			//printf("%s", a.c_str());
			//for (unsigned int j = 0; j < list[i].size(); j++)
			//{
				//putchar(list[i][j]);
			//}
			//printf("\r\n");
		//}
	}
}

void NextFrame()
{	
	ReadWholeDirectory("D:\\Pictures\\packs\\1");
}

void HttpResponseToFile(std::string name, std::string dirname)
{
	std::vector<std::vector<unsigned char>> list;
	FILE *output;
	output = fopen("buffer.dat", "w");
	if (ReadWholeDirectory(dirname))
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			fprintf(output, "%s\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n", name.c_str(), list[i].size());
			for (unsigned int j = 0; j < list[i].size(); j++)
			{
				fputc(list[i][j], output);
			}
			fprintf(output, "\r\n");
		}
	}
	fclose(output);
}

void LibRun(UINT *i, int j)
{	
	std::vector<unsigned char> data;
	std::vector<int> params;
	Mat img(Size(WIDTH, HEIGHT), CV_8UC1, SaveImage[*i]);	
	cv::putText(img, std::to_string(j), Point(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 1.5, Scalar::all(255), 2, 8);
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(85);
	imencode(".jpg", img, data, params);
	Poco::Mutex::ScopedLock lock(_mutex);
	CurrentFrame = data;
	Poco::Mutex::ScopedLock unlock(_mutex);
}