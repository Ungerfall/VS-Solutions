#pragma once

#include "FrameRequestHandler.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

class FrameRunnable : public Poco::Runnable
{
	virtual void run();
};

