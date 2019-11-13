#pragma once
#include <string>

using namespace std;

namespace MeaningOfLife
{	
	namespace Cpp
	{
		class __declspec(dllexport) FileLogger
		{
		public:
			FileLogger(string file);
			void log(string s, bool withTime = true);
			void logg(string s, bool withTime = true, string sep = "");
		private:
			string file;
		};
	}
}
