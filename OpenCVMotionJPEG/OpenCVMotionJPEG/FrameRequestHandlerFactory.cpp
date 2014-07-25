#include "FrameRequestHandlerFactory.h"

Poco::Net::HTTPRequestHandler *FrameRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
	return new FrameRequestHandler;
}