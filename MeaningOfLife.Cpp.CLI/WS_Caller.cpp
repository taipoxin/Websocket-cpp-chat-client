#include <msclr/marshal.h>
using namespace std;
using namespace System;
using namespace System::Configuration;

#include <string>
#include "WS_Caller.h"
#include <Windows.h>
#include "..\MeaningOfLife.Cpp\WS_Caller.h"
#include "CastUtils.h"


MeaningOfLife::Cpp::CLI::WS_Caller::WS_Caller(String^ file, String^ host)
	: _impl(new Cpp::WS_Caller(string_to_char_array(file), string_to_char_array(host)))
{}


void MeaningOfLife::Cpp::CLI::WS_Caller::connectWS(double timeoutS)
{
	_impl->connectWS(timeoutS);
}

void MeaningOfLife::Cpp::CLI::WS_Caller::send(String^ message)
{
	_impl->send(string_to_char_array(message));
}


void MeaningOfLife::Cpp::CLI::WS_Caller::close()
{
	_impl->close();
}

void MeaningOfLife::Cpp::CLI::WS_Caller::IsAlive()
{
	_impl->IsAlive();
}

