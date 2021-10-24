#include <iostream>
#include <fstream>
#include "Contact.h"
using namespace std;
using namespace sdds;

int noOfRecs(const char* filename);
Contact ReadPhoneFromFile(istream& istr);

int main() {
	int i;
	int recs = noOfRecs("phoneNumbers.csv");
	Contact C{ "Gandalf The Grey",111,222,3 };
	ifstream phoneFile("phoneNumbers.csv");
	ofstream goodPhoneFile("goodNumbers.txt");
	cout << endl << "Rule of three test ---------------------------------------------" << endl;
	for (i = 0; phoneFile && i < recs; i++) {
		C = ReadPhoneFromFile(phoneFile);
		cout << C << endl;
	}
	return 0;
}

int noOfRecs(const char* filename) {
	int num = 0;
	ifstream file(filename);
	while (file) num += (file.get() == '\n');
	return num;
}

Contact ReadPhoneFromFile(istream& istr) {
	Contact C;
	istr >> C;
	cout << C.m_name << endl; // <---- this is nullptr 
	return C;
}
