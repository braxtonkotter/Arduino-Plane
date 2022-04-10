#pragma once
#include "utils.h"
#include <math.h>
#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::make_shared;
using std::to_string;
using std::vector;

const static string expLegalChars = "1234567890t()+-*/^"; // All legal characters in an expression. All numbers, 't', and all operators. Plus parentheses.
const static string operators = "+-*/^";

class expression {
public:
	expression();
	expression(const string s);
	expression(const expression& e);
	expression operator= (const expression & e);

	// Used to combine two expressions together and make a new expression

	expression operator+(const expression& e);
	expression operator-(const expression& e);
	expression operator*(const expression& e);
	expression operator/(const expression& e);
	expression operator^(const expression& e);

	void operator+=(const expression& e); // Change the expression by adding another to it
	void operator-=(const expression& e); // Change the expression by subtraction another to it
	void operator*=(const expression& e); // Change the expression by multiplying it by another
	void operator/=(const expression& e); // Change the expression by dividing it by another

	string getExp() const { return exp; }

	void simplify();
	string simplify(string); // Combines like terms

	string isolateParentheses(string);

	bool singleTerm(const string); // Returns true if it's a single term

	double operator()(double); // Solve the expression with a variable number
private:
	string exp;
};

expression::expression() {
	exp = "";
}

expression::expression(string s) {
	int parenthCnt = 0;
	for (char c : s) {
		if (expLegalChars.find(c) != string::npos) {
			exp += c;
			if (c == '(') {
				parenthCnt++;
			}
			else if (c == ')') {
				parenthCnt--;
			}
		}
		if (parenthCnt < 0) {
			exp = "0";
			break;
		}
	}
	if (parenthCnt != 0) {
		exp = "0";
	}
}

expression::expression(const expression& e) {
	exp = e.exp;
}

expression expression::operator=(const expression& e) {
	return expression(e);
}

expression expression::operator+(const expression& e) {
	string ret = this->exp + "+(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator-(const expression& e) {
	string ret = this->exp + "-(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator*(const expression& e) {
	string ret = this->exp + "*(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator/(const expression& e) {
	string ret = this->exp + "/(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator^(const expression& e) {
	string ret = this->exp + "^(" + e.exp + ")";
	return expression(ret);
}

void expression::operator+=(const expression& e){
	this->exp = this->exp + "+(" + e.exp + ")";
}

void expression::operator-=(const expression& e) {
	this->exp = this->exp + "-(" + e.exp + ")";
}

void expression::operator*=(const expression& e) {
	this->exp = this->exp + "*(" + e.exp + ")";
}

void expression::operator/=(const expression& e) {
	this->exp = this->exp + "/(" + e.exp + ")";
}

double expression::operator()(double param) {
	string temp = exp;
	for (int i = 0; i < temp.length(); i++) {
		char c = temp[i];
		if (c == 't') {
			temp.replace(i, 1, "(" + to_string(param) + ")"); // Replaces all variables with the parameter
			i += 2;
		}
	}

	string simpli = simplify(temp);
	char* it = &simpli[0];
	char* c;
	return strtod(it,&c);
}

string expression::simplify(string s) {
	
	//Loop of combination of like terms followed by PEMDAS

	string temp = s;
	
	for (int i = 0; i < temp.length(); i++) {
		char c = temp[i];
		if (c == '(') {
			string parenth = isolateParentheses(temp, i);
		}
		else if (c == 't') {
			
		}

			
	}
}

string expression::isolateParentheses(string s) {

}

void expression::simplify() {
	exp = simplify(exp);
}

bool expression::singleTerm(const string s) {
	for (char c : operators) {
		if (exp.find(c) != string::npos) {
			return false;
		}
	}
	return true;
}