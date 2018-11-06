#include<iostream>
#include<string>
#include<cmath>
#include "hashTable.hpp"
using namespace std;

HashTable::HashTable(){
	tableSize = DEFAULT_TABLE_SIZE;
	numOfElements = 0;
	numOfCol = 0;
	polVar = DEFAULT_POL_VAR;
	a = DEFAULT_A;
	b = DEFAULT_B;
	entryTable = new Entry*[DEFAULT_TABLE_SIZE];
	for(int i =0;i<DEFAULT_TABLE_SIZE;i++)
		entryTable[i]=NULL;
	powerArr = new unsigned int[MAX_WORD_LENGTH];
	powerArr[0]=1;
	for(int i =1;i<MAX_WORD_LENGTH;i++)
		powerArr[i]=powerArr[i-1]*polVar;
}

HashTable::HashTable(int size){
	if(size!=0)
		tableSize = size;
	else
		tableSize = DEFAULT_TABLE_SIZE;
	numOfElements = 0;
	numOfCol = 0;
	polVar = DEFAULT_POL_VAR;
	a = DEFAULT_A;
	b = DEFAULT_B;
	entryTable = new Entry*[tableSize];
	for(int i =0;i<tableSize;i++)
		entryTable[i]=NULL;
	powerArr = new unsigned int[MAX_WORD_LENGTH];
	powerArr[0]=1;
	for(int i =1;i<MAX_WORD_LENGTH;i++)
		powerArr[i]=powerArr[i-1]*polVar;
}

HashTable::~HashTable(){
	for(int i =0;i<tableSize;i++){
		if(entryTable[i]!=NULL && entryTable[i] != empty)
			delete(entryTable[i]);
		}
	delete (entryTable);
	cout<<" Program End \n";
}

void HashTable::printAllData(){
	int c=0;
	for(int i =0;i<tableSize;i++){
		if(entryTable[i]!=NULL & entryTable[i]!= empty){
			c++;	
			cout<<c<<" ) "<<entryTable[i]->word<<"\t:  "<<entryTable[i]->meaning<<endl;	
		}
	}
}

void HashTable::print(int pos){
	cout<<entryTable[pos]->word<<" \t:\t"<<entryTable[pos]->meaning<<endl;
}

unsigned int HashTable::hashCode(string str){
	unsigned int n=0;
	for(int i=0;i<str.size();i++)
		n+=((int)str[i])*powerArr[i];
	return n;
}

unsigned int HashTable::hashMap(unsigned int n){
	return (((n*a)+b)%tableSize);
}

unsigned int HashTable::hashMapProbe(unsigned int n){
	return (tableSize-(n%tableSize));
}

int HashTable::getTableSize(){
	return this->tableSize;
}

int HashTable::getNumOfElements()
{
	return this->numOfElements;
}

int HashTable::getNumOfCol()
{
	return this->numOfCol;
}

void HashTable::insert(string word,Entry *ptr){
	unsigned int n,p;
	p = getPos(word);
	if(p!=-1){
		delete(entryTable[p]);
		entryTable[p] = ptr;
	}
	else{
		n=hashCode(word);
		n=hashMap(n);
		p=hashMapProbe(n);
		if(entryTable[n]==NULL || entryTable[n]== empty)
			entryTable[n]=ptr;
		else{
			int i;
			numOfCol++;
			for(i=1; (entryTable[(n+i*p)%tableSize]!=NULL && entryTable[(n+i*p)%tableSize]!= empty);i++);
			entryTable[(n+i*p)%tableSize]=ptr;
		}
		numOfElements++;	
	}
}

void HashTable::search(string word){
	int pos;
	pos = getPos(word);
	if(pos == -1){
		cout<<"No Match Found!\n";
		return;
	}
	else{
		cout<<"Match Found!\n";
		cout<<"Word : "<<entryTable[pos]->word<<"\nMeaning : "<<entryTable[pos]->meaning<<endl;
		return;
	}
}

int HashTable::getPos(string word){
	int pos;
	unsigned int n,p;
	n=hashCode(word);
	n=hashMap(n);
	p=hashMapProbe(n);
	if(entryTable[n]!= empty && entryTable[n]->isEqual(word))
		return n;
	else{
		int i=1;
		while(entryTable[(n+i*p)%tableSize]!=NULL){
			if(entryTable[(n+i*p)%tableSize]== empty);
			else if(entryTable[(n+i*p)%tableSize]->isEqual(word))
				return ((n+i*p)%tableSize);
			i++;
		}
		return -1;
	}
}

void HashTable::remove(string word){
	int pos;
	unsigned int n,p;
	n=hashCode(word);
	n=hashMap(n);
	p=hashMapProbe(n);
	pos = getPos(word);
	if(pos==-1)
		cout<<" No such word found !";
	else{
		if(entryTable[pos+1] == NULL){
			delete(entryTable[pos]);
			entryTable[pos] = NULL;
		}
		else{
			delete(entryTable[pos]);
			entryTable[pos] = empty;
		}
		cout<<" Word removed !\n";
	}
	numOfElements--;
}

void HashTable::rehash(){
	int tempTableSize = tableSize;
	Entry **tempEntryTable = new Entry*[tempTableSize];
	for(int i =0;i<tempTableSize;i++)
		tempEntryTable[i]=NULL;
	for(int i =0;i<tempTableSize;i++){
		if(entryTable[i]!=empty && entryTable !=NULL){
			tempEntryTable[i] = entryTable[i];
		}
	}
	tableSize = tempTableSize*2+1;
	while(!checkPrime(tableSize))
		tableSize++;
	numOfElements=0;
	delete(entryTable);
	entryTable = new Entry*[tableSize];
	for(int i =0;i<tableSize;i++)
		entryTable[i]=NULL;
	for(int i =0;i<tempTableSize;i++){
		if(tempEntryTable[i]!=NULL)
			insert(tempEntryTable[i]->word,tempEntryTable[i]);
	}
	delete(tempEntryTable);
}

bool HashTable::checkPrime(int x){
	if(x==0 || x==1)
		return 0;
	for(int i=2; i<=x/2; i++){
		if(x%i==0)
			return 0;
	}
	return 1;
}


