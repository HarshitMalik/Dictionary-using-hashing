all: code

code: main.o hashTable.o functions.o entry.o
	g++ main.o hashTable.o functions.o entry.o -o code

main.o: main.cpp
	g++ -std=c++14 -c main.cpp

hashTable.o: hashTable.cpp
	g++ -std=c++14 -c hashTable.cpp

functions.o: functions.cpp
	g++ -std=c++14 -c functions.cpp

entry.o: entry.cpp
	g++ -std=c++14 -c entry.cpp

clean:
	rm -f *o code

run: code
		./code
