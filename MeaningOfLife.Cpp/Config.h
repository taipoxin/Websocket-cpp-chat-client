// Logic.h
#pragma once

#include <string>

namespace MeaningOfLife
{	
	namespace Cpp
	{
	using namespace std;
		// This is our native implementation
		// It's marked with __declspec(dllexport) 
		// to be visible from outside the DLL boundaries
		class __declspec(dllexport) Config
		{
		public:
			static inline const char* wsSource = "ws://192.168.137.97:9000";
			static inline const char* userName = "";
			static inline const char* logFileName = "logs.txt";
		};
	}
}
