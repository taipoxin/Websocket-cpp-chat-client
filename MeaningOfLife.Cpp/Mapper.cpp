
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


#include <iostream>
using namespace std;

#define MAX 10

class student
{
private:
	char  name[30];
	int   rollNo;
	int   total;
	float perc;
public:
	//member function to get student's details
	void getDetails(void);
	//member function to print student's details
	void putDetails(void);
};

//member function definition, outside of the class
void student::getDetails(void) {
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter roll number: ";
	cin >> rollNo;
	cout << "Enter total marks outof 500: ";
	cin >> total;

	perc = (float)total / 500 * 100;
}

//member function definition, outside of the class
void student::putDetails(void) {
	cout << "Student details:\n";
	cout << "Name:" << name << ",Roll Number:" << rollNo << ",Total:" << total << ",Percentage:" << perc;
}

int studentTest()
{
	student std[MAX];       //array of objects creation
	int n, loop;

	cout << "Enter total number of students: ";
	cin >> n;

	for (loop = 0; loop < n; loop++) {
		cout << "Enter details of student " << loop + 1 << ":\n";
		std[loop].getDetails();
	}

	cout << endl;

	for (loop = 0; loop < n; loop++) {
		cout << "Details of student " << (loop + 1) << ":\n";
		std[loop].putDetails();
	}

	return 0;
}

#include <iostream>
using namespace std;

class Time
{
private:
	int hours;
	int minutes;
	int seconds;

public:
	void getTime(void);
	void putTime(void);
	void addTime(Time T1, Time T2);
};

void Time::getTime(void)
{
	cout << "Enter time:" << endl;
	cout << "Hours? ";    cin >> hours;
	cout << "Minutes? ";  cin >> minutes;
	cout << "Seconds? ";  cin >> seconds;
}

void Time::putTime(void)
{
	cout << endl;
	cout << "Time after add: ";
	cout << hours << ":" << minutes << ":" << seconds << endl;
}

void Time::addTime(Time T1, Time T2)
{

	this->seconds = T1.seconds + T2.seconds;
	this->minutes = T1.minutes + T2.minutes + this->seconds / 60;;
	this->hours = T1.hours + T2.hours + (this->minutes / 60);
	this->minutes %= 60;
	this->seconds %= 60;
}


int testTime()
{
	Time T1, T2, T3;
	T1.getTime();
	T2.getTime();
	//add two times
	T3.addTime(T1, T2);
	T3.putTime();

	return 0;
}

using namespace std;

class candidate {
public:
	string name;
	int vote;
};

void outputElection(candidate* arr) {
	int total_vote = 0;
	for (int i = 0; i < 5; i++) {
		//finding total no of votes
		total_vote = total_vote + arr[i].vote;
	}

	cout << "result of the election............." << endl;
	cout << "name of candidate" << "\t" << "vote received" << "\t" << "percentage" << endl;
	for (int i = 0; i < 5; i++) {
		cout << arr[i].name << "\t\t\t";
		cout << arr[i].vote << "\t\t";
		cout << (arr[i].vote * 100) / total_vote << "%" << endl;
	}

	int max = INT_MIN, count = 0;
	int index[5] = { 0 };

	for (int i = 0; i < 5; i++) {
		if (arr[i].vote > max) {
			max = arr[i].vote;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (arr[i].vote == max) {
			index[count] = i;
			count++;
		}
	}

	if (count == 1)
		cout << "The winner is " << arr[index[count - 1]].name << endl;
	else {
		cout << "There is tie between:" << endl;
		for (int i = 0; i < count - 1; i++)
			cout << arr[index[i]].name << ", ";
		cout << arr[index[count - 1]].name << endl;
		cout << "all are winner\n";
	}
	return;
}

int testCandidate() {
	string s;
	int v;
	candidate arr[5];
	cout << "enter candidates last name, there are five candidates\n";
	for (int i = 0; i < 5; i++) {
		cout << "enter candidate " << i << " last name\n";
		cin >> s;
		arr[i].name = s;
		cout << "enter no of votes received by candidate " << i << endl;
		cin >> v;
		arr[i].vote = v;
	}
	outputElection(arr);
	return 0;
}


#include <iostream>
using namespace std;

class Number
{
	private:
		int num;
	public:
		//constructor
		Number(){ num=0; };
		
		//member function to get input
		void inputNumber (void)
		{
			cout<<"Enter an integer number: ";
			cin>>num;
		}
		//member function to display number 
		void displayNumber()
		{
			cout<<"Num: "<<num<<endl;
		}
};

//Main function
int byPointer()
{
	//declaring object to the class number
	Number N;
	//input and display number using norn object
	N.inputNumber();
	N.displayNumber();

	//declaring pointer to the object 
	Number *ptrN;
	ptrN = new Number; //creating & assigning memory 
	
	//printing default value
	cout<<"Default value... "<<endl;
	//calling member function with pointer 
	ptrN->displayNumber();
	
	//input values and print 
	ptrN->inputNumber();
	ptrN->displayNumber();

	return 0;
}

#include <iostream>
using namespace std;

// claas declaration
class point
{
private:
	int X, Y;

public:
	//defualt constructor 
	point() { X = 0; Y = 0; }

	//setter function
	void setPoint(int a, int b)
	{
		X = a;
		Y = b;
	}
	//getter functions
	int getX(void)
	{
		return X;
	}
	int getY(void)
	{
		return Y;
	}

};

//Main function
int pointXY()
{
	//object 
	point p1, p2;

	//set points
	p1.setPoint(5, 10);
	p2.setPoint(50, 100);

	//get points 
	cout << "p1: " << p1.getX() << " , " << p1.getY() << endl;
	cout << "p1: " << p2.getX() << " , " << p2.getY() << endl;

	return 0;
}

#include <iostream>
using namespace std;

//structure definition with private and public memebers
struct Student1
{
private:
	int rNo;
	float perc;
public:
	//function to read details
	void read(void)
	{
		cout << "Enter roll number: ";
		cin >> rNo;
		cout << "Enter percentage: ";
		cin >> perc;
	}
	//function to print details
	void print(void)
	{
		cout << endl;
		cout << "Roll number: " << rNo << endl;
		cout << "Pecentage: " << perc << "%" << endl;
	}
};

//Main code
int stTest()
{
	//declaring structure variable
	struct Student1 std;
	//reading and printing student details
	//by calling public member functions of the structure
	std.read();
	std.print();

	return 0;
}