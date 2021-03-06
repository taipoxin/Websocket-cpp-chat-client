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
			static string wsSource;
			static string userName;
			static string logFileName;
		};
	}
}
