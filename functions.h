#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<fstream>
#include "hashTable.hpp"
using namespace std;

void mainMenu(HashTable&);
void addNewWord(HashTable&);
void removeWord(HashTable&);
void searchWord(HashTable&);
void getTableSize(HashTable&);
void getNumOfWord(HashTable&);
void readFileData(HashTable&);
void spellCheck(HashTable&);
bool isPrime(int);

#endif
