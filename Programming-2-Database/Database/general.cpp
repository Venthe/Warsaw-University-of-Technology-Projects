#include "general.h"

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
}