#include <string>
using namespace std;

namespace vth {
	class PERSON {
	protected:
		string name;
		string surname;
		int id;
	public:
		virtual void display() = 0;
		int getId();
		string getName();
		string getSurname();
	};
}