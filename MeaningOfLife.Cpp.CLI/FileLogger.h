
#pragma once
using namespace System;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class FileLogger;
		namespace CLI
		{
			public ref class FileLogger
			{
			public:
				FileLogger(String^ file);
				void log(String^ text);
			private:
				Cpp::FileLogger* _impl;
			};
		}
	}
}