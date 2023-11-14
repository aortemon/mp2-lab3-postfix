#include <iostream>
#include <exception>
#include "Postfix.h"
#include "../source/Postfix.cpp"

using namespace std;

void demonstrate() {
	string expr;
	Postfix a;
	bool is_end = false;
	while (!is_end) {
		bool is_expr_correct = false;
		while (!is_expr_correct) {
			cout << "Enter the expression: ";
			cin >> expr;
			try { a.load(expr); is_expr_correct = true;}
			catch (exception ignore) { cout << "Invalid input, try again!" << endl << endl; }
		}
		cout << a;
		cout << "Value: " << a.execute();

		string ans;
		while (!(ans == "0" || ans == "1")) {
			cout << endl << endl << "One more time? (1 / 0)" << endl;
			cin >> ans;
		}
		is_end = ans == "0";
		cout << endl << endl << "================================================" << endl << endl;
	}
}

void show_examples() {
	Postfix long_expr("(7 * (9 + 0) / 3) ^ 4 - 2 * ((7 - 5) ^ 2) - ((7 * (9 + 0) / 3) ^ 4 - 2 * ((7 - 5) ^ 2)) + 2 ^ (7 + 2 ^ 3 - 5)");
	Postfix expr_with_vars("x ^ y / z - 2 ^ w");
	cout << "Here we've got some examples" << endl << "Such as long expression:" << endl;
	cout << long_expr << endl << endl << "And expression with variables: " << endl;
	cout << expr_with_vars;
	cout << "Value:   " << expr_with_vars.execute({{'x', 12}, {'y', 2}, {'z', 9}, {'w', 4}}) << " (using x = 12, y = 2, z = 9, w = 4)" << endl;
}

int main() {
	demonstrate();
	show_examples();
}
