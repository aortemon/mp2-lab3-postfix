#ifndef POSTFIX_H
#define POSTFIX_H

#include <iostream>
#include <algorithm>
#include <map>
#include <exception>
#include <string>
#include "Letter.h"
#include "Stack.h"

using namespace std;

class Postfix {

	string infix;
	string postfix;

	void convert();						// infix expr -> postfix expr

	bool is_correct();					// is infix expr correct
	bool has_variables();				// are variables being used in expr
	map<char, double> get_variables_map();

public:
	
	Postfix();
	Postfix(string);
	
	void load(string);					// set/change infix string

	double execute();                   // shortened version of execute(map<char, double>) for exprs w/o variables
	double execute(map<char, double>);  // calculates expr using variables' values recieved from map

	string get_infix() const;
	string get_postfix() const;

	
	friend ostream& operator<<(ostream&, Postfix&);

};

//#include "Postfix.h"




#endif // POSTFIX_H