#pragma once
#include "utils.h"
#include "variable.h"
#include "coefficient.h"
#include <math.h>
#include <memory>

using std::shared_ptr;

struct mathoperator {
	char symbol;
	shared_ptr<expression> exPtr = nullptr;
	shared_ptr<variable> varPtr = nullptr;
	shared_ptr<coefficient> coPtr = nullptr;
};

class expression {
public:
	double operator+(expression e); // Return a number value for addition between the two expressions
	double operator-(expression e); // Return a number value for subtraction between the two expressions
	double operator*(expression e); // Return a number value for multiplication between the two expressions
	double operator/(expression e); // Return a number value for division between the two expressions
	double operator^(expression e); // Return a number value for exponent between the two expressions

	void operator+=(expression e); // Change the expression by adding another
	void operator-=(expression e);
	void operator*=(expression e);
	void operator/=(expression e);

	void simplify(); // Combines like terms

	double operator()(double); // Solve the expression with a variable number

private:

	shared_ptr<mathoperator> operation = nullptr;
};

double expression::operator+(expression e) {

}