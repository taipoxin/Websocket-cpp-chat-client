#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include "WS_Caller.h"

using namespace std;
using namespace MeaningOfLife::Cpp;


void WS_Caller::call(string file, string message) {
	ofstream writer;
	//ofstream writer(this->file);
	writer.open(file);
	writer << message;
}

int WS_Caller::connectWS(double timeoutS) {
	call(file, "connect:::" + to_string(timeoutS));
	return 0;
}
void WS_Caller::send(string message) {
	call(file, "send:::" + message);
}

void WS_Caller::close() {
	call(file, "close:::");
}

bool WS_Caller::IsAlive() {
	call(file, "isalive:::");
	return true;
}

WS_Caller::WS_Caller(string file, string host) {
	this->file = file;
	this->host = host;
	call("init.txt", "init:::" + host);
}
