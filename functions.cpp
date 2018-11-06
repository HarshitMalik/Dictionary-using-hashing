#include<iostream>
#include<set>
#include "functions.h"
using namespace std;

void mainMenu(HashTable &ht){
	char c;
	int ch;
	do{
		cout<<"\n  ***** MAIN MENU *****\n\n"
				<<" 1 ) Read file Data\n 2 ) Add new word\n"
				<<" 3 ) Remove a word\n 4 ) Search for a word\n"
				<<" 5 ) Get table size\n 6 ) Get number of words\n"
				<<" 7 ) SpellCheck\n 8 ) Rehash\n 9 ) Print all words\n"
				<<"Enter your choice : ";
		cin>>ch;
		switch(ch){
			case 1 : readFileData(ht);
						break;
			case 2 : addNewWord(ht);
						break;
			case 3 : removeWord(ht);
						break;
			case 4 : searchWord(ht);
						break;
			case 5 : getTableSize(ht);
						break;
			case 6 : getNumOfWord(ht);
						break;
			case 7 : spellCheck(ht);
						break;
			case 8 : ht.rehash(); cout<<"\nTable rehashed !\n";
						break;
			case 9 : ht.printAllData();
						break;
			default : cout<<" INVALID CHOICE \n";
		}
		cout<<"show menu again ? (y/n)";
		cin>>c;
	}while(c == 'y' || c == 'Y');
}

void readFileData(HashTable &ht){
	Entry *e;
	string word,meaning;
	ifstream fin;
	cout<<"Enter file name : ";
	cin>>word;
	fin.open(word);
	if(!fin.is_open())
		cout<<"\nError in file opening.\n";
	else{
		cout<<"File reading succesful.\n";
		while(fin>>word){
			if(ht.getNumOfElements()== ht.getTableSize()-1){
				ht.rehash();
			}
			getline(fin,meaning);
			meaning[0]=' ';
			e = new Entry(word,meaning);
			ht.insert(word,e);
		}		
		cout<<"Total words read : "<<ht.getNumOfElements()<<endl;
	}
	fin.close();
}

void addNewWord(HashTable &ht){
	if(ht.getNumOfElements()== ht.getTableSize()-1){
		ht.rehash();
	}
	string word,meaning;
	cout<<"Enter word :\n";
	cin>>word;
	cout<<"Enter meaning :\n";
	cin>>meaning;
	Entry *w = new Entry(word,meaning);
	ht.insert(word,w);
	cout<<" New word successfully added.\n";
}

void removeWord(HashTable &ht){
	if(ht.getNumOfElements()==0){
		cout<<" Dictionary is empty !\n";
		return;
	}
	string word;
	cout<<" Enter the word to be removed :\n";
	cin>>word;
	ht.remove(word);
}

void searchWord(HashTable &ht){
	if(ht.getNumOfElements()==0){
		cout<<" Dictionary is empty !\n";
		return;
	}
	string word;
	cout<<"Enter the word to be searched :\n";
	cin>>word;
	ht.search(word);
}

void spellCheck(HashTable &ht){
	string word, temp;
	set<string> sugWord;
	cout<<"Enter the word :\n";
	cin>>word;
	temp=word;
	if(ht.getPos(word)!=-1)
		ht.print(ht.getPos(temp));
	else{
		int i,j,pos;
		char c,ch;

		for(i=0;i<word.size();i++){
			ch = word[i];
			for(c='a';c<='z';c++){
				word[i] = c;
				if(ht.getPos(word)!=-1)
						sugWord.insert(word);
					//ht.print(ht.getPos(word));
			}
			word[i] = ch;
		}

		for(i=0;i<word.size()-1;i++){
			c = word[i];
			word[i] = word[i+1];
			word[i+1] = c; 
			if(ht.getPos(word)!=-1)
				sugWord.insert(word);
//				ht.print(ht.getPos(word));
			c = word[i];
			word[i] = word[i+1];
			word[i+1] = c; 
		}

		temp.push_back('a');
		for(i=temp.size()-1;i>0;i--){
			for(c='a';c<='z';c++){
				temp[i] = c;
				if(ht.getPos(temp)!=-1)
					sugWord.insert(temp);
//					ht.print(ht.getPos(temp));
			}
			c = temp[i];
			temp[i] = temp[i-1];
			temp[i-1] = c; 
		}
		for(c='a';c<='z';c++){
				temp[0] = c;
				if(ht.getPos(temp)!=-1)
					sugWord.insert(temp);
//					ht.print(ht.getPos(temp));
		}
		char ar[word.size()];
		temp = word;
		temp.pop_back();
		for(i=0;i<word.size();i++)
			ar[i]=word[i];
		for(i=0;i<word.size();i++){
			pos=0;
			for(j=0;j<word.size();j++){
				if(j!=i)
					temp[pos++]=ar[j];
			}
			if(ht.getPos(temp)!=-1)
				sugWord.insert(temp);
//					ht.print(ht.getPos(temp));
		}
		if(!sugWord.empty()){
			cout<<"\nSuggested Words :\n\n";
			for(auto itr = sugWord.begin(); itr!=sugWord.end(); itr++)
				ht.print(ht.getPos(*itr));
		}
		else
			cout<<"\nSorry! No Suggestion \n";
	}
}

void getTableSize(HashTable &ht){
	cout<<"Table size is : "<<ht.getTableSize()<<endl;
}

void getNumOfWord(HashTable &ht){
	cout<<"Total words in dictionary are : "<<ht.getNumOfElements()<<endl;
}

bool isPrime(int x){
	if(x==0 || x==1)
		return 0;
	for(int i=2; i<=x/2; i++){
		if(x%i==0)
			return 0;
	}
	return 1;
}




