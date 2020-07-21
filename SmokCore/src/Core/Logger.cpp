#include "smpch.h"
#include "Logger.h"

std::vector<std::string> Logger::errorTypes;
bool Logger::logErrorOnce = false; //only logs a error of a type once


	//returns if a error type is already stored
	bool Logger::IsError(const std::string& type)
	{
#ifndef SMOK_DIST
		if (errorTypes.size() < 1)
			return false;

		for (int i = 0; i < errorTypes.size(); i++)
		{
			if (errorTypes[i] == type)
				return true;
		}

#endif

		return false;
	}

	//adds a error type
	void Logger::AddErrorType(const std::string& type)
	{
#ifndef SMOK_DIST

		if (IsError(type))
			return;

		errorTypes.emplace_back(type);

#endif
	}

	//logs a error message
	void Logger::LogError(const std::string& type, const std::string& message)
	{
#ifndef SMOK_DIST

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		std::printf("ERROR, Type: %s || %s\n", type.c_str(), message.c_str());
		AddErrorType(type);
#endif
	}

	//logs a message
	void Logger::LogMessage(const std::string& message)
	{
#ifndef SMOK_DIST
		std::printf("%s\n", message.c_str());
#endif
	}

	//logs a error message
	void Logger::LogError(const char* type, const char* message)
	{
#ifndef SMOK_DIST

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		std::printf("ERROR, Type: %s || %s\n", type, message);
		AddErrorType((std::string)type);
#endif
	}

	//logs a message
	void Logger::LogMessage(const char* message)
	{
#ifndef SMOK_DIST
		std::printf("%s\n", message);
#endif
	}