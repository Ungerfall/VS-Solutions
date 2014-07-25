#include "FrameRequestHandler.h"

Poco::Mutex _mutex;

void FrameRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	/*resp.setContentType("text/html");

	std::ostream &out = resp.send();
	out << "<h1>Hello world!</h1>"
        << "<p>Count: "  << ++count         << "</p>"
        << "<p>Host: "   << req.getHost()   << "</p>"
        << "<p>Method: " << req.getMethod() << "</p>"
        << "<p>URI: "    << req.getURI()    << "</p>";
    out.flush();

	std::cout << std::endl
         << "Response sent for count=" << count
         << " and URI=" << req.getURI() << std::endl;*/
	if (req.getURI() == "/?type:stream")
	{
		resp.setContentType("image/jpeg; boundary=--myboundary");
		std::ostream &out = resp.send();
		while (out.good())
		{			
			std::vector<unsigned char> local_current;
			out << "--myboundary";
			out << "\r\n";
			out << "Content-Type: image/jpeg";
			out << "\r\n";
			Poco::Mutex::ScopedLock lock(_mutex);
			out << "Content-Length: " << CurrentFrame.size();
			out << "\r\n";
			out << "\r\n";
			local_current = CurrentFrame;			
			Poco::Mutex::ScopedLock unlock(_mutex);
			for (std::vector<unsigned char>::const_iterator i = local_current.begin(); i != local_current.end(); i++)
				out << *i;
			out << "\r\n";
			out.flush();
			printf_s("Кадр отправлен");
		}
	}
	else
	{
		resp.setContentType("image/jpeg; boundary=--myboundary");
		Poco::Mutex::ScopedLock lock(_mutex);
		resp.sendBuffer(&CurrentFrame[0], CurrentFrame.size());
		Poco::Mutex::ScopedLock unlock(_mutex);
	}
	
	/*std::ostream &out = resp.send();
	out << "\r\n";
	for(unsigned int i = 0; i < CurrentFrame.size(); i++)
	{
		out << CurrentFrame[i];
	}
	out << "\r\n";*/
}