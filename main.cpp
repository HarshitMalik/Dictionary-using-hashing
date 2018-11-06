#include<iostream>
#include<fstream>
#include "hashTable.hpp"
#include "functions.h"
using namespace std;

int main(){
	char choice;
	int size=0;
	cout<<"===== DICTIONARY =====\n\n";
	cout<<"Do you want to give table size ? (y/n)\n";
	cin>>choice;
	if( choice == 'y' || choice == 'Y' ){
		while(!isPrime(size)){
		cout<<"Enter table size (It should be prime) : ";
		cin>>size;
		if(isPrime(size))
			break;
		else
			cout<<size<<" is not a prime number.\nTry again\n";		
		}
	}
	HashTable ht(size);
	cout<<"Read word meaning file ? (y/n)\n";
	cin>>choice;
	if( choice == 'y' || choice == 'Y' ){
		readFileData(ht);
		mainMenu(ht);
	}
return 0;
}
