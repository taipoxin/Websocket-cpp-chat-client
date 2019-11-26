
#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>


std::map<std::string, int>::iterator serachByValue(std::map<std::string, int> & mapOfWords, int val)
{
	// Iterate through all elements in std::map and search for the passed element
	std::map<std::string, int>::iterator it = mapOfWords.begin();
	while (it != mapOfWords.end())
	{
		if (it->second == val)
			return it;
		it++;
	}
}
int checkExample()
{
	std::map<std::string, int> mapOfWords;
	// Inserting data in std::map
	mapOfWords.insert(std::make_pair("earth", 1));
	mapOfWords.insert(std::make_pair("moon", 2));
	mapOfWords["sun"] = 3;
	std::map<std::string, int>::iterator it = serachByValue(mapOfWords, 3);
	if (it != mapOfWords.end())
		std::cout << it->first << " :: " << it->second << std::endl;
	return 0;
}


int isExistsExample() {

	// Map of string & int i.e. words as key & there
	// occurrence count as values
	std::map<std::string, int> wordMap = {
			{ "is", 6 }, { "the", 5 },
			{ "hat", 9 }, { "at", 6 }
	};

	// Create an iterator of map
	std::map<std::string, int>::iterator it;

	// Find the element with key 'hat'
	it = wordMap.find("hat");

	// Check if element exists in map or not
	if (it != wordMap.end()) {
		// Element with key 'hat' found
		std::cout << "'hat' Found" << std::endl;

		// Access the Key from iterator
		std::string key = it->first;
		// Access the Value from iterator
		int value = it->second;

		std::cout << "key = " << key << " :: Value = " << value << std::endl;
	}
	else {
		// Element with key 'hat' Not Found
		std::cout << "'hat' Not Found" << std::endl;
	}

	// Find the element with key 'hello'
	it = wordMap.find("hello");

	// Check if element exists in map or not
	if (it != wordMap.end()) {
		// Element with key 'hello' found
		std::cout << "'hello' Found" << std::endl;

		// Access the Key from iterator
		std::string key = it->first;
		// Access the Value from iterator
		int value = it->second;

		std::cout << "key = " << key << " :: Value = " << key << std::endl;

	}
	else {
		// Element with key 'hello' Not Found
		std::cout << "'hello' Not Found" << std::endl;
	}

	return 0;
}