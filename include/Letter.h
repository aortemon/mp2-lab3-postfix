#ifndef LETTER_H
#define LETTER_H

using namespace std;

// distinguished types of characters
enum class LetterType {DIGIT, VARIABLE, OPERATOR, OPEN_BRACKET, CLOSE_BRACKET, UNKNOWN}; 

// seems to improve readability and to shorten code
class Letter {

	char sign;

public:

	Letter(char _ = '0') : sign(_) {}
	
	operator char() { return sign; }	// to-char conversion

	int to_int() { return sign - 48; }	// simple to-int conversion

	LetterType type() {					// to-LetterType conversion
		if (sign >= 'a' && sign <= 'z' || sign >= 'A' && sign <= 'Z') return LetterType::VARIABLE;
		else if (sign >= '0' && sign <= '9') return LetterType::DIGIT;
		else if (string("+-*/^").find(sign) != string::npos) return LetterType::OPERATOR;
		else if (sign == '(') return LetterType::OPEN_BRACKET;
		else if (sign == ')') return LetterType::CLOSE_BRACKET;
		else return LetterType::UNKNOWN;
	}

	int priority() {
		if (sign == '^') return 1;
		else if (sign == '*' || sign == '/') return 2;
		else if (sign == '+' || sign == '-') return 3;
		else return 4;
	}
};

#endif // LETTER_H