#pragma once

#include <Poco\Net\HTTPServer.h>
#include <Poco\Util\ServerApplication.h>
#include "FrameRequestHandler.h"
#include "FrameRequestHandlerFactory.h"
#include "OpenCVmjpeg.h"

using namespace Poco::Util;
using namespace Poco::Net;

class FrameServer : public ServerApplication
{
protected:
	void initialize(Application&);
	void uninitialize();
	int main(const std::vector<std::string>&);
};
