#include <string>
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
		BOOK * getNext(){ return next; }
		string getAuthorName(){ return authorName; }
		string getAuthorSurname(){ return authorSurname; }
		string getTitle(){ return title; }
		string getAbstract(){ return abstract; }
		int getId(){ return id; }
		string getISBN(){ return "978" + string(ISBN); }
		void display(){ cout << "[" << id << "][ISBN:" << "978" + string(ISBN)<< "] " << authorSurname << ", " << authorName << " | \"" << title << "\"\n\t" << abstract << endl; }
	};
}