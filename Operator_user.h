#ifndef OPER_H_
#define OPER_H_

//#include <iostream>
//#include <vector>
//#include <sstream>
#include <exception>
#include "Filer.h"
#include "Coordinates.h"

using namespace std;

struct ParsingException : public exception
{
	const char * too_long() const throw() { return "Too long!!"; }
};

class Operator
{
private:
	vector<char> ascii_symbols;
	vector<string> degrees;
	string final_sentence;
	File_text text;
	Coords translator;
public:
	void setup_symbol(); // Good
	void setup_file();	// Good
	void parse_file();	// Good
	void making_sentence();
	void run();
	string get_sentence() const { return final_sentence; }
	void print_sentence() // Good
	{
		cout << get_sentence() << endl;
	}
};

#endif	// OPER_H_