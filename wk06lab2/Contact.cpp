#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Contact.h"
using namespace std;
namespace sdds {
	bool Contact::validPhone(int areaCode, int exchangeCode, int number)const {
		return areaCode >= 100 && areaCode <= 999 && exchangeCode >= 100 && exchangeCode <= 999 && number >= 0 && number <= 9999;
	}

	void Contact::setEmpty() {
		m_name = nullptr;
	}

	void Contact::allocateAndCopy(const char* name) {
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}

	void Contact::extractChar(std::istream& istr, char ch)const {
		if (istr.peek() != ch)
			istr.setstate(ios::failbit);
		else
			istr.get();
	}

	std::ostream& Contact::printPhoneNumber(std::ostream& ostr)const {
		ostr << "(" << m_area << ") " << m_exchangeCode << "_";
		ostr.width(4);
		ostr.fill('0');
		ostr << m_number;
		ostr.fill(' ');
		ostr.unsetf(ios::right);
		return ostr;
	}

	void Contact::set(const char* name, int areaCode, int exchangeCode, int number) {
		if (name && name[0] && validPhone(areaCode, exchangeCode, number))
		{
			allocateAndCopy(name);
			m_area = areaCode;
			m_exchangeCode = exchangeCode;
			m_number = number;
		}
		else
		{
			delete[] m_name;
			setEmpty();
		}
	}

	Contact::Contact(const char* name, int areaCode, int exchangeCode, int number) {
		set(name, areaCode, exchangeCode, number);
	}

	Contact::Contact(const Contact& cnt) {
		cout << cnt.m_area << endl; // <---- it has value comming from csv file
		cout << (cnt.m_name == nullptr) << endl; // <---- it has not value. it is nullptre
		if (cnt) {
			set(cnt.m_name, cnt.m_area, cnt.m_exchangeCode, cnt.m_number);
		}
	}

	Contact& Contact::operator=(const Contact& cnt) {
		if (this != &cnt)
			set(cnt.m_name, cnt.m_exchangeCode, cnt.m_exchangeCode, cnt.m_number);
		return *this;
	}

	Contact::~Contact() {
		delete[] m_name;
	}

	Contact::operator bool() const {
		return this->m_name != nullptr;
	}

	std::ostream& Contact::print(ostream& ostr, bool toFile) const {
		if (*this) {
			if (toFile) {
				ostr << "this is if\n";
			}
			else {
				int len = 50 - strlen(this->m_name);
				ostr << this->m_name;
				for (int i = 0; i < len; i++) {
					ostr << '.';
				}
				ostr << '(' << this->m_area << ") ";
				ostr << this->m_exchangeCode << '-';
			}
		}
		return ostr;
	}

	std::istream& Contact::read(istream& istr) {
		char name[MaxNameLength];
		//int ac = -1, ec = -1, num;
		//read mame using
		istr.get(name, MaxNameLength, ',');

		//extract a comma:
		extractChar(istr, ',');

		// (
		extractChar(istr, '(');

		//area code
		istr >> this->m_area;

		// )
		extractChar(istr, ')');

		//space
		extractChar(istr, ' ');

		//exchange code
		istr >> this->m_exchangeCode;

		//dash ('-')
		extractChar(istr, '-');

		//number
		istr >> this->m_number;

		extractChar(istr, '\n');

		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Contact& cnt) {
		if (cnt)
			cnt.print(ostr, false);
		else {
			ostr << "Invalid Phone Record";
		}
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Contact& cnt) {
		return cnt.read(istr);
	}
}
