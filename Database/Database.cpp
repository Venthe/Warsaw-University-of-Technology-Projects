#include "database.h"
#include "stdafx.h"


//PErson class
PERSON::PERSON(){
	//	items = NULL;
	next = NULL;
}
void PERSON::display(){ // TODO Switch - display with or without items?
	std::cout << surname.c_str() << "; " << name.c_str() << std::endl;
}
PERSON* PERSON::pNext(){ return next; }
void PERSON::setData(std::string inputName, std::string inputSurname){
	name = inputName;
	surname = inputSurname;
}

//Database class
DATABASE::DATABASE(){
	people = NULL;
	std::cout << "Database created!\n";
}
DATABASE::~DATABASE(){ std::cout << "Databse destroyed!\n"; }
void DATABASE::print(){
	if (people == NULL){
		std::cout << "Database is empty!\n";
		return;
	}
	else if (people->pNext() == NULL) {
		std::cout << "1) ";
		people->display();
		return;
	}
	PERSON * temp = people;
	int recordCount = 1;
	while (temp != NULL) {
		std::cout << recordCount << ") ";
		temp->display();
		temp = temp->pNext();
		recordCount++;
	}
}
void PERSON::setNext(PERSON * inputNext){
	next = inputNext;
}
void DATABASE::add(std::string inputName, std::string inputSurname){
	std::cout << "Adding " << inputName.c_str() << " " << inputSurname.c_str() << "...\n";
	PERSON * newPerson = new PERSON;
	newPerson->setData(inputName, inputSurname);
	PERSON * temp = people;

	if (temp != NULL) {
		// Nodes already present in the list
		// Parse to end of list
		while (temp->pNext() != NULL) {
			temp = temp->pNext();
		}
		// Point the last node to the new node
		temp->setNext(newPerson);
	}
	else {
		// First node in the list
		people = newPerson;
	}

}

void DATABASE::remove(){

	// Create a temp pointer
	PERSON * temp = people;

	// No nodes
	if (temp == NULL){
		std::cout << "Database is empty!\n";
		return;
	}

	// Last node of the list
	if (temp->pNext() == NULL) {
		std::cout << "Deleting: ";
		temp->display();
		delete temp;
		people = NULL;
		std::cout << "Database cleared!\n";
	}
	else {
		PERSON *previous=NULL;
		while (temp->pNext() != NULL){
			previous = temp;
			temp = temp->pNext();
		}
		std::cout << "Deleting: ";
		temp->display();
		previous->setNext(NULL);
		delete temp;
		
		//// Parse thru the nodes
		//PERSON *previous;
		//do {
		//	if (tmp->Data() == data) break;
		//	prev = tmp;
		//	tmp = tmp->Next();
		//} while (temp != NULL);

		//// Adjust the pointers
		//prev->SetNext(tmp->Next());

		//// Delete the current node
		//delete tmp;
	}
}