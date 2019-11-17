
#pragma once
using namespace System;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class WS_Caller;
		namespace CLI
		{
			public ref class WS_Caller
			{
			public:
				WS_Caller(String^ file, String^ host);
				void connectWS(double timeoutS);
				void send(String^ message);
				void close();
				void IsAlive();
			private:
				Cpp::WS_Caller* _impl;
			};
		}
	}
}