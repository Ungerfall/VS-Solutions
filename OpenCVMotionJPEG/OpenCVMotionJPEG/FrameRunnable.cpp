#include "OpenCVmjpeg.h"
#include "FrameRunnable.h"


void FrameRunnable::run()
{
	//home
	//NextFrame();

	//autowash
	InitCamera();
	GetFrame();
}