#ifndef SDDS_CONTACT_H
#define SDDS_CONTACT_H
#include <iostream>
using namespace std;

namespace sdds {
	const int MaxNameLength = 55;

	class Contact
	{
		//char* m_name{}; // sets m_name to nullptr before any constructor invocation 
		//int m_area;
		int m_exchangeCode;
		int m_number;
		bool validPhone(int areaCode, int exchangeCode, int number)const;
		void setEmpty();
		void allocateAndCopy(const char* name);
		void extractChar(std::istream& istr, char ch)const;
		std::ostream& printPhoneNumber(ostream& istr)const;
		void set(const char* name, int areaCode, int exchangeCode, int number);

	public:
		char* m_name{};
		int m_area;
		Contact(const char* name = nullptr, int areaCode = 0, int exchangeCode = 0, int number = 0);
		Contact(const Contact& cnt);
		Contact& operator=(const Contact& cnt);
		~Contact();
		operator bool() const;
		std::ostream& print(ostream& ostr, bool toFile = true) const;
		std::istream& read(istream& istr);
	};

	std::ostream& operator<<(std::ostream& ostr, const Contact& cnt);
	std::istream& operator>>(std::istream& istr, Contact& cnt);
}
#endif // !SDDS_CONTACT_H


