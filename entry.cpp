#include<iostream>
#include<string>
#include "entry.hpp"
using namespace std;

Entry::Entry(){
	this->word.push_back('\0');
	this->meaning.push_back('\0');
}

Entry::Entry(string wordInp,string meaningInp){
	for(int i=0;i<wordInp.size();i++)
		this->word.push_back(wordInp[i]);
	for(int i=0;i<meaningInp.size();i++)
		this->meaning.push_back(meaningInp[i]);
}

bool Entry::isEqual(string str){
	if(this->word.size() != str.size())
		return 0;
	else{
		for(int i=0;i<str.size();i++){
			if(this->word[i] != str[i])
					return 0;
		}
		return 1;
	}
}
