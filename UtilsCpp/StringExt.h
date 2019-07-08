#pragma once

#include <string>

using namespace std;


#ifdef  UTILS_EXPORTS
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

DLLEXPORT string Trim(string text);
