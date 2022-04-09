#pragma once
#include "expression.h"

class variable {
public:
	variable(char n, bool x = false, double v = 0) : name(n), value(v), var(x) {}

	double operator+(expression e); 
	double operator-(expression e); 
	double operator*(expression e); 
	double operator/(expression e); 
	double operator^(expression e); 

	double operator+(variable v);
	double operator-(variable v);
	double operator*(variable v);
	double operator/(variable v);
	double operator^(variable v);

	char getVariableName();
private:
	char name;
	double value;
	bool var;

	shared_ptr<operation>
};