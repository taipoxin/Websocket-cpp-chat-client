
#pragma once

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) WebsocketCore
		{
		public:
			WebsocketCore();
			WebsocketCore(string host, string port);
			void saveJSON(string json);
			int init(string host, string port, string text);
		private:
			string host;
			string port;
		};
	}
}
