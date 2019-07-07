#pragma once

#include <string>

class FeedExceptionCpp
{
public:
	FeedExceptionCpp(std::string message, int lineCountOfException = -1, std::string lineOfException = "");
	~FeedExceptionCpp();


	std::string Message;
	int CurrentLineCountOfException;
	std::string LineOfException;
};

