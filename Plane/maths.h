#pragma once
#include <math.h>
#include <memory>
#include <string>

class function;
class expression;
class variable;
class SpaceCurve;

using std::shared_ptr;
using std::string;
using std::make_shared;

//===== variable.h

class variable {
public:
	variable() { val = 0; var = false; operand = ' '; }
	variable(bool x, double v, char c = ' ') : val(v), var(x) {}
	variable(bool x, char c = ' ') : var(x), operand(c) { val = 0; }

	/*variable operator+(expression e);
	variable operator-(expression e);
	variable operator*(expression e);
	variable operator/(expression e);
	variable operator^(expression e);

	variable operator+(variable v);
	variable operator-(variable v);
	variable operator*(variable v);
	variable operator/(variable v);
	variable operator^(variable v);

	shared_ptr<variable> operator()(double d) const;*/

	void setOperand(const char ch) { operand = ch; }
	char getOperand() const { return operand; }

	void setNextVar(shared_ptr<variable> var);
	void setNextExp(shared_ptr<expression> exp);

	bool isVar() const { return var; }
	double value() const { return val; }
private:
	double val;
	bool var;

	char operand;

	shared_ptr<expression> nextExp = nullptr;
	shared_ptr<variable> nextVar = nullptr;
};

void variable::setNextVar(shared_ptr<variable> var) {
	nextVar = var;
}

void variable::setNextExp(shared_ptr<expression> var) {
	nextExp = var;
}

/*shared_ptr<variable> variable::operator()(double d) const
{
	auto temp = make_shared<variable>(false, val); //this copied
	if (isVar()) {
		temp->val = d;
	}

	temp->setOperand(operand);

	if (nextExp != nullptr) {
		temp->nextExp = nextExp->operator()(d);
	}
	else if (nextVar != nullptr) {
		temp->nextVar = nextVar->operator()(d);
	}

	return temp;
}*/

//===== expression.h

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

	char getOperand() const { return operand; }
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
			addVar(variable(false, strtod(ch_arr, &end)));
			ch_arr = end;
		}
		else if ((*ch_arr == '+' || *ch_arr == '-' || *ch_arr == '*' || *ch_arr == '/' || *ch_arr == '^') && getFinalOperand() == ' ') {
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

//===== function.h

class function {
public:
	function(string s);

	void operator+(function f); // Add function to another

	double operator()(double d); // Determine the value based on a parameter
private:
	expression val;
};

function::function(string s) {
	val = expression(&s[0]);
}

//====== SpaceCurve.h

class SpaceCurve {
public:
private:
	function x;
	function y;
	function z;
};