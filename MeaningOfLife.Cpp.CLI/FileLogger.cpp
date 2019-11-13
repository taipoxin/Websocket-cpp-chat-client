#include <msclr/marshal.h>
using namespace std;
using namespace System;
using namespace System::Configuration;

#include <string>
#include "FileLogger.h"
#include <Windows.h>
#include "..\MeaningOfLife.Cpp\FileLogger.h"
#include "CastUtils.h"


MeaningOfLife::Cpp::CLI::FileLogger::FileLogger(String^ file)
	: _impl(new Cpp::FileLogger(string_to_char_array(file)))
{}


void MeaningOfLife::Cpp::CLI::FileLogger::log(String^ text)
{
	_impl->log(string_to_char_array(text));
}
