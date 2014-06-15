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
			ERROR(UNEXPECTED);
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
			ERROR(e.val);
		}
		catch (...){
			ERROR(UNEXPECTED);
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
			ERROR(e.val);
		}
		catch (...){
			ERROR(UNEXPECTED);
		}
	}
	void DATABASE::print(int selection, int id)//print database
	{
		try {
			if (selection == READERS){
				// cout << "Printing READERS...\n";
				readers->print(id);
			}
			else if (selection == BOOKS){
				// cout << "Printing BOOKS...\n";
				books->print(id);
			}
		}
		catch (const THROWABLE &e){
			ERROR(e.val);
		}
		catch (...){
			ERROR(UNEXPECTED);
		}
	}
	void DATABASE::add(string readerName, string readerSurname, string readerPESEL){
		try{
			readers->add(readerName, readerSurname, readerPESEL);
		}
		catch (const THROWABLE &e){
			ERROR(e.val);
		}
		catch (...){
			ERROR(UNEXPECTED);
		}
	}
	void DATABASE::add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN){
		try{
			books->add(authorName, authorSurname, bookTitle, bookAbstract, ISBN);
		}
		catch (const THROWABLE &e){
			ERROR(e.val);
		}
		catch (...){
			ERROR(UNEXPECTED);
		}
	}
	void DATABASE::clear(int selection){
		try{
			if (selection == BOOKS){
				delete books;
				books = new LIST<vth::BOOK>;
			}
			else if (selection == READERS){
				delete readers;
				readers = new LIST<vth::READER>;
			}
		}
		catch (...){
			ERROR(UNEXPECTED);
		}
	}
}