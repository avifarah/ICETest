#pragma once

#include <string>


#ifdef  UTILSCPP_EXPORTS
	#define UTILS_DLLEXPORT __declspec(dllexport)
#else
	#define UTILS_DLLEXPORT __declspec(dllimport)
#endif

using namespace std;

UTILS_DLLEXPORT string Trim(string text);
