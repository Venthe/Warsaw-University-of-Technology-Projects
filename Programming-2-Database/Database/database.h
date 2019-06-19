#include "list.h"

namespace vth {
	class DATABASE {
	private:
		vth::LIST<READER> * readers; // List of all users in database, singly linked list
		vth::LIST<BOOK> * books;
	public:
		DATABASE();
		~DATABASE();
		void find(int selection, int id);
		void find(int selection, string input);
		void pop(int selection, int id = WRONGID); //Pop via ID
		void pop(int selection, string input); //Pop via string database
		void print(int selection, int id = WRONGID); //print database
		void add(string readerName, string readerSurname, string readerPESEL); //Add reader
		void add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN); //Add book

		//void optimize(); //remove unused entries
	};
}