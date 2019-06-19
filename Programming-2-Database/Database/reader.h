#include <iostream>
using namespace std;

#include "general.h"
#include "person.h"
namespace vth {
	class READER : public PERSON{
	protected:
		char PESEL[11];
		READER * next;
	public:
		READER::READER(const READER& p) { // Copy constructor
			surname = p.surname;
			name = p.name;
			for (int i = 0; i < (sizeof(PESEL) / sizeof(char)); i++){
				PESEL[i] = p.PESEL[i];
			}
		}
		READER(string inputName, string inputSurname, string inputPesel, int gid, READER * next = NULL);
		READER();
		bool operator==(const READER& rhs);
		void display();
		READER * getNext();
		void setNext(READER * newNext);
		string getPesel();
	};
}