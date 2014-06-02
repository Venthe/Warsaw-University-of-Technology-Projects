#include "database.h"
#include "general.h"

//PErson class
PERSON::PERSON(){
	//	items = NULL;
	next = NULL;
}
void PERSON::display(){ // TODO Switch - display with or without items?
	cout << "[id:" << pid << "] " << surname.c_str() << "; " << name.c_str() << "\n";
}
PERSON* PERSON::getNext(){ return next; }
void PERSON::setData(string inputName, string inputSurname){
	name = inputName;
	surname = inputSurname;
}
void PERSON::setNext(PERSON * inputNext){
	next = inputNext;
}
void PERSON::setPid(int gid){
	pid = gid;
}
string PERSON::getData(int i){
	if (i == 0){ return surname; }
	else if (i == 1){ return name; }
	else{ return ""; }
}


//Database class
//template<typename TYPE>
vector<int> DATABASE::__find(string input){
	// Dynamically expanding array
	vector<int> returnValue;

	input = vth::lowercase(input);
	if (people == NULL){ // If empty
		returnValue.push_back(-1);
		return returnValue;
	}
	// todo modify to either output possible matches, or print single pid
	PERSON * temp = people;
	bool match = false;
	while (temp != NULL){

		int length = 0;
		if (input.length() > temp->getData(0).length()){
			length = temp->getData(0).length();
		}
		else {
			length = input.length();
		}

		string tempInput = vth::lowercase(temp->getData(0));
		match = true;
		int i = 0;

		for (; i < length; i++){
			if (input[i] == tempInput[i]){ continue; }
			else if (input[i] != tempInput[i]){ match = false; break; }
		}
		if (match == true){
			returnValue.push_back(temp->pid);
		}
		temp = temp->getNext();
	}
	if (returnValue.size() == 0){
		returnValue.push_back(-1);
		return returnValue;
	}

	return returnValue;
}
void DATABASE::find(string input){
	vector<int> temp = __find(input);
	if (temp[0] != -1){
		for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); ++it){
			if (*it == -1){ break; }
			cout << (*it) << " ";
		}
	}
	else{ cout << "Empty!"; }
	cout << "\n";
};
DATABASE::DATABASE(){
	people = NULL;
	gid = 0;
	cout << "Database created!\n";
}
DATABASE::~DATABASE(){
	while (people != NULL){
		people = people->getNext();
	}
	cout << "Database destroyed!\n";
}
void DATABASE::print(){
	if (people == NULL){
		cout << "Database is empty!\n";
		return;
	}
	else if (people->getNext() == NULL) {
		cout << "1) ";
		people->display();
		return;
	}
	PERSON * temp = people;
	int recordCount = 1;
	while (temp != NULL) {
		cout << recordCount << ") ";
		temp->display();
		temp = temp->getNext();
		recordCount++;
	}
}
void DATABASE::print(int id){
	if (people == NULL){
		cout << "Database is empty!\n";
		return;
	}
	else if (people->getNext() == NULL&&people->pid == id) {
		cout << "1) ";
		people->display();
		return;
	}
	PERSON * temp = people;
	while (temp != NULL) {
		if (temp->pid == id){
			temp->display();
			return;
		}
		temp = temp->getNext();
	}
	cout << "No matches in database!\n";
}
void DATABASE::print(string input){

	vector<int> id = __find("Lipiec");
	if (people == NULL){
		cout << "Database is empty!\n";
		return;
	}
	else if (id[0] == -1){
		cout << "No matches in database!\n";
	}
	else if (people->getNext() == NULL&&people->pid == id[0]) {
		cout << "1) ";
		people->display();
		return;
	}
	PERSON * temp = people;
	int record_count = 0;
	while (temp != NULL) {
		for (std::vector<int>::iterator it = id.begin(); it != id.end(); ++it){
			if (temp->pid == *it){
				cout << record_count << ") ";
				temp->display();
				record_count++;
			}
		}
		/*if (people->pid == *id){
			cout << record_count << ") ";
			temp->display();
			record_count++;
			*id++;
			}*/
		temp = temp->getNext();
	}
}

void DATABASE::add(string inputName, string inputSurname){
	cout << "Adding " << inputName.c_str() << " " << inputSurname.c_str() << "...\n";
	PERSON * newPerson = new PERSON;
	newPerson->setData(inputName, inputSurname);
	newPerson->setPid(gid);
	PERSON * temp = people;

	// Wrzuca rekord po zamiast przed przy true!
	if (temp != NULL) {// Add sorted insert
		if (vth::compare(newPerson->getData(0), temp->getData(0))){ //lipiec, gomulka -> false
			newPerson->setNext(temp);
			people = newPerson;
		}
		else{
			if (temp->getNext() == NULL){ //Insert record at the beginning
				if (vth::compare(newPerson->getData(0), temp->getData(0))){
					newPerson->setNext(temp);
					people = newPerson;
				}
				else{ people->setNext(newPerson); }
			}
			else{
				PERSON * prev = temp;
				while (temp->getNext() != NULL){
					if (vth::compare(newPerson->getData(0), temp->getData(0))){
						newPerson->setNext(temp);
						prev->setNext(newPerson);
						break;
					}
					prev = temp;
					temp = temp->getNext();
				}
				//cout << newPerson->getData(1).c_str() << " " << vth::compare(newPerson->getData(1), temp->getData(1)) << " " << temp->getData(1).c_str() << "\n";
			}
		}
	}
	else {
		people = newPerson;
	}
	gid++;
}
void DATABASE::remove(){

	// Create a temp pointer
	PERSON * temp = people;

	// No nodes
	if (temp == NULL){
		cout << "Database is empty!\n";
		return;
	}
	cout << "Deleting: ";

	// Last node of the list
	if (temp->getNext() == NULL) {
		people = NULL;
		cout << "Database cleared!\n";
	}
	else {
		PERSON *previous = NULL;
		while (temp->getNext() != NULL){
			previous = temp;
			temp = temp->getNext();
		}
		temp->display();
		previous->setNext(NULL);
	}
	delete temp;
}
void DATABASE::remove(int id){

	// Create a temp pointer
	PERSON * temp = people;

	// No nodes
	if (temp == NULL){
		cout << "Database is empty!\n";
		return;
	}

	// Last node of the list
	if (temp->getNext() == NULL&&temp->pid == id) {
		people = NULL;
		cout << "Database cleared!\n";
	}
	else {
		PERSON *previous = NULL;
		while (temp->getNext() != NULL){
			previous = temp;
			if (temp->pid == id){
				break;
			}
			temp = temp->getNext();
		}
		if (temp->pid == id){
			cout << "Deleting: ";
			temp->display();
			if (temp->getNext() == NULL){
				previous->setNext(NULL);
			}
			else{
				previous->setNext(temp->getNext());
			}
		}
	}

	delete temp;
}