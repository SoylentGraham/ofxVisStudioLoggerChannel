#include "ofxVisStudioLoggerChannel.h"


void ofVisStudioLoggerChannel::log(ofLogLevel level, const string & module, const string & message){
	std::string out;
	out += "[";
	// only print the module name if it's not "OF"
	if(module != "OF") {
		out += module;
		out += ":";
	}
	out += ofGetLogLevelName(level);
	out += "] ";
	out += message;
	out += "\n";

	OutputDebugStringA( out.c_str() );
}	

void ofVisStudioLoggerChannel::log(ofLogLevel logLevel, const string & module, const char* format, ...){
	va_list args;
	va_start(args, format);
	log(logLevel, module, format, args);
	va_end(args);
}

void ofVisStudioLoggerChannel::log(ofLogLevel logLevel, const string & module, const char* format, va_list args)
{
	//	generate final output message
	string message;
	char Buffer[2000];
	int Len = vsnprintf_s( Buffer, sizeof(Buffer)-1, format, args );

	//	too long for buffer,(or error) alloc a buffer temporarily with std::vector
	if ( Len < 0 || Len >= sizeof(Buffer) )
	{
		//	calc length so we know how much to allocate
		Len = _vscprintf( format, args );
		//	-1 should only occur with bad parameters, but just in case...
		//	http://msdn.microsoft.com/en-us/library/d3xd30zz(v=vs.90).aspx
		Len = max( Len, 0 );
		std::vector<char> BufferVector( Len+1 );

		Len = vsnprintf_s( &BufferVector[0], BufferVector.size(), BufferVector.size()-1, format, args );
		Len = max( Len, 0 );
		BufferVector[Len] = '\0';
		message = static_cast<const char*>( &BufferVector[0] );
	}
	else
	{
		Buffer[Len] = '\0';
		message = Buffer;
	}

	log( logLevel, module, message );
}
