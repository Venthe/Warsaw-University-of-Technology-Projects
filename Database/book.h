#include <string>
using namespace std;
namespace vth {
	class BOOK{
	private:
		int id;

		//author
		string author_name;
		string author_surname;

		// Book
		string title;
		string abstract;
		char ISBN[13];

		BOOK * next;
	public:
		BOOK() : next(NULL){}
		BOOK * getNext(){ return next; }
	};
}