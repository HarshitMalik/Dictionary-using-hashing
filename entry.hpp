#ifndef ENTRY_HPP
#define ENTRY_HPP
#include<string>
using namespace std;

class Entry{
	public:
		string word,meaning;
		Entry();
		Entry(string,string);
		bool isEqual(string);
};

#endif
