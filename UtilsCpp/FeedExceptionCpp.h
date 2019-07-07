#pragma once

#include <string>

#ifdef  UTILS_EXPORTS
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

class DLLEXPORT FeedExceptionCpp
{
public:
	FeedExceptionCpp(std::string message, int lineCountOfException = -1, std::string lineOfException = "");
	~FeedExceptionCpp();

	std::string Message;
	int CurrentLineCountOfException;
	std::string LineOfException;
};


