#include "Logic.h"
#include "..\MeaningOfLife.Cpp\Logic.h"
#include <string>
#include <Windows.h>

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

String^ char_array_to_string(const char* str)
{
	String^ res = Marshal::PtrToStringAnsi((IntPtr)(char *)str);
	return res;
}

const char* string_to_char_array(String^ str) 
{
	return (const char*)(void*)
		Marshal::StringToHGlobalAnsi(str);
}

string ManagedStringToStdString(System::String^ str)
{
	cli::array<unsigned char>^ bytes = System::Text::Encoding::ASCII->GetBytes(str);
	pin_ptr<unsigned char> pinned = &bytes[0];
	std::string nativeString((char*)pinned, bytes->Length);
	return nativeString;
}


MeaningOfLife::Cpp::CLI::Logic::Logic()
	: _impl(new Cpp::Logic()) 
	// Allocate some memory for the native implementation
{
}

String^ MeaningOfLife::Cpp::CLI::Logic::Get(String^ text)
{
	
	const char* mText = string_to_char_array(text);
	String^ a = char_array_to_string(_impl->Get(mText));
	//String^ a = gcnew String(_impl->Get());
	
	
	/*
	const wchar_t* w = _impl->Get();
	System::Console::WriteLine(w);
	wchar_t* wc = const_cast<wchar_t*>(_impl->Get());
	System::Console::WriteLine(wc);
	//std::wcout << wc;
	String^ a = Marshal::PtrToStringUni((IntPtr)wc);
	System::Console::WriteLine(a);
	//return gcnew String(_impl->Get());
	*/
	return a;
	//return a; // Call native Get
}

void MeaningOfLife::Cpp::CLI::Logic::Destroy()
{
	if (_impl != nullptr)
	{
		delete _impl;
		_impl = nullptr;
	}
}

MeaningOfLife::Cpp::CLI::Logic::~Logic()
{
	// C++ CLI compiler will automaticly make all ref classes implement IDisposable.
	// The default implementation will invoke this method + call GC.SuspendFinalize.
	Destroy(); // Clean-up any native resources 
}

MeaningOfLife::Cpp::CLI::Logic::!Logic()
{
	// This is the finalizer
	// It's essentially a fail-safe, and will get called
	// in case Logic was not used inside a using block.
	Destroy(); // Clean-up any native resources 
}



void MeaningOfLife::Cpp::CLI::Logic::InitializeLibrary(System::String^ path)
{
	string nativePath = ManagedStringToStdString(path);
	LoadLibrary(nativePath.c_str()); // Actually load the delayed library from specific location
}
