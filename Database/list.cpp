#include "list.h"
#include "general.h"

namespace vth {
	void LIST<READER>::print(){
		if (root == NULL){
			throw EMPTYDATABASE;
		}
		else if (root->getNext() == NULL) {
			root->display();
			return;
		}
		else {
			READER * temp = root;
			while (temp != NULL) {
				temp->display();
				temp = temp->getNext();
			}
		}
	}
	void LIST<READER>::add(string inputName, string inputSurname, string inputPesel){
		READER * newPerson = new READER(inputName, inputSurname, inputPesel, id);
		if (root == NULL){
			root = newPerson;
		}
		else {
			READER * temp = root;
			if (temp->getPesel() == newPerson->getPesel()){
				throw THROWABLE(DUPLICATERECORD);
			}
			READER * previous = NULL;
			bool result = true;
			while (temp->getNext() != NULL){
				if (temp->getSurname() == inputSurname){
					result = compare(temp->getName(), inputName);
				}
				else {
					result = compare(temp->getSurname(), inputSurname);
				}
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
			if (temp->getNext() == NULL&&result==true){
				temp->setNext(newPerson);
			}
			else if (temp->getNext() != NULL&&result == false)
			{
				newPerson->setNext(temp);
				root = newPerson;
			}
			else{
				newPerson->setNext(temp);
				previous->setNext(newPerson);
			}
		}
		id++;
	}
	void LIST<READER>::pop(int delid){
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
}