#include "CastCoreUtils.h"
#include <iostream>
#include <vector>

using namespace std;


typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
std::string base64_encode(const std::string &in) {
	std::string out;

	int val = 0, valb = -6;
	for (uchar c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(b[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}




std::string base64_decode(const std::string &in) {

	std::string out;

	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T[b[i]] = i;

	int val = 0, valb = -8;
	for (uchar c : in) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

wstring string_to_wstring(string str) {
	CA2W ca2w(str.c_str());
	wstring w = ca2w;
	return w;
}


void waitSec(double time) {
	clock_t this_time = clock();
	clock_t last_time = this_time;
	while ((time * CLOCKS_PER_SEC > (double)(this_time - last_time))) {
		this_time = clock();
	}
}
