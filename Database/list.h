#include <string>
#include "reader.h"
#include "book.h"

namespace vth {
	template <class c_type>
	class __LIST {
	protected:
		c_type * root;
		int id;
	public:
		__LIST() : root(NULL), id(0){}
		~__LIST(){
			while (root != NULL){
				root = root->getNext();
			}
		}
		void print(int delid = WRONGID);
		void pop(int delid = WRONGID);
		void pop(string input); // TODO: Delete via string, not only via id or pop
		bool find(int delid);
		bool find(string input);
	};
	
	template <class c_type>
	class LIST{};

	template<>
	class LIST<BOOK> : public __LIST<BOOK>{
	public:
		void add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN);
	};

	template<>
	class LIST<READER> : public __LIST<READER>{
		bool __compare(READER* first, READER* second);
	public:
		void add(string readerName, string readerSurname, string readerPesel);
	};
}