#include "general.h"
#include <string>

class PERSON {
protected:
	string name;
	string surname;
	int id;
public:
	virtual void display()=0;
	int getId(){ return id; }
	string getName(){ return name; }
	string getSurname(){ return surname; }
};