#pragma once
#include "variable.h"

class expression {
public:
	expression();
	expression(char* ch_arr);
	expression(expression& e);

	expression operator=(expression& e);

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

	char getOperator() const { return operand; }
	void setOperator(const char ch) { operand = ch; }

	void setNextVar(shared_ptr<variable> var);
	void setNextExp(shared_ptr<expression> exp);

	shared_ptr<variable> getNextVar() const { return nextVar; }
	shared_ptr<expression> getNextExp() const { return nextExp; }

	void assign(string);
	void assign(char* ch_arr);

	shared_ptr<expression> operator()(double); // Solve the expression with a variable number

private:

	void addVar(variable);
	void addExp(expression);

	void setFinalSubOperator(const char ch);
	char getFinalSubOperator() const;

	shared_ptr<variable> nextVar = nullptr;
	shared_ptr<variable> firstSubVar = nullptr;
	shared_ptr<variable> finalSubVar = nullptr;

	shared_ptr<expression> nextExp = nullptr;
	shared_ptr<expression> firstSubExp = nullptr;
	shared_ptr<expression> finalSubExp = nullptr;

	char operand = ' ';
};

expression::expression() {}

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
		else if (( *ch_arr == '+' || *ch_arr == '-' || *ch_arr == '*' || *ch_arr == '/' || *ch_arr == '^') && getFinalSubOperator() == ' ') { //Basic operators
			setFinalSubOperator(*ch_arr);
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

expression::expression(expression& e) {
	auto tempVar = e.firstSubVar;
	auto tempExp = e.firstSubExp;

	while (!(tempVar==nullptr && tempExp == nullptr) && tempVar->getNextVar() != nullptr && tempExp->getNextExp() != nullptr) {
		
	}
}

expression expression::operator=(expression& e) {
	return expression(e);
}

void expression::addVar(variable var) {
	auto temp = make_shared<variable>(var);
	if (finalSubVar != nullptr) {
		if (finalSubVar->getOperator() == ' ') {
			finalSubVar->setOperator('*');
		}
		finalSubVar->setNextVar(temp);
	}
	else if (finalSubExp != nullptr) {
		if (finalSubExp->getOperator() == ' ') {
			finalSubExp->setOperator('*');
		}
		finalSubExp->setNextVar(temp);
	}
	finalSubVar = temp;
	finalSubExp = nullptr;
}

void expression::addExp(expression var) {
	auto temp = make_shared<expression>(var);
	if (finalSubVar != nullptr) {
		if (finalSubVar->getOperator() == ' ') {
			finalSubVar->setOperator('*');
		}
		finalSubVar->setNextExp(temp);
	}
	else if (finalSubExp != nullptr) {
		if (finalSubExp->getOperator() == ' ') {
			finalSubExp->setOperator('*');
		}
		finalSubExp->setNextExp(temp);
	}
	finalSubExp = temp;
	finalSubVar = nullptr;
}

char expression::getFinalSubOperator() const {
	if (finalSubVar != nullptr) {
		return finalSubVar->getOperator();
	}
	else if (finalSubExp != nullptr) {
		return finalSubExp->getOperator();
	}
	return ' ';
}

void expression::setFinalSubOperator(const char ch) {
	if (finalSubVar != nullptr) {
		finalSubVar->setOperator(ch);
	}
	else if (finalSubExp != nullptr) {
		finalSubExp->setOperator(ch);
	}
}
void expression::setNextVar(shared_ptr<variable> var) {
	nextVar = var;
}

void expression::setNextExp(shared_ptr<expression> var) {
	nextExp = var;
}