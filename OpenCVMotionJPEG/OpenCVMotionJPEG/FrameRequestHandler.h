#pragma once

#include <Poco\Net\HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Mutex.h>
#include <iostream>
#include <string>
#include "FrameRunnable.h"
#include "OpenCVmjpeg.h"
#include <Windows.h>
#include <WinSock2.h>

extern Poco::Mutex _mutex;

class FrameRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	virtual void handleRequest(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse&);

private:
	static int count;
};

