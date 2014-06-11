#include "general.h"
#include "reader.h"
#include <string>

namespace vth {
	template <class c_type>
	class LIST{
	private:
		c_type * root;
		int id;
	public:
		LIST(){
			root = NULL;
			id = 0;
		}
		void print(); // TODO: Print certain record or all
		void pop(int delid);
		void pop(string input); // TODO: Delete via string, not only via id or pop
		void add(string inputName, string inputSurname, string inputPesel); // TODO: Add sorted!
	};
}