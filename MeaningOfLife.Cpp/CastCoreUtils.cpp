#include "CastCoreUtils.h"

wstring string_to_wstring(string str) {
	CA2W ca2w(str.c_str());
	wstring w = ca2w;
	return w;
}
