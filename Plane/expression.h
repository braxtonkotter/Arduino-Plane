#pragma once
#include "utils.h"
#include "variable.h"
#include <math.h>
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;
using std::make_shared;
using std::stoi;

struct operation {
	char symbol = ' ';
	shared_ptr<expression> exPtr = nullptr;
	shared_ptr<variable> varPtr = nullptr;
};

class expression {
public:
	expression(string s);

	double operator+(expression e);
	double operator-(expression e);
	double operator*(expression e);
	double operator/(expression e);
	double operator^(expression e);

	void operator+=(expression e); // Change the expression by adding another to it
	void operator-=(expression e); // Change the expression by subtraction another to it
	void operator*=(expression e); // Change the expression by multiplying it by another
	void operator/=(expression e); // Change the expression by dividing it by another

	void simplify(); // Combines like terms

	double operator()(double); // Solve the expression with a variable number

private:
	double concatNum(string& s);
	string removeFirstChar(string& s);
	shared_ptr<variable> var = nullptr;
	shared_ptr<expression> nextExp = nullptr;
	operation operand;
};

double expression::concatNum(string& s) {
	bool dec = false;
	string preDec;
	string postDec;
	while((s[0]>='0' && s[0]<='9') || s[0] == '.') { // Split up the string to make a number string
		char ch = s[0];
		if (ch >= '0' && ch <= '9') {
			s = removeFirstChar(s);
			if (dec) {
				postDec += ch;
			}
			else {
				preDec += ch;
			}
		}
		else if (ch == '.') {
			dec = true;
		}
	}

	double front = stoi(preDec);

	if (dec) {
		front += stoi(postDec) / (pow(10,postDec.size()));
	}
	
	return front;
}

string expression::removeFirstChar(string& s) {
	string temp;
	for (int i = 1; i < s.size(); i++) {
		temp += s[i];
	}
	return temp;
}

expression::expression(string exp) { //Allowed: any char, any number, +, -, /, *, ^
	string temp = exp;
	while (temp.size() > 0) {
		char ch = temp[0];
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
			if (var != nullptr) {
				var = make_shared<variable>(ch, true);
			}
			else {
				operand.symbol = '*';
				temp = removeFirstChar(temp);
				nextExp = make_shared<expression>(temp);
			}
		}
		else if (ch >= '1' && ch <= '9') {
			int x = concatNum(temp);
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			operand.symbol = ch;
			temp = removeFirstChar(temp);
			nextExp = make_shared<expression>(temp);
		}

		temp = removeFirstChar(temp);
	}
}
double expression::operator+(expression e) {

}