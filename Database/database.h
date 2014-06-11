#include "stdafx.h"
#include "list.h"
#include "general.h"
//#include <vector>

class DATABASE {
private:
	vth::LIST<READER> * readers; // List of all users in database, singly linked list
	// vector<int> __find(string input); // Internal find function
public:
	DATABASE::DATABASE(){
		readers = new vth::LIST<READER>;
	}
	void pop(int selection, int id = WRONGID)//print database
	{
		try {
			if (selection == READERS){
				readers->pop(id);
			}
		}
		catch (const THROWABLE &e){
			if (e.val == EMPTYDATABASE){
				cout << "Database is empty.\n";
			}
			else if (e.val == WRONGID){
				cout << "Wrong id!\n";
			}
			else if (e.val == DATABASECLEARED){
				cout << "Database is clear.\n";
			}
			else if (e.val == IDNOTFOUND){
				cout << "Record not found.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void pop(int selection, string input)//print database
	{
		try {
			if (selection == READERS){
				readers->pop(input);
			}
		}
		catch (const THROWABLE &e){
			if (e.val == EMPTYDATABASE){
				cout << "Database is empty.\n";
			}
			else if (e.val == WRONGID){
				cout << "Wrong id!\n";
			}
			else if (e.val == DATABASECLEARED){
				cout << "Database is clear.\n";
			}
			else if (e.val == IDNOTFOUND){
				cout << "Record not found.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void print(int selection)//print database
	{
		try {
			if (selection == READERS){
				readers->print();
			}
		}
		catch (const THROWABLE &e){
			if (e.val == EMPTYDATABASE){
				cout << "Database is empty.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void add(string inputName, string inputSurname, string inputPesel){
		try{
			readers->add(inputName, inputSurname, inputPesel);
		}
		catch (const THROWABLE &e){
			if (e.val == WRONGPESEL){
				cout << "Pesel was wrong.\n";
			}
			else if (e.val == DUPLICATERECORD){
				cout << "Duplicate record.\n";
			}
		}
		catch(...){
			cout << "Unexpected ERROR.\n";
		}
	}

	//DATABASE::~DATABASE(){
	//	while (people != NULL){
	//		people = people->getNext();
	//	}
	//	while (books != NULL){
	//		books = books->getNext();
	//	}
	//	while (authors != NULL){
	//		authors = authors->getNext();
	//	}
	//	//cout << "Database destroyed!\n";
	//}

	// Displaying whole database
	//void print(int subset = PEOPLE); // Print all
	//void print(int id, int subset = PEOPLE); // Print one record by id
	//void print(string input, int subset = PEOPLE); // Print one record by string

	//void add(string name, string surname,int NIN, int subset = PEOPLE);

	// Deleting
	//void pop(int subset = PEOPLE); // last
	//void remove(int id, int subset = PEOPLE); // by id

	// Public find; either by number or string
	//void find(int id, int subset = PEOPLE);
	//void find(string input, int subset = PEOPLE);

	//void optimize(); //remove unused entries
};