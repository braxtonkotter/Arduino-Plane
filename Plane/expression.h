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

class expression {
public:
	expression();
	expression(char* ch_arr);

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

	char getOperand() const{ return operand; }
	void setOperand(const char ch) { operand = ch; }

	void setNextVar(shared_ptr<variable> var);
	void setNextExp(shared_ptr<expression> exp);

	shared_ptr<expression> operator()(double); // Solve the expression with a variable number

private:

	void addVar(variable);
	void addExp(expression);

	void setFinalOperand(const char ch);
	char getFinalOperand() const;

	shared_ptr<variable> var = nullptr;
	shared_ptr<variable> finalVar = nullptr;

	shared_ptr<expression> Exp = nullptr;
	shared_ptr<expression> finalExp = nullptr;

	char operand;
};

expression::expression(char* ch_arr) { //Allowed: t, any number, +, -, /, *, ^, (, )
	while (*ch_arr != '\0') { // While there's still more string to traverse
		if (*ch_arr == 't') { // If it's a variable
			addVar(variable(true));
		}
		else if (*ch_arr >= '1' && *ch_arr <= '9') { // If it's a number
			char* end;
			addVar(variable(false,strtod(ch_arr, &end)));
			ch_arr = end;
		}
		else if (( *ch_arr == '+' || *ch_arr == '-' || *ch_arr == '*' || *ch_arr == '/' || *ch_arr == '^') && getFinalOperand() == ' ') {
			setFinalOperand(*ch_arr);
		}
		else if (*ch_arr == '(') {
			ch_arr++;
			addExp(expression(ch_arr));
		}
		else if (*ch_arr == ')') {
			break;
		}

		ch_arr++;
	}
	if (*ch_arr == '\0') {
		delete ch_arr;
	}
}

void expression::addVar(variable var) {
	auto temp = make_shared<variable>(var);
	if (finalVar->getOperand() == ' ') {
		finalVar->setOperand('*');
	}
	finalVar->setNextVar(temp);
	finalVar = temp;

	finalExp = nullptr;
}

void expression::addExp(expression exp) {
	auto temp = make_shared<expression>(exp);
	if (finalExp->getOperand() == ' ') {
		finalExp->setOperand('*');
	}
	finalExp->setNextExp(temp);
	finalExp = temp;

	finalVar = nullptr;
}