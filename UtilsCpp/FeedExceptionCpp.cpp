#include "pch.h"
#include "FeedExceptionCpp.h"

FeedExceptionCpp::FeedExceptionCpp(std::string message, int lineCountOfException /*= -1*/, std::string lineOfException /*= ""*/)
	: Message(message), CurrentLineCountOfException(lineCountOfException), LineOfException(lineOfException)
{
}

FeedExceptionCpp::~FeedExceptionCpp()
{
}
