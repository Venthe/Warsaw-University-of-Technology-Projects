#include "list.h"
#include <regex>
namespace vth {
	void LIST<BOOK>::add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN){}; //If ISBN 13, then skip first three
	void __LIST<BOOK>::print(int){};
	void __LIST<BOOK>::pop(int){};
	void __LIST<BOOK>::pop(string){} // TODO: Delete via string, not only via id or pop
	void __LIST<BOOK>::find(string input){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			BOOK * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				if (regex_search(temp->getAuthorName()+temp->getAbstract()+temp->getAuthorSurname()+temp->getISBN()+temp->getTitle(), self_regex)) {
					temp->display();
				}
				temp = temp->getNext();
			}
		}
	}

	void __LIST<READER>::find(string input){
		if (root == NULL){
			throw THROWABLE(EMPTYDATABASE);
		}
		else {
			READER * temp = root;
			regex self_regex(input, regex_constants::ECMAScript | regex_constants::icase);
			while (temp != NULL){
				if (regex_search(temp->getName()+temp->getPesel()+temp->getSurname(), self_regex)){
					temp->display();
				}
				temp = temp->getNext();
			}
		}
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
	void __LIST<READER>::print(int delid){
		if (root == NULL){
			throw EMPTYDATABASE;
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
	void __LIST<READER>::pop(int delid){
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
	void __LIST<READER>::pop(string input){} // TODO: Delete via string, not only via id or pop
}