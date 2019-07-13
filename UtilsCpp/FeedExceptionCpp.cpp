#include "pch.h"
#include <string>
#include "FeedExceptionCpp.h"

using namespace std;

FeedExceptionCpp::FeedExceptionCpp(string message, int lineCountOfException /*= -1*/, string lineOfException /*= ""*/)
	: Message(message), CurrentLineCountOfException(lineCountOfException), LineOfException(lineOfException)
{
}

FeedExceptionCpp::~FeedExceptionCpp()
{
}

string FeedExceptionCpp::GetExMessage() { return Message; }

int FeedExceptionCpp::GetCurrentLineCountOfException() { return CurrentLineCountOfException; }

string FeedExceptionCpp::GetLineOfException() { return LineOfException; }
