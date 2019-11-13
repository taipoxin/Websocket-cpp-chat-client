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
		class __declspec(dllexport) FileLogger
		{
		public:
      FileLogger(const char* file);
      void log(const char* s, bool withTime = true);
      void logg(const char* s, bool withTime = true, const char* sep = "");

    private:
      const char* file;
		};
	}
}
