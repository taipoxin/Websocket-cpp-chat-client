
#pragma once
#include <string>
namespace MeaningOfLife
{
	namespace Cpp
	{
		using namespace std;

		class __declspec(dllexport) WS_Caller
		{
		public:
			WS_Caller();
			WS_Caller(string file, string host);
			void call(string file, string message);
			int connectWS(double timeoutS);
			void send(string message);
			void close();
			bool IsAlive();
		private:
			string host;
			string file;
		};
	}
}