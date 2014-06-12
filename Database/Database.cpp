#include "database.h"
namespace vth {
	DATABASE::DATABASE() : readers(new vth::LIST<READER>), books(new vth::LIST<BOOK>){
		cout << "Database Created!\n";
	}
	DATABASE::~DATABASE(){
		delete readers;
		delete books;
		cout << "Database destroyed!\n";
	}

	void DATABASE::find(int selection, int id){
		cout << "Record: ";
		DATABASE::print(selection, id);
	}
	void DATABASE::find(int selection, string input){
		try{
			if (selection == READERS){
				readers->find(input);
			}
			else if (selection == BOOKS){
				books->find(input);
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void DATABASE::pop(int selection, int id)//print database
	{
		try {
			if (selection == READERS){
				readers->pop(id);
			}
			else if (selection == BOOKS){
				books->pop(id);
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
	void DATABASE::pop(int selection, string input)
	{
		try {
			if (selection == READERS){
				readers->pop(input);
			}
			else if (selection == BOOKS){
				books->pop(input);
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
	void DATABASE::print(int selection, int id)//print database
	{
		try {
			if (selection == READERS){
				readers->print(id);
			}
			else if (selection == BOOKS){
				books->pop(id);
			}
		}
		catch (const THROWABLE &e){
			if (e.val == EMPTYDATABASE){
				cout << "Database is empty.\n";
			}
			else if (e.val == IDNOTFOUND){
				cout << "Record not found.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void DATABASE::add(string readerName, string readerSurname, string readerPESEL){
		try{
			readers->add(readerName, readerSurname, readerPESEL);
		}
		catch (const THROWABLE &e){
			if (e.val == WRONGPESEL){
				cout << "Pesel was wrong.\n";
			}
			else if (e.val == DUPLICATERECORD){
				cout << "Duplicate record.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
	void DATABASE::add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN){
		try{
			books->add(authorName, authorSurname, bookTitle, bookAbstract, ISBN);
		}
		catch (const THROWABLE &e){
			if (e.val == WRONGPESEL){
				cout << "Pesel was wrong.\n";
			}
			else if (e.val == DUPLICATERECORD){
				cout << "Duplicate record.\n";
			}
		}
		catch (...){
			cout << "Unexpected ERROR.\n";
		}
	}
}