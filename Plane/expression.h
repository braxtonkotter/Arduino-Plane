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

	~expression() {}

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

	double operator()(double); // Solve the expression with a variable number
private:
	void formatEquation();

	string exp;
};

expression::expression() {
	exp = "1";
}

expression::expression(string s) {
	exp = s;
	formatEquation();
	simplify();
}

expression::expression(const expression& e) {
	exp = e.exp;
}

expression expression::operator=(const expression& e) {
	return expression(e);
}

void expression::operator=(const string& s) {
	this->exp = s;
	formatEquation();
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

string expression::simplify(string s) { // Needed to nest

	char* ptr; //Pointer to the characters in the string

	string ans; //Factor 

	string exp1; // Holder for an isolated factor
	string exp2; // Factor in the process of being isolated

	for (ptr = &exp[0]; *ptr != string::npos; ptr++) { //Do until there's no more string.
		while (operators.find(*ptr) == string::npos) { exp2 += *ptr; ptr++; } //Find the next operator

		if (*ptr == '(') { //Find the matching parenthesis, and make a string of the value(s) between. P
			char* ptr2;
			int pCnt = 1;
			for (ptr2 = ptr + 1; *ptr2 != string::npos; ptr2++) { //Find the matching
				if (*ptr2 == '(') {
					pCnt++;
				}
				else if (*ptr2 == ')') {
					pCnt--;
				}

				if (pCnt == 0) {
					break;
				}
			}
		}

		if (exp1.empty()) { //If there is no first factor
			exp1 = exp2;
		}
		else { // This is where the math happens

		}
	}

	delete ptr;

	return newExpr;
}

void expression::simplify() {
	exp = simplify(exp);
}

void expression::formatEquation() {

	string newExpr;

	string temp;

	int parenthesisCnt = 0;

	for (int i = 0; i < exp.length(); i++) { // Prepare the expression for the operations that follow
		char c = exp[i];

		if (numericVal.find(c) != string::npos) { //If it's a numeric value, it can be standalone or as a coefficient
			if (c == '.') { //If it's a decimal, make sure it's properly used
				if (temp.empty()) {
					temp += '0'; //Add a zero if the decimal is the first value.
				}
				else { // If there's already a value 
					if (temp.find('.') != string::npos) { //If the number already has a decimal point, ignore this one.
						continue;
					}
				}
			}
			temp += c; //Add the value
		}
		else if (c == 't') { //If it's a variable value
			if (!temp.empty()) { //If there's another item before it
				if (temp.back() == '.') { //For syntax reasons
					temp.pop_back(); //Remove the decimal
				}
				temp += "*";
				newExpr += temp;
				temp = "";
			}
			temp += c; //Add the variable
		}
		else if (operators.find(c) != string::npos) { // If it's an operator
			if (c == '(' || c == ')') { //If we're dealing with a parenthesis, it'll be 5(x), 10+2(3+x). Split up into 5* ( x ), 10+ 2 * ( 3+ x )
				parenthesisCnt += (c == '(') ? 1 : -1;
				if (parenthesisCnt < 0) { //Parenthesis balancing
					newExpr = '(' + newExpr;
				}
				if (!temp.empty()) { //If there's a number before the operator, add a multiplication symbol, then clear.
					temp += '*';
					newExpr += temp;
					temp = ""; //Clear the current string
				}
			}
			temp += c; // Add the operator. Parentheses will be alone.
			newExpr += temp;
			temp = "";
		}
	}

	exp = newExpr;
}