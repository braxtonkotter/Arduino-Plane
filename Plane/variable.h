#pragma once
#include "utils.h"
#include <memory>
#include <string>
#include <math.h>

using std::shared_ptr;
using std::string;
using std::make_shared;

class expression;

class variable {
public:
	variable() { val = 0; var = false; operand = ' '; }
	variable(bool x, double v, char c = ' ') : val(v), var(x), operand(c) {  }
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

	void setOperator(const char ch) { operand = ch; }
	char getOperator() const { return operand; }

	void setNextVar(shared_ptr<variable> var);
	void setNextExp(shared_ptr<expression> exp);

	shared_ptr<variable> getNextVar() const { return nextVar; }
	shared_ptr<expression> getNextExp() const { return nextExp; }

	bool isVar() const { return var; }
	double value() const { return val; }
private:
	double val;
	bool var;

	char operand = ' ';

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