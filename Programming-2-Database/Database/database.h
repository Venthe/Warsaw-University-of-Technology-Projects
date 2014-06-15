#include "list.h"

namespace vth {
	class DATABASE {
	private:
		vth::LIST<READER> * readers; // List of all users in database, singly linked list
		vth::LIST<BOOK> * books;
	public:
		DATABASE();
		~DATABASE();
		void find(int selection, int id); // Find a person by ID
		void find(int selection, string input); // Find a person via String
		void pop(int selection, int id); //Pop via ID
		void pop(int selection, string input); //Pop via String
		void print(int selection, int id = WRONGID); //print database
		void add(string readerName, string readerSurname, string readerPESEL); //Add reader
		void add(string authorName, string authorSurname, string bookTitle, string bookAbstract, string ISBN); //Add book
		void clear(int selection); //Clears section of database
	};
}