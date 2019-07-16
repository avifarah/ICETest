#pragma once

#include <string>


#ifdef  UTILSCPP_EXPORTS
	#define UTILS_DLLEXPORT __declspec(dllexport)
	#pragma message("__declspec(dllexport)")
#else
	#define UTILS_DLLEXPORT __declspec(dllimport)
	#pragma message("__declspec(dllimport)")
#endif

using namespace std;

class UTILS_DLLEXPORT FeedExceptionCpp
{
private:
	string Message;
	int CurrentLineCountOfException;
	string LineOfException;

public:
	FeedExceptionCpp(string message, int lineCountOfException = -1, string lineOfException = "");
	~FeedExceptionCpp();

	string GetExMessage();
	int GetCurrentLineCountOfException();
	string GetLineOfException();
};


