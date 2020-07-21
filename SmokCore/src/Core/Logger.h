//handles logging

#ifndef Logger_h
#define Logger_h

#include <string>
#include <stdio.h>

//logs a error message
inline void LogError(const std::string& type, const std::string& message)
{
#ifndef SMOK_DIST
	std::printf("ERROR, Type: %s || %s\n", type.c_str(), message.c_str());
#endif
}

//logs a message
inline void LogMessage(const std::string& message)
{
#ifndef SMOK_DIST
	std::printf("%s\n", message.c_str());
#endif
}

#endif


