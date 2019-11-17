#include "CastCoreUtils.h"

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
