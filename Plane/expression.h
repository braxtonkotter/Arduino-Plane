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
const static string operators = "+-*/^";

class expression;

struct factor { // Fractions and Exponentials
	~factor() {
		delete exp1;
		delete exp2;
	}
	expression* exp1;
	expression* exp2;
	char operand;
};

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

	bool operator==(const expression& e); // Determines if the two expressions are equal
	bool operator==(double d);

	string getExp() const { return exp; }

	void simplify(); // Starts the simplification process for the specific class

	double operator()(const double); // Solve the expression with a variable number
private:
	void formatExpression();
	string getFactor(char*);
	string simplify(char*); // Combines like terms

	string exp;
};

expression::expression() {
	exp = "1";
}

expression::expression(string s) {
	exp = s;
	formatExpression();
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
	formatExpression();
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

bool expression::operator==(const expression& e) {
	expression exp = *this - e;
	exp.simplify();
	if (exp == 0) {
		return true;
	}
	return false;
}

bool expression::operator==(double d) {
	char* ptr;
	if (strtod(&exp[0], &ptr) == d) {
		if (*ptr == string::npos) {
			return true;
		}
	}
	return false;
}

double expression::operator()(const double param) {
	string temp;
	char* c = &exp[0];

	while (*c != string::npos) { //Until the end of the xpression
		if (*c == 't') {
			temp += param;
		}
		else {
			temp += *c;
		}
		c++;
	}

	double ret = strtod(&simplify(&temp[0])[0], &c);

	delete c;

	return ret;
}

string expression::simplify(char* ch) { // Needed to nest

	string simplified;
	string temp;

	while (*ch != string::npos) { //Until the end of hte expression is reached

	}

	return simplified;
}

string expression::getFactor(char* c) { //Hand me an operand and an expression! I will return as if multiplying or dividing otherwise!
	string ret;

	const bool pStart = *c == '('; // If we started with an open parenthesis
	c += pStart; // Move to the next one if so
	int pCnt = pStart;

	while (*c != string::npos) { //While we haven't hit the end of the string
		pCnt += (*c == '(' || *c == ')') ? (*c == '(') ? 1 : -1 : 0; // Add parenthesis count;
		if (pCnt == 0) { // If parentheses are balanced, we can terminate
			if (pStart) { //Don't add the final parenthesis pair
				break; 
			}
			if (operators.find(*c) != string::npos) { // If we're encountering a possible other factor
				if (pStart || (*c != '+' && *c != '-')) { // Ignore the final parenthesis if we started with one, or stop if it stops the factor
					break;
				}
				
			}
		}
		else if (pCnt < 0) { //Skip the end parenthesis
			pCnt++;
			continue;
		}
		ret += c;
		c++;
	}

	c++; //Move past the final value (an operator or a parenthesis

	return ret;
}

void expression::simplify() {
	exp = simplify(&exp[0]);
}

void expression::formatExpression() {

	// A loose decimal will have consequences. Ex: 6 +.t = 6 + 0 * t

	string newExpr;

	string temp; //Embodies the new factor

	int parenthesisCnt = 0;

	for (auto &c : exp) {

		if (expLegalChars.find(c) != string::npos) { //If it's a legal value
			if (c >= '0' && c <= '9') { //If it's a numeric value
				temp += c; //Add the value
			}
			else if (c == '.') { //If it's a decimal, make sure it's properly used
				if (temp.empty()) {
					temp += '0'; //Add a zero if the decimal is the first value.
				}
				else if(temp.find('.') != string::npos) { // If the number already has a decimal point, ignore this one.
						continue;
				}
			}
			else { //Once we stop adding to the number
				newExpr += temp;
				temp.clear();

				if (newExpr.back() == '.') { //If the final value was a decimal, remove it
					newExpr.pop_back();
				}

				char prev = newExpr.empty() ? '\0' : newExpr.back();

				if (operators.find(c) != string::npos) { //If current char is an operator
					if (prev=='\0') { // If this is the first value
						continue;
					}
					else if (operators.find(prev) != string::npos) { //If there was an operator before me. Ex: --, -+, ++, +- ILLEGAL CASES: ** , //, */, ^^, +*, -/
						if (c == '-' || c == '+') { //CASES: /+, *-, --, ++, +-
							if (c == '-' && prev == '-') { //CASE: --
								newExpr.pop_back();
								newExpr += '+';
								continue;
							}
							else if ((c == '+' && prev == '-') || (c == '-' && prev == '+')) { //CASES: +-, -+
								newExpr.pop_back();
								newExpr += '-';
								continue;
							}
							else if (c == '+' && prev == '+') { //CASE: ++
								continue;
							}
							else { //CASES: *-, /+
								if (c == '+') {
									continue; 
								}
							}
						}
						else { // CASES: ** , //, */, ^^, +*, -/  ... Skip all of these???
							continue;
						}
					}
					if (prev == '(' || prev == ')') { //If previous value was a parenthesis. Ex: )*, )+, (- ILLEGAL CASES: (/, (*,
						if ((c != '+' && c != '-') && prev == '(') { //CASES: (*, (/, (^
							continue;
						}
					}
					
				}
				else { // If current char is not an operator. Ex: t, (, )

					parenthesisCnt += (c == '(' || c == ')') ? (c == '(') ? 1 : -1 : 0;

					while (parenthesisCnt < 0) {
						parenthesisCnt++;
						newExpr = '(' + newExpr;
					}

					prev = newExpr.empty() ? '\0' : newExpr.back();

					if (prev == '\0') { //CASES: t, (

					}
					else if (operators.find(prev) == string::npos) { //If the last value wasn't an operator, multiply. Ex: 5), t), )) Special Cases: 5t, 5(, )(, () ILLEGAL CASES: (), )
						if ((c == 't' || c == '(')) {
							newExpr += '*';
						}
						else if (c == ')') {
							if (prev == '(') {
								newExpr.pop_back();
								continue; //Skip adding this end parenthesis.
							}
							else if (prev == '\0') {
								continue; //Don't add
							}
						}
					}
					else if (c == ')') { //If the previous value was an operator. Ex: +(, /(, *t, -t ILLEGAL CASES: *) , /), -) , +)
						if (operators.find(prev) != string::npos) {
							newExpr.pop_back();
						}
					}
				}
				newExpr += c; //Back here to include '(';
			}
		}
	}

	for (int i = 0; i < parenthesisCnt; i++) { // Parenthesis balancing
		newExpr += ')';
	}

	exp = newExpr;
}