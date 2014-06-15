#include "general.h"
#include <iostream>
namespace vth {
	//todo Throw, try, catch empty imput
	bool compare(string first, string second){
		first = lowercase(first);
		second = lowercase(second);
		int length = 0;
		if (first.length() > second.length()){
			length = second.length();
		}
		else {
			length = first.length();
		}

		for (int i = 0; i < length; i++){
			if (first[i] == second[i]){ continue; }
			else if (first[i]>second[i]){ return false; }
			else return true;
		}
		return true;
	}
	string lowercase(string input){
		int diff = 'a' - 'A';
		for (unsigned int i = 0; i < input.length(); i++){
			if (input[i] >= 'A'&&input[i] <= 'Z'){
				input[i] += diff;
			}
		}
		return input;
	}

	//WRONGID = -1,
	//EMPTYDATABASE,
	//WRONGPESEL,
	//DATABASECLEARED,
	//IDNOTFOUND,
	//DUPLICATERECORD,
	//WRONGISBNCOUNTRY,
	//WRONGISBNLENGTH,
	//RECORDNOTFOUND,
	//TOOMANYRECORDS
	void ERROR(int val){
		if (val == UNEXPECTED)
			cout << "Unexpected error";
		else if (val == WRONGID)
			cout << "Wrong id";
		else if (val == EMPTYDATABASE)
			cout << "Empty database";
		else if (val == WRONGPESEL)
			cout << "PESEL has wrong legth";
		else if (val == DATABASECLEARED)
			cout << "Database is cleared";
		else if (val == IDNOTFOUND)
			cout << "ID not found";
		else if (val == DUPLICATERECORD)
			cout << "Record is a duplicate";
		else if (val == WRONGISBNLENGTH)
			cout << "ISBN has wrong legth";
		else if (val == WRONGISBNCOUNTRY)
			cout << "Book cannot be registered in Poland";
		else if (val == RECORDNOTFOUND)
			cout << "Record not found";
		else if (val == TOOMANYRECORDS)
			cout << "More than one record found";
		else
			cout << "Unknown error " << val;
		cout << ".\n";
	}
}