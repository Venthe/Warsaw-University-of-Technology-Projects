#include "list.h"
#include <regex>
namespace vth {
	int __LIST<BOOK>::__find(string input){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			BOOK * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				string SearchString = temp->getName() + " " + temp->getSurname() + " " + temp->getAbstract() + " " + temp->getTitle() + " " + temp->getISBN();
				if (regex_search(SearchString, self_regex)){
					BOOK * temp2 = temp->getNext();
					while (temp2 != NULL){
						SearchString = temp2->getName() + " " + temp2->getSurname() + " " + temp2->getAbstract() + " " + temp2->getTitle() + " " + temp2->getISBN();
						if (regex_search(SearchString, self_regex)){
							throw THROWABLE(TOOMANYRECORDS);
						}
						temp2 = temp2->getNext();
					}
					return temp->getId();
				}
				temp = temp->getNext();
			}
		}
		throw THROWABLE(RECORDNOTFOUND);
	}
	void __LIST<BOOK>::pop(int delid){
		if (root == NULL){
			if (delid == WRONGID){
				throw THROWABLE(EMPTYDATABASE);
			}
			else {
				throw THROWABLE(WRONGID);
			}
		}
		if (delid == WRONGID){
			if (root->getNext() == NULL) {
				root = NULL;
				throw THROWABLE(DATABASECLEARED);
			}
			else{
				BOOK * temp = root->getNext();
				BOOK * previous = root;

				while (temp->getNext() != NULL){
					previous = temp;
					temp = temp->getNext();
				}
				previous->setNext(NULL);

				delete temp, previous;
			}
		}
		else{
			if (root->getNext() == NULL&&root->getId() == delid) {
				root = NULL;
				throw THROWABLE(DATABASECLEARED);
			}
			else{
				if (root->getId() == delid){
					root = root->getNext();
					return;
				}
				BOOK * temp = root->getNext();
				BOOK * previous = root;

				while (temp->getNext() != NULL){
					if (temp->getId() == delid){ break; }
					previous = temp;
					temp = temp->getNext();
				}

				if (temp->getNext() == NULL&&temp->getId() != delid){
					throw THROWABLE(IDNOTFOUND);
				}
				previous->setNext(temp->getNext());

				delete temp, previous;
			}
		}
	}
	void __LIST<BOOK>::print(int delid){

		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else if (root->getNext() == NULL) {
			if (delid == root->getId() || delid == WRONGID){
				root->display();
				return;
			}
			throw THROWABLE(IDNOTFOUND);
		}
		else {
			BOOK * temp = root;
			while (temp != NULL) {
				if (delid == temp->getId() || delid == WRONGID){
					temp->display();
					if (delid != WRONGID){
						return;
					}
				}
				temp = temp->getNext();
			}
		}
		if (delid != WRONGID){
			throw THROWABLE(IDNOTFOUND);
		}
	}
	bool LIST<BOOK>::__compare(BOOK* first, BOOK* second){
		if (first->getSurname() == second->getSurname()){
			if (first->getName() == second->getName()){
				return compare(first->getTitle(), second->getTitle());
			}
			else{
				return compare(first->getName(), second->getName());
			}
		}
		else {
			return compare(first->getSurname(), second->getSurname());
		}
	}
	void LIST<BOOK>::add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN) //If ISBN 13, then skip first three
		// ISBN correction
	{
		// cout <<"\t* ISBN length: ["<< ISBN.length() << "] \"" << ISBN.c_str() <<"\"\n";
		if (ISBN.length() != 13 && ISBN.length() != 10){
			throw THROWABLE(WRONGISBNLENGTH);
		}
		else if (ISBN.length() == 13){
			if ((ISBN[0] == '9') && (ISBN[1] == '7') && (ISBN[2] == '8')){
				ISBN.erase(0, 3);
				//cout << ISBN;
			}
			else if ((ISBN[0] != '9') || (ISBN[1] != '7') || (ISBN[2] != '8')){
				throw THROWABLE(WRONGISBNCOUNTRY);
			}
		}


		BOOK * newBook = new BOOK(authorName, authorSurname, bookTitle, bookAbstract, ISBN, id);

		if (root == NULL){
			root = newBook;
		}
		else {
			BOOK * temp = root;
			if (temp->getISBN() == newBook->getISBN()){
				throw THROWABLE(DUPLICATERECORD);
			}
			BOOK * previous = NULL;
			//bool result = true;
			bool result = __compare(temp, newBook);
			if (result == false){
				newBook->setNext(temp);
				root = newBook;
			}
			else{
				while (temp->getNext() != NULL){
					if (temp->getISBN() == newBook->getISBN()){
						throw THROWABLE(DUPLICATERECORD);
					}
					result = __compare(temp, newBook);

					if (result == false){
						BOOK * temp2 = temp;
						while (temp2->getNext() != NULL){ // Is this a duplicate entry?
							if (temp->getISBN() == newBook->getISBN()){
								throw THROWABLE(DUPLICATERECORD);
							}
							temp2 = temp2->getNext();
						}
						break;
					}
					previous = temp;
					temp = temp->getNext();
				}

				if (temp->getNext() == NULL&&result == true){
					if (temp->getISBN() == newBook->getISBN()){
						throw THROWABLE(DUPLICATERECORD);
					}
					temp->setNext(newBook);
				}
				else{
					newBook->setNext(temp);
					previous->setNext(newBook);
				}
			}
		}
		id++;
	};
	void __LIST<BOOK>::find(string input){
		//cout << "input: " << input.c_str() << endl;
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			BOOK * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				string SearchString = temp->getName() + " " + temp->getSurname() + " " + temp->getAbstract() + " " + temp->getTitle() + " " + temp->getISBN();
				//cout << SearchString.c_str() << endl;
				if (regex_search(SearchString, self_regex)) {
					temp->display();
				}
				temp = temp->getNext();
			}
		}
	}
	void __LIST<BOOK>::pop(string input){
		pop(__find(input));
	} // TODO: Delete via string, not only via id or pop

	void __LIST<READER>::find(string input){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			//cout << "input: " << input.c_str() << endl;
			READER * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				string buff = temp->getName() + " " + temp->getPesel() + " " + temp->getSurname();
				//cout << buff.c_str() <<endl;
				if (regex_search(buff, self_regex)){
					temp->display();
				}
				temp = temp->getNext();
			}
		}
	}
	int __LIST<READER>::__find(string input){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			READER * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				string buff = temp->getName() + " " + temp->getPesel() + " " + temp->getSurname();
				if (regex_search(buff, self_regex)){

					READER * temp2 = temp->getNext();
					while (temp2 != NULL){
						buff = temp2->getName() + " " + temp2->getPesel() + " " + temp2->getSurname();
						if (regex_search(buff, self_regex)){
							throw THROWABLE(TOOMANYRECORDS);
						}
						temp2 = temp2->getNext();
					}


					return temp->getId();
				}
				temp = temp->getNext();
			}
		}
		throw THROWABLE(RECORDNOTFOUND);
	}
	bool LIST<READER>::__compare(READER* first, READER* second){
		if (first->getSurname() == second->getSurname()){
			return compare(first->getName(), second->getName());
		}
		else {
			return compare(first->getSurname(), second->getSurname());
		}
	}
	void LIST<READER>::add(string readerName, string readerSurname, string readerPesel){
		READER * newPerson = new READER(readerName, readerSurname, readerPesel, id);
		if (root == NULL){
			root = newPerson;
		}
		else {
			READER * temp = root;
			if (temp->getPesel() == newPerson->getPesel()){
				throw THROWABLE(DUPLICATERECORD);
			}
			READER * previous = NULL;
			//bool result = true;
			bool result = __compare(temp, newPerson);
			if (result == false){
				newPerson->setNext(temp);
				root = newPerson;
			}
			else{
				while (temp->getNext() != NULL){
					if (temp->getPesel() == newPerson->getPesel()){
						throw THROWABLE(DUPLICATERECORD);
					}
					result = __compare(temp, newPerson);

					if (result == false){
						READER * temp2 = temp;
						while (temp2->getNext() != NULL){ // Is this a duplicate entry?
							if (temp->getPesel() == newPerson->getPesel()){
								throw THROWABLE(DUPLICATERECORD);
							}
							temp2 = temp2->getNext();
						}
						break;
					}
					previous = temp;
					temp = temp->getNext();
				}

				if (temp->getNext() == NULL&&result == true){
					if (temp->getPesel() == newPerson->getPesel()){
						throw THROWABLE(DUPLICATERECORD);
					}
					temp->setNext(newPerson);
				}
				else{
					newPerson->setNext(temp);
					previous->setNext(newPerson);
				}
			}
		}
		id++;
	}
	void __LIST<READER>::pop(string input){
		pop(__find(input));
	} // TODO: Delete via string, not only via id or pop
	template<>
	void __LIST<READER>::pop(int delid){
		if (root == NULL){
			if (delid == WRONGID){
				throw THROWABLE(WRONGID);
			}
			else {
				throw THROWABLE(EMPTYDATABASE);
			}
		}
		if (delid == WRONGID){
			if (root->getNext() == NULL) {
				root = NULL;
				throw THROWABLE(DATABASECLEARED);
			}
			else{
				READER * temp = root->getNext();
				READER * previous = root;

				while (temp->getNext() != NULL){
					previous = temp;
					temp = temp->getNext();
				}
				previous->setNext(NULL);

				delete temp, previous;
			}
		}
		else{
			if (root->getNext() == NULL&&root->getId() == delid) {
				root = NULL;
				throw THROWABLE(DATABASECLEARED);
			}
			else{
				if (root->getId() == delid){
					root = root->getNext();
					return;
				}
				READER * temp = root->getNext();
				READER * previous = root;

				while (temp->getNext() != NULL){
					if (temp->getId() == delid){ break; }
					previous = temp;
					temp = temp->getNext();
				}

				if (temp->getNext() == NULL&&temp->getId() != delid){
					throw THROWABLE(IDNOTFOUND);
				}
				previous->setNext(temp->getNext());

				delete temp, previous;
			}
		}
	}
	void __LIST<READER>::print(int delid){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else if (root->getNext() == NULL) {
			if (delid == root->getId() || delid == WRONGID){
				root->display();
				return;
			}
			throw THROWABLE(IDNOTFOUND);
		}
		else {
			READER * temp = root;
			while (temp != NULL) {
				if (delid == temp->getId() || delid == WRONGID){
					temp->display();
					if (delid != WRONGID){
						return;
					}
				}
				temp = temp->getNext();
			}
		}
		if (delid != WRONGID){
			throw THROWABLE(IDNOTFOUND);
		}
	}
}