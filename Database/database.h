#include <iostream>

//class ITEM {


//};

class PERSON {
friend class DATABASE;
private:
	std::string name;
	std::string surname;
	//ITEM * items; // TODO Another singly linked list; this time with items
	PERSON * next;

	PERSON* pNext();
	void setData(std::string name, std::string surname);
	void setNext(PERSON * inputNext);
	PERSON();
	void display();
};

class DATABASE {
private:
	PERSON * people;
public:
	DATABASE();
	~DATABASE();
	void print();
	void add(std::string name, std::string surname);
	void remove();//TODO Remove by narrowing down people to one record, or by id. Currently employed: Delete last
};