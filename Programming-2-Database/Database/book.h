#include <iostream>
#include "general.h"
using namespace std;
namespace vth {
	class BOOK{
	private:
		int id;

		//author
		string authorName;
		string authorSurname;

		// Book
		string title;
		string abstract;
		char ISBN[10];

		BOOK * next;
	public:
		BOOK() : next(NULL){}
		BOOK(string inputauthorName, string inputauthorSurname, string inputtitle, string inputabstract, string inputISBN, int gid, BOOK * inputnext = NULL);
		BOOK * getNext(){ return next; }
		string getName(){ return authorName; }
		string getSurname(){ return authorSurname; }
		string getTitle(){ return title; }
		string getAbstract(){ return abstract; }
		int getId(){ return id; }
		string getISBN(){ return "978" + string(ISBN); }
		void display(){ cout << "Book id: " << id << " | " << authorSurname << ", " << authorName << " | \"" << title << "\" | ISBN:" << "978" + string(ISBN) << " | " << abstract << endl; }
		void setNext(BOOK * iNext){
			next = iNext;
		};
	};
}