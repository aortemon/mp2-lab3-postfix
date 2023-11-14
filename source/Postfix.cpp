#include "Postfix.h"


Postfix::Postfix() : infix(""), postfix("") {}


Postfix::Postfix(string _infix) : infix(_infix) {
	if (is_correct()) convert();
	else throw invalid_argument("Incorrect infix expr");
}


void Postfix::load(string expr) {
	// assigns expr to infix and tries to convert it to postfix

	infix.assign(expr);
	if (is_correct()) convert();
	else throw invalid_argument("Incorrect infix expr");
}



void Postfix::convert() { 
	// infix -> postfix

	postfix.assign(""); // if Postfix object has been used previously
	Stack<Letter> opeartors;

	for (Letter sign : infix) {
		switch (sign.type()) {

		case LetterType::OPEN_BRACKET: opeartors.push(sign); break;

		case LetterType::CLOSE_BRACKET: {
			while (char(opeartors.top()) != '(')
				postfix.push_back(opeartors.pop());
			opeartors.pop();
			break;
		};

		case LetterType::DIGIT: case LetterType::VARIABLE: postfix.push_back(sign); break;

		case LetterType::OPERATOR: {
			while (!opeartors.isEmpty() && sign.priority() >= opeartors.top().priority())
				postfix.push_back(opeartors.pop());
			opeartors.push(sign);
			break;
		};

		case LetterType::UNKNOWN: {
			if (sign != ' ') throw invalid_argument("Unknown character in infix string");
			break;
		}
		}
	}

	while (!opeartors.isEmpty())
		postfix.push_back(opeartors.pop());
}


bool Postfix::is_correct() {
	// infix correctness check

	string mask;

	// unifying infix string
	for (Letter sign : infix) {
		switch (sign.type()) {
		case LetterType::OPEN_BRACKET:	mask.push_back('0'); break;
		case LetterType::CLOSE_BRACKET: mask.push_back('1'); break;
		case LetterType::OPERATOR:		mask.push_back('2'); break;
		case LetterType::VARIABLE: case LetterType::DIGIT: mask.push_back('3'); break;
		}
	}

	// sholudn't start or end with operator
	if (mask[0] == '2' || mask[mask.size() - 1] == '2') return false;

	// looking for invalid subsequences
	for (string exclude : {"22", "33", "02", "21", "10", "30", "13"}) if (mask.find("22") != string::npos) return false;

	// count of open brackets should be equal with the count of close ones
	if (count(mask.begin(), mask.end(), '0') != count(mask.begin(), mask.end(), '1'))
		return false;

	return true;
}


bool Postfix::has_variables() {
	for (Letter sign : postfix) if (sign.type() == LetterType::VARIABLE) return true;
	return false;
}

map<char, double> Postfix::get_variables_map() {
	// finds all occurences of variables and asks user to enter them

	map<char, double> result;
	bool is_input_correct;
	string input;

	for (Letter sign : infix) 
		if (sign.type() == LetterType::VARIABLE)
			result[sign] = 0;
	for (auto const& imap : result) {
		is_input_correct = false;
		while (!is_input_correct) {
			cout << "Enter the value of " << imap.first << " variable: ";
			cin >> input;
			try {result[imap.first] = stod(input); is_input_correct = true; }
			catch (invalid_argument ignore) { cout << "Incorrect value, try again!" << endl; }
		}
	}
	return result;
}


double Postfix::execute() {
	// calculates expression asking user to set up variables or just calculates it if there are no of them
	if (has_variables()) return execute(get_variables_map());
	return execute({{}});
}


double Postfix::execute(map<char, double> vars) {
	// calculates expression using map of variables

	Stack<double> tmp;

	for (Letter sign : postfix)
		switch (sign.type()) {
		case LetterType::VARIABLE:	tmp.push(vars.at(sign)); break;
		case LetterType::DIGIT:		tmp.push(sign.to_int()); break;
		case LetterType::OPERATOR:
			double b = tmp.pop();
			double a = tmp.pop();
			switch (sign) {
			case '+': tmp.push(a + b); break;
			case '-': tmp.push(a - b); break;
			case '*': tmp.push(a * b); break;
			case '/': tmp.push(a / b); break;
			case '^': tmp.push(pow(a, b)); break;
			}
			break;
		}
	return tmp.pop();
}


string Postfix::get_infix() const { return infix; }


string Postfix::get_postfix() const { return postfix; }


ostream& operator<<(ostream& out, Postfix& v) {
	out << "Infix:   " << v.infix << endl;
	out << "Postfix: " << v.postfix << endl;
	return out;
}