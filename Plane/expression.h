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

const static string expLegalChars = "1234567890.t()+-*/^"; // All legal characters in an expression. All numbers, 't', and all operators. Plus parentheses.
const static string operators = "()+-*/^";
const static string numericVal = "1234567890.";

class expression {
public:
	expression();
	expression(const string s);
	expression(const expression& e);
	expression operator= (const expression & e);
	void operator= (const string& s);

	// Used to combine two expressions together and make a new expression

	expression operator+(const expression& e) const;
	expression operator-(const expression& e) const;
	expression operator*(const expression& e) const;
	expression operator/(const expression& e) const;
	expression operator^(const expression& e) const;

	void operator+=(const expression& e); // Change the expression by adding another to it
	void operator-=(const expression& e); // Change the expression by subtraction another to it
	void operator*=(const expression& e); // Change the expression by multiplying it by another
	void operator/=(const expression& e); // Change the expression by dividing it by another

	string getExp() const { return exp; }

	void simplify(); // Starts the simplification process for the specific class
	string simplify(string); // Combines like terms

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
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
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
	simplify();
}

expression::expression(const expression& e) {
	exp = e.exp;
}

expression expression::operator=(const expression& e) {
	return expression(e);
}

void expression::operator=(const string& s) {
	*this = expression(s);
}

expression expression::operator+(const expression& e) const {
	string ret = "(" + this->exp + ")+(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator-(const expression& e) const {
	string ret = "(" + this->exp + ")-(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator*(const expression& e) const {
	string ret = "(" + this->exp + ")*(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator/(const expression& e) const {
	string ret = "(" + this->exp + ")/(" + e.exp + ")";
	return expression(ret);
}

expression expression::operator^(const expression& e) const {
	string ret = "(" + this->exp + ")^(" + e.exp + ")";
	return expression(ret);
}

void expression::operator+=(const expression& e){
	this->exp = "(" + this->exp + ")+(" + e.exp + ")";
	simplify();
}

void expression::operator-=(const expression& e) {
	this->exp = "(" + this->exp + ")-(" + e.exp + ")";
	simplify();
}

void expression::operator*=(const expression& e) {
	this->exp = "(" + this->exp + ")*(" + e.exp + ")";
	simplify();
}

void expression::operator/=(const expression& e) {
	this->exp = "(" + this->exp + ")/(" + e.exp + ")";
	simplify();
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

	vector<string> factors;

	string newExpr;

	string temp;
	
	for (int i = 0; i < s.length(); i++) { // Isolate all factors
		char c = s[i];

		//Isolate factors first, scoping down if need be.

		if (numericVal.find(c) != string::npos) { //If it's a numeric value, it can be standalone or as a coefficient
			if (!temp.empty() && c != '.') { //If there is a value and we're not dealing with a decimal
				if (temp.back()=='t') { // If the 

				}
			}
			if (c == '.') { //If it's a decimal, make sure it's properly used
				if (temp.empty()) {
					temp += '0'; //Add a zero if the decimal is the first value.
				}
				else { // If there's already a value 
					if (numericVal.find(temp.back()) == string::npos) { // If the most recent factor wasn't a number
						temp += '*';
						factors.push_back(temp);
						temp = c;
						continue;
					}
					bool flag = 0;
					for (char ch : temp) {
						if (ch == '.') {
							flag = 1;
							break;
						}
					}
					if (flag) {
						continue; //Skip adding the decimal if there's already one.
					}
				}
			}
			temp += c;
			if (i < s.length() - 1 && s[i + 1] == 't') { //If there is a next character and it's a variable, we factor it as a coefficient and variable.
				i++;
				temp += s[i];
				factors.push_back(temp);
				temp = "";
			}
		}
		else if (c == 't') { //If it's a variable value
			if (!temp.empty()) { //If there's another item before it
				if (temp.back() == '.') {
					temp.pop_back(); //Remove the decimal
				}
				temp += "*";
				factors.push_back(temp);
				temp = c;
			}
		}
		else if (c == '(') {
			if (!temp.empty()) {
				if (operators.find(temp.back()) == string::npos) {
					temp += "*";
				}
				if (i < s.length()) {
					temp += simplify(s.substr(i + 1)); //Get the rest of the string;
				}
			}
		}
		else if (c == ')') {
			temp += c;
			break;
		}
		else if (operators.find(c) != string::npos) { // If it's an operator
			factors.push_back(temp);
		}
	}

	return newExpr;
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