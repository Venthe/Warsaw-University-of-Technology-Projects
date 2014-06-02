#include "stdafx.h"
#include <vector>

//class ITEM {};

struct PERSON {
	friend class DATABASE;
private:
	string name;
	string surname;
	int pid;
	PERSON * next;
	//ITEM * items; // TODO Another singly linked list; this time with items
public:
	PERSON();
	string getData(int i);
	PERSON* getNext();
	void display();

	void setData(string name, string surname);
	void setPid(int gid);
	void setNext(PERSON * inputNext);
};

class DATABASE {
private:
	PERSON * people;
	int gid;
	vector<int> __find(string input);
public:

	//template <typename TYPE>
	DATABASE();
	~DATABASE();
	void print();
	void print(int id);
	void print(string input);
	void add(string name, string surname);
	void remove();//Delete last
	void remove(int id);//Delete by id
	void find(string input);
};