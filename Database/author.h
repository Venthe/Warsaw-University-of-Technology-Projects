#include "person.h"

class AUTHOR : PERSON {
protected:
	AUTHOR * next;
public:
	//READER(const READER& p) {
	//	surname = p.surname;
	//	name = p.name;
	//	for (int i = 0; i < (sizeof(PESEL) / sizeof(char)); i++){
	//		PESEL[i] = p.PESEL[i];
	//	}

	//}
	//READER(string inputName, string inputSurname, string inputPesel, int gid, READER * next = NULL){

	//	if (inputPesel.length() != 11){
	//		throw THROWABLE(WRONGPESEL);
	//	}
	//	else{
	//		for (unsigned int i = 0; i < inputPesel.length(); i++){
	//			PESEL[i] = inputPesel[i];
	//		}
	//		name = inputName;
	//		surname = inputSurname;
	//		id = gid;
	//	}
	//}
	//READER(){
	//	for (int i = 0; i < (sizeof(PESEL) / sizeof(char)); i++){
	//		PESEL[i] = '0';
	//	}
	//	id = 0;
	//	name = "John";
	//	surname = "Doe";
	//	next = NULL;
	//}
	//void display(){
	//	cout << id << "] " << name.c_str() << " " << surname.c_str() << " ";
	//	for (int i = 0; i < (sizeof(PESEL) / sizeof(char)); i++){
	//		cout << PESEL[i];
	//	}
	//	cout << endl;
	//}
	//READER * getNext(){ return next; }
	////void setData(string inputName, string inputSurname, char inputPESEL[]);
	//void setNext(READER * newNext){
	//	next = newNext;
	//}
	//int getId(){ return id; }
};