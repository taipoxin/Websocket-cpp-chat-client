#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include "FileLogger.h"

using namespace std;
using namespace MeaningOfLife::Cpp;

FileLogger::FileLogger(string file)
{
	this->file = file;
}

void FileLogger::logg(string s, bool withTime, string sep) {
	string ss = s;
	if (withTime) {
		auto end = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(end);
		string dt = ctime(&end_time);
		dt.pop_back();
		ss = "[" + dt + "]: " + s + sep;
	}
	ofstream writer;
	//ofstream writer(this->file);
	writer.open(this->file, ios::app);
	writer << ss;
}


void FileLogger::log(string s, bool withTime) {
  logg(s, withTime, "\n");
}

