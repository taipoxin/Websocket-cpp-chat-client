#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include "FileLogger.h"

using namespace std;

MeaningOfLife::Cpp::FileLogger::FileLogger(string file)
{
	this->file = file;
}

void MeaningOfLife::Cpp::FileLogger::logg(string s, bool withTime, string sep) {
	string ss = s;
	if (withTime) {
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		string dt = std::ctime(&end_time);
		dt.pop_back();
		ss = "[" + dt + "]: " + s + sep;
	}
	std::ofstream writer;
	//std::ofstream writer(this->file);
	writer.open(this->file, std::ios::app);
	writer << ss;
}


void MeaningOfLife::Cpp::FileLogger::log(string s, bool withTime) {
  logg(s, withTime, "\n");
}

