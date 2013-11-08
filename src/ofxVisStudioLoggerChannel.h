#pragma once
/*
	Very simple ofLoggerChannel that prints out to visual studio via OutputDebugString()


	usage;
	
	if ( IsDebuggerPresent() )
		ofLog::setChannel(ofPtr<ofVisStudioLoggerChannel>(new ofVisStudioLoggerChannel));

	IsDebuggerPresent just tells you if a debugger is attached.
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms680345(v=vs.85).aspx
*/
#include <ofMain.h>


class ofVisStudioLoggerChannel: public ofBaseLoggerChannel{
public:
	virtual ~ofVisStudioLoggerChannel(){};
	void log(ofLogLevel level, const string & module, const string & message);
	void log(ofLogLevel logLevel, const string & module, const char* format, ...);
	void log(ofLogLevel logLevel, const string & module, const char* format, va_list args);
};

