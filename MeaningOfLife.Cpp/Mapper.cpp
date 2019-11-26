
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


int eraseElExample() {

	// Map of string & int i.e. words as key & there
	// occurrence count as values
	std::map<std::string, int> wordMap = { { "is", 6 }, { "the", 5 },
			{ "hat", 9 }, { "at", 6 }, { "of", 2 }, { "hello", 1 } };


	std::cout << "Map Entries Before Deletion" << std::endl;
	// Print the map elements
	for (auto elem : wordMap)
		std::cout << elem.first << " :: " << elem.second << std::endl;

	// Create an iterator pointing to begin of map
	std::map<std::string, int>::iterator it1 = wordMap.begin();

	// Create an iterator pointing to begin of map
	std::map<std::string, int>::iterator it2 = wordMap.begin();
	// Increment Iterator
	it2++;
	// Increment Iterator
	it2++;
	// Itr2 is now pointing to 3rd element


	// Check if iterator is valid.
	if (it1 != wordMap.end() && it2 != wordMap.end())
	{
		// Remove the element pointed by iterator
		wordMap.erase(it1, it2);
		std::cout << "Elements Removed" << std::endl;
	}
	else
		std::cout << "Key Not Found" << std::endl;


	std::cout << "Map Entries After Deletion" << std::endl;
	// Print the map elements
	for (auto elem : wordMap)
		std::cout << elem.first << " :: " << elem.second << std::endl;

	return 0;
}


#include <unordered_map>
#include <string>

int unorderedMap() {
	// Initialize an unordered_map through initializer_list
	std::unordered_map<std::string, int> wordMap({
		{ "First", 1 }, { "Second",	2 }, { "Third", 3 }
		});

	// Declare an iterator to unordered_map
	std::unordered_map<std::string, int>::iterator it;

	// Find if an element with key "First" exists or not.
	// find() returns an iterator

	it = wordMap.find("First");

	// Check if iterator points to end of map
	if (it != wordMap.end())
	{
		std::cout << "Element Found - ";
		std::cout << it->first << "::" << it->second << std::endl;
	}
	else
	{
		std::cout << "Element Not Found" << std::endl;
	}

	return 0;
}


#include <iostream>
#include <set>
#include <string>
#include <algorithm>


/*
 * Access nth element from a set.
 * It returns a pair of Element and bool.
 * bool represents if nth element exists in set or not.
 * if bool is true them First element of pair T contains the element value
 */
template <typename T>
std::pair<T, bool> getNthElement(std::set<T> & searchSet, int n)
{
	std::pair<T, bool> result;
	if (searchSet.size() > n)
	{
		result.first = *(std::next(searchSet.begin(), n));
		result.second = true;
	}
	else
		result.second = false;

	return result;
}

void setByIndex()
{
	std::set<std::string> setOfStr =
	{ "bb", "ee", "dd", "aa", "ll" };

	std::cout << "***** Set Contents *****" << std::endl;
	for (std::string elem : setOfStr)
		std::cout << elem << std::endl;

	std::cout << "***** Accessing Elements by Index ***" << std::endl;

	// Access 3rd element
	std::pair<std::string, bool> result = getNthElement(setOfStr, 3);

	if (result.second)
		std::cout << "3rd Element in set = " << result.first << std::endl;
	else
		std::cout << "3rd Element in set not found" << std::endl;


	// Access 7th element
	result = getNthElement(setOfStr, 7);

	if (result.second)
		std::cout << "7th Element in set = " << result.first << std::endl;
	else
		std::cout << "7th Element in set not found" << std::endl;

}

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

class Wallet
{
	int mMoney;
	std::mutex mutex;
public:
	Wallet() :mMoney(0) {}
	int getMoney() { return mMoney; }
	void addMoney(int money)
	{
		mutex.lock();
		for (int i = 0; i < money; ++i)
		{
			mMoney++;
		}
		mutex.unlock();
	}
};


int testMultithreadedWallet()
{
	Wallet walletObject;
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
	}
	for (int i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}
	return walletObject.getMoney();
}
int WalletThread()
{
	int val = 0;
	for (int k = 0; k < 1000; k++)
	{
		if ((val = testMultithreadedWallet()) != 5000)
		{
			std::cout << "Error at count = " << k << "  Money in Wallet = " << val << std::endl;
			//break;
		}
	}
	return 0;
}


int testMultithreadedWallet1()
{
	Wallet walletObject;
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
	}
	for (int i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}
	return walletObject.getMoney();
}
int multiWallet()
{
	int val = 0;
	for (int k = 0; k < 1000; k++)
	{
		if ((val = testMultithreadedWallet1()) != 5000)
		{
			std::cout << "Error at count = " << k << " Money in Wallet = " << val << std::endl;
		}
	}
	return 0;
}