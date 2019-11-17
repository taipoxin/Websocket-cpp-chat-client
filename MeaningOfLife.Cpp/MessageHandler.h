#pragma once
#include <string>

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) MessageHandler
		{
		public:
			MessageHandler(string file);
			void handle(string message);
		private:
			string file;
			string castType(string type);
		};
	}
}
