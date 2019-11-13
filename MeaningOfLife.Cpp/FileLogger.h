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
      FileLogger();
      void log(const char* s, bool toEnd);
      void log(const char* s);
      void logg(const char* s, bool toEnd);

    private:
      const char* file;
		};
	}
}
