// Logic.h
#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>


#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include "WS_Core.h"


namespace MeaningOfLife
{	
	namespace Cpp
	{
	using namespace std;
		// This is our native implementation
		// It's marked with __declspec(dllexport) 
		// to be visible from outside the DLL boundaries
		class __declspec(dllexport) Logic
		{
		public:
			std::wstring Get(string text) const;
		};
	}
}