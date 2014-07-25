#include "FrameServer.h"

int FrameRequestHandler::count = 0;

void FrameServer::initialize(Application &self)
{
	loadConfiguration();
	ServerApplication::initialize(self);
}

void FrameServer::uninitialize()
{
	ServerApplication::uninitialize();
}

int FrameServer::main(const std::vector<std::string>& args)
{
	HTTPServer s(new FrameRequestHandlerFactory, ServerSocket(9000), new HTTPServerParams);
	s.start();
	printf_s("Start server");
	FrameRunnable runnble;
	Poco::Thread thread;
	thread.start(runnble);
	thread.join();
	waitForTerminationRequest();

	printf_s("Shutting down");
	s.stop();
	return 0;
}

POCO_SERVER_MAIN(FrameServer)

