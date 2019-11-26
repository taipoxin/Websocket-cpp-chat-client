#pragma once


#include <iostream>
#include <AtlBase.h>
#include <atlconv.h>
#include <stdio.h>
#include <time.h>

using namespace std;

std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);

wstring string_to_wstring(string str);
void waitSec(double time);
