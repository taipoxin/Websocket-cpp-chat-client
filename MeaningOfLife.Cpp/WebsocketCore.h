
#pragma once
#include <string>

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) WebsocketCore
		{
		public:
			WebsocketCore();
			WebsocketCore(string target);
			void saveJSON(string json);
		private:
			string target;
		};
	}
}
