#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include<string>
#include "entry.hpp"
using namespace std;

#define DEFAULT_TABLE_SIZE 5003
#define DEFAULT_POL_VAR 33
#define MAX_WORD_LENGTH 20
#define DEFAULT_A 13
#define DEFAULT_B 17

static Entry* empty;

class HashTable{
	private:
		int tableSize,numOfElements,numOfCol;
		unsigned int polVar,a,b;
		unsigned int *powerArr;
		Entry **entryTable;
		unsigned int hashCode(string);
		unsigned int hashMap(unsigned int);
		unsigned int hashMapProbe(unsigned int);
		bool checkPrime(int);
	public:
		HashTable();
		HashTable(int);
		~HashTable();
		void print(int);
		void printAllData();
		int getTableSize();
		int getNumOfElements();
		int getNumOfCol();
		int getPos(string);
		void insert(string,Entry*);
		void remove(string);
		void search(string);
		void rehash();
};

#endif
